#include "Headers/Globals.h"
#include "Headers/Ui_Utils.h"
#include "Headers/Validators.h"
#include "Headers/CSV_Utils.h"

#include <iostream>
#include <string>     //for string variables
#include <cstdlib>    //for system clear command
#include <chrono>     // For time functionality
#include <iomanip>    // For formatting time
#include <vector>     //for vector storage
#include <limits>     //for numeric_limits
#include <filesystem> // For CSV Handling
#include <cctype>     // for toupper
#include <regex>      // for regex date validation
#include <fstream>    // to read and write in CSV
#include <sstream>    // for stringstream
#include <algorithm>  // for algorithms like find in CSV Helpers
#include <windows.h>  // For console cursor positioning

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::getline;
using std::max;
using std::numeric_limits;
using std::regex;
using std::regex_match;
using std::setprecision;
using std::streamsize;
using std::string;
using std::to_string;
using std::vector;

string ResolveCSVPath(const string &csvPath) // Path Resolver
{
    namespace fs = std::filesystem;
    try
    {
        fs::path p(csvPath);
        if (p.is_absolute())
        {
            if (fs::exists(p))
                return p.string();
        }
        else
        {
            if (fs::exists(p))
                return fs::absolute(p).string();
        }

        fs::path name = p.filename();
        for (auto &entry : fs::recursive_directory_iterator(fs::current_path()))
        {
            if (!entry.is_regular_file())
                continue;
            if (entry.path().filename() == name)
                return entry.path().string();
        }
    }
    catch (const std::exception &)
    {
        // ignore and return original path
    }
    return csvPath;
}

bool IsCSVReadable(const string &csvPath) // Checks if CSV is readable
{
    string pathToUse = ResolveCSVPath(csvPath);
    std::ifstream infile(pathToUse);
    if (!infile.is_open())
        return false;
    string tmp;
    return static_cast<bool>(getline(infile, tmp));
}

bool IsDateTaken(const string &dateStr, const string &csvPath)
{
    string pathToUse = ResolveCSVPath(csvPath);
    std::ifstream infile(pathToUse);

    if (!infile.is_open())
        return false;

    string line;
    int dateCol = -1;
    vector<string> headers;

    // CSV line parser
    auto parseCSVLine = [](const string &line) -> vector<string>
    {
        vector<string> result;
        string cur;
        bool inQuotes = false;
        for (size_t i = 0; i < line.size(); ++i)
        {
            char c = line[i];
            if (c == '"')
            {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"')
                {
                    cur.push_back('"');
                    ++i;
                }
                else
                    inQuotes = !inQuotes;
            }
            else if (c == ',' && !inQuotes)
            {
                size_t s = 0, e = cur.size();
                while (s < e && isspace((unsigned char)cur[s]))
                    ++s;
                while (e > s && isspace((unsigned char)cur[e - 1]))
                    --e;
                string f = cur.substr(s, e - s);
                if (f.size() >= 2 && f.front() == '"' && f.back() == '"')
                    f = f.substr(1, f.size() - 2);
                result.push_back(f);
                cur.clear();
            }
            else
                cur.push_back(c);
        }
        size_t s = 0, e = cur.size();
        while (s < e && isspace((unsigned char)cur[s]))
            ++s;
        while (e > s && isspace((unsigned char)cur[e - 1]))
            --e;
        string f = cur.substr(s, e - s);
        if (f.size() >= 2 && f.front() == '"' && f.back() == '"')
            f = f.substr(1, f.size() - 2);
        result.push_back(f);
        return result;
    };

    // Read header
    while (getline(infile, line))
    {
        if (line.empty())
            continue;
        headers = parseCSVLine(line);

        for (size_t idx = 0; idx < headers.size(); ++idx)
        {
            string h = headers[idx];
            transform(h.begin(), h.end(), h.begin(), ::tolower);
            if (h == "date")
            {
                dateCol = (int)idx;
                break;
            }
        }
        if (dateCol != -1)
            break;
    }

    if (dateCol == -1)
    {
        if (!headers.empty() && headers.size() >= 5)
            dateCol = 4;
        else
            return false;
    }

    // Rewind file to start reading data
    infile.clear();
    infile.seekg(0, std::ios::beg);
    getline(infile, line); // skip header line

    string targetNorm = NormalizeDate(dateStr);
    string targetShort;
    if (targetNorm.size() >= 10)
        targetShort = targetNorm.substr(0, 6) + targetNorm.substr(8, 2);

    // Check rows
    while (getline(infile, line))
    {
        if (line.empty())
            continue;
        vector<string> cells = parseCSVLine(line);

        if (dateCol >= 0 && dateCol < (int)cells.size())
        {
            string fileDateRaw = cells[dateCol];
            if (fileDateRaw.empty())
                continue;

            string fileDate = NormalizeDate(fileDateRaw); // Normalize CSV date too
            string fileShort;
            if (fileDate.size() >= 10)
                fileShort = fileDate.substr(0, 6) + fileDate.substr(8, 2);

            if (fileDate == targetNorm || (!targetShort.empty() && fileShort == targetShort))
            {
                return true;
            }
        }
    }

    return false;
}

