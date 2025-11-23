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

bool ValidateDate(const string &date)
{
    regex datePattern(R"(^\d{2}/\d{2}/\d{2}$)");
    return regex_match(date, datePattern);

    
}

// Date Format Checker
bool Date_Checker(const string &dateStr)
{
    const regex date_pattern(
        R"(^\s*(0?[1-9]|1[0-2])/(0?[1-9]|[12][0-9]|3[01])/((\d{2})|(19|20)\d{2})\s*$)");
    return regex_match(dateStr, date_pattern);
}

// Time Format Checker
bool Time_Checker(const string &timeStr)
{
    const regex time_pattern(
        R"(^([0-9]|0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])-([0-9]|0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])$)"); //HH:MM-HH:MM - Military Time
    return regex_match(timeStr, time_pattern);
}

string NormalizeTime(const string &timeStr)
{
    std::smatch m;
    regex r(R"(^\s*([0-9]|0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])-([0-9]|0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])\s*$)");

    if (regex_match(timeStr, m, r))
    {
        // Extract start and end time parts
        string startH = m[1].str();
        string startM = m[2].str();
        string endH = m[3].str();
        string endM = m[4].str();

        // Add leading zeroes where needed
        if (startH.size() == 1)
            startH = "0" + startH;
        if (endH.size() == 1)
            endH = "0" + endH;

        return startH + ":" + startM + "-" + endH + ":" + endM;
    }

    return timeStr; // Return as-is if not matched
}



string NormalizeDate(const string &dateStr)
{
    std::smatch m;
    regex r(R"(^\s*(0?[1-9]|1[0-2])/(0?[1-9]|[12][0-9]|3[01])/((\d{2})|(19|20)\d{2})\s*$)");

    if (regex_match(dateStr, m, r))
    {

        string mm = m[1].str();
        if (mm.size() == 1) // Add 0 in the beginning if need
            mm = "0" + mm;

        string dd = m[2].str();
        if (dd.size() == 1) //  Add 0 in the beginning if need
            dd = "0" + dd;

        string yy = m[3].str();
        if (yy.size() == 2)
            yy = "20" + yy; // Convert "25" to "2025"

        return mm + "/" + dd + "/" + yy;
    }

    return dateStr; // Return as-is if not matched
}
