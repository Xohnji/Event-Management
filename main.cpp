// Custom Headers
#include "Headers/Globals.h"
#include "Headers/Ui_Utils.h"
#include "Headers/NewBooking.h"
#include "Headers/Payment.h"
#include "Headers/Run_Financial.h"
#include "Headers/View_Calendar.h"
#include "Headers/View_Update_Booking.h"
#include "Headers/Validators.h"
#include "Headers/CSV_Utils.h"
#include "Headers/ManageResources.h"

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



int main()
{
    while (true)
    {
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(39, 8);
        cout << "YNARICH CAKES, CATERING & PARTY NEEDS - EMS";
        gotoxy(25, 9);
        cout << line;
        gotoxy(30, 11);
        cout << "MAIN MENU";
        gotoxy(30, 13);
        cout << "[1] Create New Booking";
        gotoxy(30, 14);
        cout << "[2] View/Update Bookings";
        gotoxy(30, 15);
        cout << "[3] Manage Suppliers & Resources";
        gotoxy(30, 16);
        cout << "[4] View Booking Calendar";
        gotoxy(30, 17);
        cout << "[5] Run Financial Reports";
        gotoxy(30, 18);
        cout << "[6] Exit System";
         // input area
        gotoxy(30, 20);
        cout << "Select an option [1-6]: ";
        gotoxy(55, 20);
        cin >> MMchoice;
        
        if (cin.fail())
        {
            cin.clear();
            Clear_Getline();
            Clear_Terminal();
            gotoxy(30, 22);
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        switch (MMchoice)
        {
        case 1:
            Clear_Terminal();
            NewBooking();
            break;
        case 2:
            Clear_Terminal();
            ViewUpdateBookings();
            break;
        case 3:
            Clear_Terminal();
            ManageSuppliersANDResources();
            break;
        case 4:
            Clear_Terminal();
            View_Booking_Calendar();
            Clear_Terminal();
            break;
        case 5:
            Clear_Terminal();
            FinancialReportsMenu();
            Clear_Terminal();
            break;
        case 6:
            // Exit System
            return 0;
            break;
        default:
            Clear_Terminal();
            gotoxy(30, 22);
            cout << "Invalid choice. Please try again.\n";
            break;
        };
    }
    return 0;
}