void AppendToCSV(const string &csvToUse)
{
    auto csvEscape = [](const string &field) -> string
    {
        if (field.find_first_of(",\"") == string::npos)
            return field;
        string out = "\"";
        for (char c : field)
        {
            if (c == '"')
                out.push_back('"');
            out.push_back(c);
        }
        out += "\"";
        return out;
    };

    auto join = [](const vector<string> &v, const string &sep) -> string
    {
        string r;
        for (size_t i = 0; i < v.size(); ++i)
        {
            if (i)
                r += sep;
            r += v[i];
        }
        return r;
    };

    auto joinDouble = [](const vector<double> &v, const string &sep) -> string
    {
        string r;
        for (size_t i = 0; i < v.size(); ++i)
        {
            if (i)
                r += sep;
            r += to_string(v[i]);
        }
        return r;
    };

    // Match the NEW CSV structure (36 columns)
    vector<string> cols(34, "");
    cols[0] = to_string(ClientID);
    cols[1] = csvEscape(ClientName);
    cols[2] = csvEscape(ClientNum);
    cols[3] = csvEscape(ClientAddress);
    cols[4] = csvEscape(NormalizeDate(EventDate));
    cols[5] = csvEscape(NormalizeTime(EventTime));
    cols[6] = csvEscape(Venue);
    cols[7] = csvEscape(ClientLandmarks);
    cols[8] = csvEscape(EventType);
    cols[9] = PaxAmount > 0 ? to_string(PaxAmount) : "";
    cols[11] = csvEscape(join(chosenEntrees, ";"));
    cols[12] = csvEscape(join(chosenDrinks, ";"));
    cols[13] = csvEscape(join(chosenAppetizers, ";"));
    cols[14] = csvEscape(join(chosenDesserts, ";"));
    cols[15] = to_string(baseCateringCost); // Catering Rate
    cols[17] = csvEscape(join(chosenEmcee, ";"));
    cols[18] = joinDouble(chosenEmceeRate, ";"); // Emcee Rate
    cols[20] = csvEscape(join(chosenPhotoboothPackage, ";"));
    cols[21] = joinDouble(chosenPhotoboothRate, ";"); // Photobooth Rate
    cols[23] = csvEscape(join(designNotes, ";"));
    cols[24] = to_string(venueSetupCost);                                   // Design Rate
    cols[26] = to_string(TotalServiceCost);                                 // Total Cost
    cols[28] = "Pending";                                                   // Payment Status
    cols[29] = "Pending";                                                   // Event Status (new column)
    cols[31] = !PayDate.empty() ? csvEscape(join(PayDate, ";")) : "";       // PaymentDate
    cols[32] = !PayAmount.empty() ? joinDouble(PayAmount, ";") : "";        // AmountPaid
    cols[33] = !PayRemarks.empty() ? csvEscape(join(PayRemarks, ";")) : ""; // Remarks

    std::ofstream outfile(csvToUse, std::ios::app);
    if (!outfile.is_open())
    {
        cout << "\nError: Could not open " << csvToUse << " for writing!\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    for (size_t i = 0; i < cols.size(); ++i)
    {
        if (i > 0)
            outfile << ",";
        outfile << cols[i];
    }
    outfile << "\n";
    outfile.flush();
    outfile.close();

    cout << "\nEvent successfully saved to " << csvToUse << "!\n";
}