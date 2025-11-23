#include "Headers/Run_Financial.h"
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

void FinancialReportsMenu()
{
    int choice;

    do
    {
        Clear_Terminal();
        Border(10, 1, 100, 26);

        double totalEstimatedRevenue = 0.0;
        double totalRevenueReceived = 0.0;
        int totalEventsCount = 0;

        int cateringCount = 0, venueCount = 0, photoboothCount = 0, emceeCount = 0;
        double cateringRevenue = 0.0, venueRevenue = 0.0, photoboothRevenue = 0.0, emceeRevenue = 0.0;

        string PathResolved = ResolveCSVPath(csvToUse);
        std::ifstream file(PathResolved);

        if (!file.is_open())
        {
            gotoxy(15, 10);
            cout << "Error: Could not open CSV file!";
            gotoxy(20, 27);
            cout << "Press Enter to return...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        string line;
        getline(file, line); 

        while (getline(file, line))
        {
            if (line.empty()) continue;  

            std::stringstream ss(line);
            vector<string> columns;
            string cell;


            while (getline(ss, cell, ','))
            {
                columns.push_back(cell);
            }

            if (!line.empty() && line.back() == ',')
            {
                columns.push_back("");
            }

            string clientID = columns[0];
            string clientName = columns[1];
            string totalCost = columns[26];
            string cateringRate = columns[15];
            string emceeRate = columns[18];
            string photoboothRate = columns[21];
            string designRate = columns[24];
            string AmountPaid = columns[32];

            if (clientID.empty() || totalCost.empty())
                continue;
            
            // Parse total cost
            double cost = 0.0;
            cost = std::stod(totalCost);
            totalEstimatedRevenue += cost;
            totalEventsCount++;

            // Parse amount paid (semicolon-delimited)
            if (!AmountPaid.empty())
            {
                std::stringstream amountStream(AmountPaid);
                string amount;
                while (getline(amountStream, amount, ';'))
                {
                    // Trim whitespace
                    amount.erase(0, amount.find_first_not_of(" \t\n\r"));
                    amount.erase(amount.find_last_not_of(" \t\n\r") + 1);
                    
                    totalRevenueReceived += std::stod(amount);
                }
            }

            // 
            if (!cateringRate.empty() && cateringRate != "0" && cateringRate != "0.000000")
            {
                cateringCount++;
                cateringRevenue += std::stod(cateringRate);
            }
            
            // 
            if (!designRate.empty() && designRate != "0" && designRate != "0.000000")
            {
                venueCount++;
                venueRevenue += std::stod(designRate);
            }
            
            // 
            if (!photoboothRate.empty() && photoboothRate != "0" && photoboothRate != "0.000000")
            {
                photoboothCount++;
                photoboothRevenue += std::stod(photoboothRate);
            }
            
            // 
            if (!emceeRate.empty() && emceeRate != "0" && emceeRate != "0.000000")
            {
                emceeCount++;
                emceeRevenue += std::stod(emceeRate);
            }
        }
        file.close();

        double totalOutstandingBalance = totalEstimatedRevenue - totalRevenueReceived;

        gotoxy(15, 2);
        cout << string(86, '=');
        gotoxy(40, 3);
        cout << "YNARICH EMS: FINANCIAL REPORTS & ANALYTICS";
        gotoxy(15, 4);
        cout << string(86, '=');
        gotoxy(15, 7);
        cout << "--- BUSINESS SUMMARY (All Events) ---";
        gotoxy(15, 8);
        cout << string(86, '-');
        gotoxy(15, 9);
        cout << "Total Estimated Revenue (All Events):  P" << fixed << setprecision(2) << totalEstimatedRevenue;
        gotoxy(15, 10);
        cout << "Total Revenue Received (All Payments): P" << fixed << setprecision(2) << totalRevenueReceived;
        gotoxy(15, 11);
        cout << "Total Outstanding Receivables:         P" << fixed << setprecision(2) << totalOutstandingBalance;

        gotoxy(15, 13);
        cout << "REPORTS MENU";
        gotoxy(15, 14);
        cout << string(86, '-');
        gotoxy(15, 15);
        cout << "1. Outstanding Balance Report   (All events with outstanding balance)";
        gotoxy(15, 16);
        cout << "2. Service Profitability Report (Revenue earned per service type)";
        gotoxy(15, 17);
        cout << "3. Return to Main Menu";

        while (true)
        {
            gotoxy(15, 19);
            cout << "Enter Choice (1-3): ";
            gotoxy(35, 19);
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3)
            {
                cin.clear();
                Clear_Getline();
                gotoxy(15, 20);
                cout << "Invalid input. Try again...";
                ClearLine(35, 19, 30);
                continue;
            }
            break;
        }

        if (choice == 1)
        {
            // --- Outstanding Balance Report ---
            Clear_Terminal();
            Border(10, 1, 100, 30);
            gotoxy(15, 2);
            cout << string(86, '=');
            gotoxy(40, 3);
            cout << "YNARICH EMS: OUTSTANDING BALANCE REPORT";
            gotoxy(15, 4);
            cout << string(86, '=');
            gotoxy(15, 6);
            cout << "(All Events - Including Completed)";
            gotoxy(15, 7);
            cout << "CLIENT NAME";
            gotoxy(35, 7);
            cout << "PAYMENT DATE";
            gotoxy(50, 7);
            cout << "TOTAL AMOUNT";
            gotoxy(68, 7);
            cout << "AMOUNT PAID";
            gotoxy(86, 7);
            cout << "BALANCE";
            gotoxy(15, 8);
            cout << string(86, '-');

            int row = 9;
            const int MAX_ROWS = 16;
            int displayedClients = 0;

            PathResolved = ResolveCSVPath(csvToUse);
            std::ifstream file2(PathResolved);
            
            if (!file2.is_open())
            {
                gotoxy(15, 10);
                cout << "Error: Could not open CSV file!";
                gotoxy(20, 27);
                cout << "Press Enter to return...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }

            getline(file2, line); // Skip header

            while (getline(file2, line) && row < 9 + MAX_ROWS)
            {
                if (line.empty()) continue;

                std::stringstream ss(line);
                vector<string> columns;
                string cell;

                while (getline(ss, cell, ','))
                {
                    columns.push_back(cell);
                }

                if (!line.empty() && line.back() == ',')
                {
                    columns.push_back("");
                }

                string clientID = (columns.size() >= 0) ? columns[0] : "";
                string clientName = (columns.size() >= 1) ? columns[1] : "";
                string eventDate = (columns.size() >= 3) ? columns[3] : "";
                string totalCost = (columns.size() >= 26) ? columns[26] : "";
                string PaymentDate = (columns.size() >= 31) ? columns[31] : "";
                string AmountPaid = (columns.size() >= 32) ? columns[32] : "";

                if (clientID.empty() || totalCost.empty())
                    continue;

                double cost = 0.0;
                try {
                    cost = std::stod(totalCost);
                } catch (...) {
                    continue;  // Skip if cost is invalid
                }

                // Parse payment dates and amounts (both semicolon-delimited)
                vector<string> paymentDates;
                vector<double> paymentAmounts;

                if (!PaymentDate.empty())
                {
                    std::stringstream dateStream(PaymentDate);
                    string pDate;
                    while (getline(dateStream, pDate, ';'))
                    {
                        pDate.erase(0, pDate.find_first_not_of(" \t\n\r"));
                        pDate.erase(pDate.find_last_not_of(" \t\n\r") + 1);
                        if (!pDate.empty())
                        {
                            paymentDates.push_back(NormalizeDate(pDate));
                        }
                    }
                }

                if (!AmountPaid.empty())
                {
                    std::stringstream amountStream(AmountPaid);
                    string amt;
                    while (getline(amountStream, amt, ';'))
                    {
                        amt.erase(0, amt.find_first_not_of(" \t\n\r"));
                        amt.erase(amt.find_last_not_of(" \t\n\r") + 1);

                        if (!amt.empty())
                        {
                            try
                            {
                                paymentAmounts.push_back(std::stod(amt));
                            }
                            catch (...)
                            {
                                // Skip only invalid amount and continues
                            }
                        }
                    }
                }

                // Calculate total amount paid and remaining balance
                double totalPaid = 0.0;
                for (double amt : paymentAmounts)
                {
                    totalPaid += amt;
                }
                double balance = cost - totalPaid;

                // Display each payment as a separate row
                if (paymentAmounts.empty())
                {
                    // No payments made yet
                    string displayName = clientName;
                    if (displayName.length() > 18)
                    {
                        displayName = displayName.substr(0, 18);
                    }

                    gotoxy(15, row);
                    cout << displayName;
                    gotoxy(35, row);
                    cout << (eventDate.empty() ? NormalizeDate(eventDate) : "No Date");
                    gotoxy(50, row);
                    cout << "P" << fixed << setprecision(2) << cost;
                    gotoxy(68, row);
                    cout << "P0.00";
                    gotoxy(86, row);
                    cout << "P" << fixed << setprecision(2) << balance;
                    row++;
                    displayedClients++;
                }
                else
                {
                    // Display first payment with client name
                    string displayName = clientName;
                    if (displayName.length() > 18)
                    {
                        displayName = displayName.substr(0, 18);
                    }

                    gotoxy(15, row);
                    cout << displayName;
                    gotoxy(35, row);
                    cout << (paymentDates.size() > 0 ? paymentDates[0] : NormalizeDate(eventDate));
                    gotoxy(50, row);
                    cout << "P" << fixed << setprecision(2) << cost;
                    gotoxy(68, row);
                    cout << "P" << fixed << setprecision(2) << paymentAmounts[0];

                    // Only show balance on last payment row
                    if (paymentAmounts.size() == 1)
                    {
                        gotoxy(86, row);
                        cout << "P" << fixed << setprecision(2) << balance;
                    }
                    row++;
                    displayedClients++;

                    // Display subsequent payments
                    for (size_t i = 1; i < paymentAmounts.size() && row < 9 + MAX_ROWS; i++)
                    {
                        gotoxy(15, row);
                        cout << "  \"";
                        gotoxy(35, row);
                        cout << (i < paymentDates.size() ? paymentDates[i] : "");
                        gotoxy(50, row);
                        cout << "";
                        gotoxy(68, row);
                        cout << "P" << fixed << setprecision(2) << paymentAmounts[i];

                        if (i == paymentAmounts.size() - 1)
                        {
                            gotoxy(86, row);
                            cout << "P" << fixed << setprecision(2) << balance;
                        }
                        row++;
                    }
                }
            }
            file2.close();

            // Show count
            if (displayedClients == 0) {
                gotoxy(35, 12); cout << "No events found in the system.";
            } else if (totalEventsCount > displayedClients) {
                gotoxy(15, row + 1); 
                cout << "Showing " << displayedClients << " of " << totalEventsCount << " total clients";
            }

            gotoxy(20, 27);
            cout << "Press Enter to return to Financial Reports Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

        else if (choice == 2)
        {
            // --- SERVICE PROFITABILITY REPORT ---
            Clear_Terminal();
            Border(10, 1, 100, 30);
            gotoxy(15, 2);
            cout << string(86, '=');
            gotoxy(40, 3);
            cout << "YNARICH EMS: SERVICE PROFITABILITY REPORT";
            gotoxy(15, 4);
            cout << string(86, '=');

            gotoxy(15, 5);
            cout << "ALL TIME EVENTS BOOKED: " << totalEventsCount;
            gotoxy(15, 7);
            cout << "REVENUE";
            gotoxy(30, 7);
            cout << "SERVICE TYPE";
            gotoxy(51, 7);
            cout << "BOOKING RATIO";
            gotoxy(70, 7);
            cout << "TOTAL ESTIMATED REVENUE";
            gotoxy(15, 8);
            cout << string(86, '-');

            gotoxy(15, 9);
            cout << "INTERNAL";

            gotoxy(30, 10);
            cout << "CATERING";
            gotoxy(51, 10);
            cout << fixed << setprecision(1) << (totalEventsCount > 0 ? (cateringCount * 100.0 / totalEventsCount) : 0.0) << "%";
            gotoxy(70, 10);
            cout << "P" << fixed << setprecision(2) << cateringRevenue;

            gotoxy(30, 12);
            cout << "VENUE SET-UP";
            gotoxy(51, 12);
            cout << fixed << setprecision(1) << (totalEventsCount > 0 ? (venueCount * 100.0 / totalEventsCount) : 0.0) << "%";
            gotoxy(70, 12);
            cout << "P" << fixed << setprecision(2) << venueRevenue;

            gotoxy(15, 14);
            cout << "EXTERNAL";

            gotoxy(30, 15);
            cout << "PHOTOBOOTH";
            gotoxy(51, 15);
            cout << fixed << setprecision(1) << (totalEventsCount > 0 ? (photoboothCount * 100.0 / totalEventsCount) : 0.0) << "%";
            gotoxy(70, 15);
            cout << "P" << fixed << setprecision(2) << photoboothRevenue;

            gotoxy(30, 17);
            cout << "EMCEE";
            gotoxy(51, 17);
            cout << fixed << setprecision(1) << (totalEventsCount > 0 ? (emceeCount * 100.0 / totalEventsCount) : 0.0) << "%";
            gotoxy(70, 17);
            cout << "P" << fixed << setprecision(2) << emceeRevenue;

            gotoxy(20, 27);
            cout << "Press Enter to return to Financial Reports Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (choice != 3);

    gotoxy(20, 23);
    cout << "Returning to Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}