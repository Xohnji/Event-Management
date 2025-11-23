#include "Headers/Payment.h"
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

string GetPaymentStatus(double totalPaid, double totalCost) {
    if (totalCost <= 0) return "INVALID COST";

    double paidRatio = totalPaid / totalCost;

    if (paidRatio >= 1.0)
        return "FULLY PAID (100%)";
    else if (paidRatio >= 0.9)
        return "PARTIAL FULFILLMENT (90% - 99%)";
    else if (paidRatio >= 0.5)
        return "FOLLOW-UP PAID (50%)";
    else if (paidRatio >= 0.1)
        return "DOWNPAYMENT PAID (10% - 49%)";
    else if (paidRatio > 0.0)
        return "PARTIAL DOWNPAYMENT (0% - 10%)";
    else
        return "INQUIRY (0%)";
}

void FinancialControlMenu() {

    int choice;
    do {
        Clear_Terminal();
        Border(10, 1, 100, 30);

        gotoxy(15, 2); cout << string(86, '=');
        gotoxy(45, 3); cout << "YNARICH EMS: FINANCIAL CONTROL MENU";
        gotoxy(15, 4); cout << string(86, '=');
        gotoxy(15, 5); cout << "EVENT STATUS: " << GetPaymentStatus(totalPaid, TotalServiceCost);
        gotoxy(15, 6); cout << "Total Estimated Cost: P" << TotalServiceCost;
        gotoxy(15, 7); cout << "Total Fulfilled Amount: P" << totalPaid;
        gotoxy(15, 8); cout << string(86, '-');
        
        gotoxy(15, 10); cout << "PAYMENT BREAKDOWN (10%/50%/40% STRUCTURE)";
        gotoxy(15, 11); cout << string(86, '-'); 
        gotoxy(15, 12); cout << "TIER"; gotoxy(50, 12); cout << "AMOUNT";
        gotoxy(15, 14); cout << "1] Downpayment (10%)";  gotoxy(50, 14); cout << "P" << fixed << setprecision(2) << (TotalServiceCost*.1);
        gotoxy(15, 15); cout << "2] Follow-Up (50%)";  gotoxy(50, 15); cout << "P" << fixed << setprecision(2) << (TotalServiceCost*.5);
        gotoxy(15, 16); cout << "3] Fulfillment (40%)";  gotoxy(50, 16); cout << "P" << fixed << setprecision(2) << (TotalServiceCost*.4);

        gotoxy(20, 19); cout << "FINANCIAL MENU OPTIONS";
        gotoxy(15, 20); cout << string(80, '-');
        gotoxy(20, 21); cout << "[1] Record a Payment";
        gotoxy(20, 22); cout << "[2] View Service Allocations & Detailed Breakdown";
        gotoxy(20, 23); cout << "[3] View Payment History Ledger";
        gotoxy(20, 24); cout << "[4] Return to Service Allocation Menu";

        while(true)
        {
            gotoxy(20, 26); cout << "Enter your choice: ";
            gotoxy(39, 26); cin >> choice;

            if (cin.fail() || choice < 1 || choice > 4) {
                cin.clear();
                Clear_Getline();
                gotoxy(20, 27); cout << "Invalid input. Try again...";
                ClearLine(39, 26, 30);
                continue;
            }
            break;
        }

        if (choice == 1) {
            // ----- RECORD A PAYMENT -----
            Clear_Terminal();
            Border(10, 1, 100, 30);

            gotoxy(15, 2); cout << string(86, '=');
            gotoxy(45, 3); cout << "YNARICH EMS: PAYMENT RECORDING";
            gotoxy(15, 4); cout << string(86, '=');
            gotoxy(15, 5); cout << "EVENT STATUS: " << GetPaymentStatus(totalPaid, TotalServiceCost);
            gotoxy(15, 6); cout << "Total Estimated Cost: P" << TotalServiceCost;
            gotoxy(15, 7); cout << "Total Fulfilled Amount: P" << totalPaid;
            gotoxy(15, 8); cout << string(86, '-');

            PaymentLog log;
            log.paymentID = paymentCounter++;

            gotoxy(20, 10); cout << "NEW PAYMENT";
            gotoxy(15, 11); cout << string(86, '-');
            gotoxy(20, 12); cout << "Enter payment date (MM/DD/YY): ";
            Clear_Getline();
            gotoxy(51, 12); getline(cin, log.date);

            while (!ValidateDate(log.date)) {
                ClearLine(51, 12, 30); //clear input
                gotoxy(20, 13); cout << "Invalid format. Use MM/DD/YY. Try again: ";
                gotoxy(51, 12); getline(cin, log.date);
            }

            ClearLine(20, 13, 50); //clear error message

            gotoxy(20, 13); cout << "Enter payment amount: ";
            gotoxy(42, 13); cin >> log.amount;

            while (cin.fail() || log.amount == 0) {
                cin.clear();
                Clear_Getline();
                gotoxy(20, 14); cout << "Invalid input. Please enter a valid number: ";
                ClearLine(42, 13, 30); //clear input
                gotoxy(42, 13); cin >> log.amount;
            }

            ClearLine(20, 14, 30);

            gotoxy(20, 14); cout << "Enter Remarks (Payment, Adjustment, Discount, etc.): ";
            Clear_Getline();
            gotoxy(73, 14); getline(cin, log.remarks);

            while(log.remarks.empty())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(20, 15); cout << "Empty input. Please enter remarks: ";
                ClearLine(42, 14, 40); //clear input
                gotoxy(42, 14); cin >> log.remarks;
                cin.get();
            }

            totalPaid += log.amount;
            log.status = GetPaymentStatus(totalPaid, TotalServiceCost);

            paymentHistory.push_back(log);
            PayID.push_back(log.paymentID);
            PayDate.push_back(log.date);
            PayAmount.push_back(log.amount);
            PayRemarks.push_back(log.remarks);
            PayStatus.push_back(log.status);

            gotoxy(20, 17); cout << "Payment recorded successfully.";
            gotoxy(20, 18); cout << ">> Fulfillment Balance updated to: P" << totalPaid;
            gotoxy(20, 19); cout << "   Current Payment Status: " << log.status;

            gotoxy(20, 21); cout << "Press Enter to return to Financial Control Menu";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cin.get();

        }

        else if (choice == 2) {
            // ----- VIEW SERVICE BREAKDOWN -----
            Clear_Terminal();
            Border(10, 1, 100, 30);

            gotoxy(15, 2); cout << string(86, '=');
            gotoxy(45, 3); cout << "YNARICH EMS: COST BREAKDOWN";
            gotoxy(15, 4); cout << string(86, '=');
            gotoxy(20, 6); cout << "Catering Cost (Package x PaxAmount): P" << fixed << setprecision(2) << baseCateringCost;
            gotoxy(20, 7); cout << "EMCEE Cost (Emcee Name): P" << emceeCost;
            gotoxy(20, 8); cout << "Photobooth Cost (PB Package): P" << photoboothCost;
            gotoxy(20, 9); cout << "Venue Setup Cost (Theme Name): P" << venueSetupCost;
            gotoxy(20, 10); cout << "Manual Expenses Cost: P" << manualExpenseCost;

            gotoxy(20, 12); cout << "------------------------------------------";
            gotoxy(20, 13); cout << "Total Service Cost:  P" << TotalServiceCost;
            gotoxy(20, 14); cout << "Total Paid:          P" << totalPaid;
            gotoxy(20, 15); cout << "Outstanding Balance: P" << (TotalServiceCost - totalPaid);

            gotoxy(20, 18); cout << "Press Enter to continue...";
            cin.get();
            cin.get();
        }

        else if (choice == 3) {
            // ----- VIEW PAYMENT HISTORY -----
            Clear_Terminal();
            Border(10, 1, 100, 30);

            gotoxy(15, 2); cout << string(86, '=');
            gotoxy(45, 3); cout << "YNARICH EMS: PAYMENT HISTORY";
            gotoxy(15, 4); cout << string(86, '=');

            if (paymentHistory.empty()) {
                gotoxy(20, 6); cout << "No payments recorded yet.";
            }
            else {
                gotoxy(18, 6); cout << "ID";
                gotoxy(23, 6); cout << "Date";
                gotoxy(38, 6); cout << "Amount";
                gotoxy(53, 6); cout << "Status";
                gotoxy(83, 6); cout << "Remarks";
                gotoxy(18, 7); cout << string(86, '-');

                int y = 9;
                for (const auto& p : paymentHistory) {

                    gotoxy(18, y); cout << p.paymentID;
                    gotoxy(23, y); cout << p.date;
                    gotoxy(38, y); cout << "P" << p.amount;
                    gotoxy(53, y); cout << p.status;
                    gotoxy(83, y); cout << p.remarks;
                    y++;
                }
            }

            gotoxy(20, 20); cout << "Press Enter to return to Financial Control Menu:";
            cin.get();
            cin.get();
        }

    } while (choice != 4);

    gotoxy(20, 25); cout << "Returning to Service Allocation Menu...";
    cin.get();

    cout << "Press ENTER to return to Ledger Options...";
    cin.get(); // wait for enter
    Clear_Terminal();
    
}