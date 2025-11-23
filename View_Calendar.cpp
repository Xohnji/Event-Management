#include "Headers/Globals.h"
#include "Headers/Ui_Utils.h"
#include "Headers/Validators.h"
#include "Headers/CSV_Utils.h"
#include "Headers/View_Calendar.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <vector>
#include <limits>
#include <filesystem>
#include <cctype>
#include <regex>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <windows.h>

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

// Helper function to safely get column value
string GetColumnValue(const vector<string>& columns, size_t index, const string& defaultValue)
{
    if (index < columns.size())
    {
        return columns[index];
    }
    return defaultValue;
}

// Helper function to parse CSV line with proper handling of empty fields
vector<string> ParseCSVLine(const string& line)
{
    vector<string> result;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.length(); ++i)
    {
        char c = line[i];

        if (c == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes)
        {
            result.push_back(current);
            current.clear();
        }
        else
        {
            current += c;
        }
    }
    result.push_back(current);

    return result;
}

void View_Booking_Calendar()
{
    int left = 20, top = 1, width = 96, height = 47;

    do
    {
        Clear_Terminal();
        Border(left, top, width, height);

        string line(71, '=');
        gotoxy(33, 3);
        cout << line;
        gotoxy(49, 4);
        cout << "MAIN MENU: 4. VIEW BOOKING CALENDAR";
        gotoxy(33, 5);
        cout << line;

        gotoxy(33, 6);
        cout << "Current Date: ";

        // Display actual current date
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm *local_time = std::localtime(&now_time);
        gotoxy(47, 6);
        cout << std::put_time(local_time, "%m/%d/%Y");

        gotoxy(43, 9);
        cout << "--- UPCOMING & ACTIVE EVENTS SCHEDULE ---";
        gotoxy(25, 10);
        cout << "-----------------------------------------------------------------------------------------";
        gotoxy(25, 11);
        cout << "|   DATE     | EVENT ID  |      CLIENT NAME      |         STATUS        |  TOTAL GUEST |";
        gotoxy(25, 12);
        cout << "|------------|-----------|-----------------------|-----------------------|--------------|";

        string PathResolved = ResolveCSVPath(csvToUse);
        std::ifstream file(PathResolved);

        if (!file.is_open())
        {
            gotoxy(25, 15);
            cout << "Error: Could not open CSV file at: " << PathResolved;
            gotoxy(25, 16);
            cout << "Press Enter to return...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        // Only show "On-going" and "Upcoming" events
        int row = 13;
        const int MAX_DISPLAY_ROWS = 10;
        int displayedEvents = 0;
        int activeEvents = 0;
        int totalEvents = 0;

        string line_data;
        getline(file, line_data); // Skip header

        while (getline(file, line_data))
        {
            if (line_data.empty())
                continue;

            vector<string> columns = ParseCSVLine(line_data);

            // Get essential fields with safe access
            string clientID = GetColumnValue(columns, 0);
            string clientName = GetColumnValue(columns, 1);
            string date = GetColumnValue(columns, 4);
            string pax = GetColumnValue(columns, 9);
            
            // Event status is in a fixed position in the CSV structure
            // Based on the CSV: Payment,Event Status,,PaymentDate...
            string eventStatus = GetColumnValue(columns, 29, "PENDING");

            if (clientID.empty())
                continue;

            totalEvents++;

            // Convert status to uppercase for comparison
            string statusUpper = eventStatus;
            transform(statusUpper.begin(), statusUpper.end(), statusUpper.begin(), ::toupper);

            // FILTER: Only show active events (not DONE or PENDING for inquiry)
            if (statusUpper.find("DONE") != string::npos)
            {
                continue;
            }

            activeEvents++;

            // Only display first MAX_DISPLAY_ROWS active events
            if (displayedEvents < MAX_DISPLAY_ROWS)
            {
                // Truncate long names
                string displayName = clientName;
                if (displayName.length() > 21)
                    displayName = displayName.substr(0, 18) + "...";

                // Display row
                gotoxy(25, row);
                cout << "|";
                gotoxy(27, row);
                cout << (date.length() > 10 ? date.substr(0, 10) : date);
                gotoxy(38, row);
                cout << "|";
                gotoxy(40, row);
                cout << (clientID.length() > 9 ? clientID.substr(0, 9) : clientID);
                gotoxy(50, row);
                cout << "|";
                gotoxy(52, row);
                cout << displayName;
                gotoxy(74, row);
                cout << "|";
                gotoxy(76, row);
                cout << eventStatus;
                gotoxy(98, row);
                cout << "|";
                gotoxy(100, row);
                cout << (pax.length() > 12 ? pax.substr(0, 12) : pax);
                gotoxy(113, row);
                cout << "|";

                row++;
                displayedEvents++;
            }
        }
        file.close();

        // Fill empty rows if less than MAX_DISPLAY_ROWS events
        while (row < 13 + MAX_DISPLAY_ROWS)
        {
            gotoxy(25, row);
            cout << "|            |           |                       |                       |              |";
            row++;
        }

        gotoxy(25, row);
        cout << "-----------------------------------------------------------------------------------------";
        row++;

        // Show count of active/pending events
        gotoxy(25, row);
        cout << "Active/Upcoming Events: " << activeEvents;
        if (activeEvents > MAX_DISPLAY_ROWS)
        {
            cout << " (Showing first " << MAX_DISPLAY_ROWS << ")";
        }
        gotoxy(25, row + 1);
        cout << "Total Events in System: " << totalEvents << " (including completed)";
        row += 3;

        gotoxy(25, row);
        cout << "--- CALENDAR ACTIONS ---";
        row++;
        gotoxy(25, row);
        cout << "1. View All Active Events (Detailed)";
        row++;
        gotoxy(25, row);
        cout << "2. View All Events Including Completed";
        row++;
        gotoxy(25, row);
        cout << "3. Return to Main Menu";
        row++;

        int VBC_choice;
        while (true)
        {
            gotoxy(25, row);
            cout << "Enter Choice (1-3): ";
            gotoxy(45, row);
            cin >> VBC_choice;

            if (cin.fail() || VBC_choice < 1 || VBC_choice > 3)
            {
                cin.clear();
                Clear_Getline();
                gotoxy(25, row + 1);
                cout << "Invalid input! Try again...";
                ClearLine(45, row, 10);
                continue;
            }
            break;
        }

        if (VBC_choice == 1)
        {
            // VIEW ACTIVE EVENTS DETAILED
            Clear_Terminal();
            Border(10, 1, 100, 30);

            gotoxy(15, 2);
            cout << string(86, '=');
            gotoxy(35, 3);
            cout << "YNARICH EMS: ACTIVE EVENTS - DETAILED VIEW";
            gotoxy(15, 4);
            cout << string(86, '=');

            gotoxy(15, 6);
            cout << "DATE";
            gotoxy(28, 6);
            cout << "ID";
            gotoxy(35, 6);
            cout << "CLIENT NAME";
            gotoxy(55, 6);
            cout << "EVENT TYPE";
            gotoxy(72, 6);
            cout << "PAX";
            gotoxy(82, 6);
            cout << "STATUS";
            gotoxy(15, 7);
            cout << string(86, '-');

            int detailRow = 8;
            int detailCount = 0;
            const int MAX_DETAIL_ROWS = 18;

            PathResolved = ResolveCSVPath(csvToUse);
            std::ifstream file2(PathResolved);

            if (!file2.is_open())
            {
                gotoxy(15, 10);
                cout << "Error: Could not open CSV file!";
                gotoxy(20, 28);
                cout << "Press Enter to return...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            getline(file2, line_data); // Skip header

            while (getline(file2, line_data) && detailRow < 8 + MAX_DETAIL_ROWS)
            {
                if (line_data.empty())
                    continue;

                vector<string> columns = ParseCSVLine(line_data);

                string clientID = GetColumnValue(columns, 0);
                string clientName = GetColumnValue(columns, 1);
                string date = GetColumnValue(columns, 4);
                string eventType = GetColumnValue(columns, 8);
                string pax = GetColumnValue(columns, 9);
                string eventStatus = GetColumnValue(columns, 29, "PENDING");

                if (clientID.empty())
                    continue;

                // Convert to uppercase for comparison
                string statusUpper = eventStatus;
                transform(statusUpper.begin(), statusUpper.end(), statusUpper.begin(), ::toupper);

                // FILTER: Only show active events (not DONE)
                if (statusUpper.find("DONE") != string::npos)
                {
                    continue;
                }

                // Display detailed info
                gotoxy(15, detailRow);
                cout << (date.length() > 10 ? date.substr(0, 10) : date);
                gotoxy(28, detailRow);
                cout << clientID;
                gotoxy(35, detailRow);
                cout << (clientName.length() > 18 ? clientName.substr(0, 18) : clientName);
                gotoxy(55, detailRow);
                cout << (eventType.length() > 15 ? eventType.substr(0, 15) : eventType);
                gotoxy(72, detailRow);
                cout << pax;
                gotoxy(82, detailRow);
                cout << (eventStatus.empty() ? "PENDING" : eventStatus);

                detailRow++;
                detailCount++;
            }
            file2.close();

            if (detailCount == 0)
            {
                gotoxy(35, 10);
                cout << "No active events found.";
            }
            else if (activeEvents > detailCount)
            {
                gotoxy(15, detailRow + 1);
                cout << "Showing " << detailCount << " of " << activeEvents << " active events";
            }

            gotoxy(20, 28);
            cout << "Press Enter to return to Calendar Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (VBC_choice == 2)
        {
            // VIEW ALL EVENTS INCLUDING COMPLETED
            Clear_Terminal();
            Border(10, 1, 100, 30);

            gotoxy(15, 2);
            cout << string(86, '=');
            gotoxy(38, 3);
            cout << "YNARICH EMS: ALL EVENTS (INCLUDING COMPLETED)";
            gotoxy(15, 4);
            cout << string(86, '=');

            gotoxy(15, 6);
            cout << "DATE";
            gotoxy(28, 6);
            cout << "ID";
            gotoxy(35, 6);
            cout << "CLIENT NAME";
            gotoxy(55, 6);
            cout << "EVENT TYPE";
            gotoxy(72, 6);
            cout << "PAX";
            gotoxy(82, 6);
            cout << "STATUS";
            gotoxy(15, 7);
            cout << string(86, '-');

            int detailRow = 8;
            int detailCount = 0;
            const int MAX_DETAIL_ROWS = 18;

            PathResolved = ResolveCSVPath(csvToUse);
            std::ifstream file3(PathResolved);

            if (!file3.is_open())
            {
                gotoxy(15, 10);
                cout << "Error: Could not open CSV file!";
                gotoxy(20, 28);
                cout << "Press Enter to return...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            getline(file3, line_data); // Skip header

            while (getline(file3, line_data) && detailRow < 8 + MAX_DETAIL_ROWS)
            {
                if (line_data.empty())
                    continue;

                vector<string> columns = ParseCSVLine(line_data);

                string clientID = GetColumnValue(columns, 0);
                string clientName = GetColumnValue(columns, 1);
                string date = GetColumnValue(columns, 4);
                string eventType = GetColumnValue(columns, 8);
                string pax = GetColumnValue(columns, 9);
                string eventStatus = GetColumnValue(columns, 29, "PENDING");

                if (clientID.empty())
                    continue;

                // Display detailed info (show ALL events)
                gotoxy(15, detailRow);
                cout << (date.length() > 10 ? date.substr(0, 10) : date);
                gotoxy(28, detailRow);
                cout << clientID;
                gotoxy(35, detailRow);
                cout << (clientName.length() > 18 ? clientName.substr(0, 18) : clientName);
                gotoxy(55, detailRow);
                cout << (eventType.length() > 15 ? eventType.substr(0, 15) : eventType);
                gotoxy(72, detailRow);
                cout << pax;
                gotoxy(82, detailRow);
                cout << (eventStatus.empty() ? "PENDING" : eventStatus);

                detailRow++;
                detailCount++;
            }
            file3.close();

            if (detailCount == 0)
            {
                gotoxy(35, 10);
                cout << "No events found in the system.";
            }
            else if (totalEvents > detailCount)
            {
                gotoxy(15, detailRow + 1);
                cout << "Showing " << detailCount << " of " << totalEvents << " total events";
            }

            gotoxy(20, 28);
            cout << "Press Enter to return to Calendar Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (VBC_choice == 3)
        {
            gotoxy(25, row + 1);
            cout << "Returning to Main Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

    } while (true);
}