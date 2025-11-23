#include "Headers/NewBooking.h"
#include "Headers/Globals.h"
#include "Headers/Ui_Utils.h"
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

void NewBooking()
{
    ResetBookingData();

    Clear_Getline();
    Clear_Terminal();
    Border(20, 2, 80, 25);
    string line(71, '=');
    gotoxy(25, 4);
    cout << line;
    gotoxy(46, 5);
    cout << "YNARICH EMS: CREATE NEW EVENT";
    gotoxy(25, 6);
    cout << line;
    gotoxy(30, 7);
    cout << "CLIENT DETAILS";

    // Client Name validation - cannot be empty
    while (true)
    {
        gotoxy(30, 9);
        cout << "Enter Client Name: ";
        gotoxy(50, 9);
        getline(cin, ClientName);

        // Remove leading/trailing whitespace
        ClientName.erase(0, ClientName.find_first_not_of(" \t\n\r"));
        ClientName.erase(ClientName.find_last_not_of(" \t\n\r") + 1);

        if (!ClientName.empty())
        {
            ClearLine(30, 12, 60);
            break;
        }
        else
        {
            gotoxy(30, 12);
            cout << "Client name cannot be empty! Please enter a valid name.";
            ClearLine(50, 9, 40);
        }
    }

    // Contact Number validation
    while (true)
    {
        gotoxy(30, 10);
        cout << "Enter Contact Number: ";
        gotoxy(53, 10);
        getline(cin, ClientNum);

        // Remove whitespace
        ClientNum.erase(0, ClientNum.find_first_not_of(" \t\n\r"));
        ClientNum.erase(ClientNum.find_last_not_of(" \t\n\r") + 1);

        if (ClientNum.empty())
        {
            gotoxy(30, 12);
            cout << "Contact number cannot be empty!";
            gotoxy(30, 13);
            cout << "Must be 11 digits starting with '09'. Please try again.";
            ClearLine(53, 10, 20);
        }
        else if (ClientNum.length() == 11 && ClientNum.substr(0, 2) == "09")
        {
            // Validate all characters are digits
            bool allDigits = true;
            for (char c : ClientNum)
            {
                if (!isdigit(c))
                {
                    allDigits = false;
                    break;
                }
            }

            if (allDigits)
            {
                ClearLine(30, 12, 60);
                ClearLine(30, 13, 60);
                break;
            }
            else
            {
                gotoxy(30, 12);
                cout << "Contact number must contain only digits!";
                gotoxy(30, 13);
                cout << "Must be 11 digits starting with '09'. Please try again.";
                ClearLine(53, 10, 60);
            }
        }
        else
        {
            gotoxy(30, 12);
            cout << "Invalid contact number!";
            gotoxy(30, 13);
            cout << "Must be 11 digits starting with '09'. Please try again.";
            ClearLine(53, 10, 60);
        }
    }

    // Client Address validation - cannot be empty
    while (true)
    {
        gotoxy(30, 11);
        cout << "Enter Client Address: ";
        gotoxy(53, 11);
        getline(cin, ClientAddress);

        // Remove leading/trailing whitespace
        ClientAddress.erase(0, ClientAddress.find_first_not_of(" \t\n\r"));
        ClientAddress.erase(ClientAddress.find_last_not_of(" \t\n\r") + 1);

        if (!ClientAddress.empty())
        {
            ClearLine(30, 12, 60);
            ClearLine(30, 13, 60);
            break;
        }
        else
        {
            gotoxy(30, 12);
            cout << "Address cannot be empty! Please enter a valid address.";
            ClearLine(53, 11, 60);
        }
    }

    gotoxy(30, 13);
    cout << "EVENT DETAILS";

    // Event Type validation - cannot be empty
    while (true)
    {
        gotoxy(30, 15);
        cout << "Enter Event Type: ";
        gotoxy(49, 15);
        getline(cin, EventType);

        // Remove leading/trailing whitespace
        EventType.erase(0, EventType.find_first_not_of(" \t\n\r"));
        EventType.erase(EventType.find_last_not_of(" \t\n\r") + 1);

        if (!EventType.empty())
        {
            ClearLine(30, 17, 60);
            break;
        }
        else
        {
            gotoxy(30, 17);
            cout << "Event type cannot be empty! Please enter a valid event type.";
            ClearLine(49, 15, 40);
        }
    }

    // Event Date Validation
    while (true)
    {
        ClearLine(30, 16, 60);
        gotoxy(30, 16);
        cout << "Enter Event Date (MM/DD/YY): ";
        gotoxy(62, 16);
        getline(cin, EventDate);

        if (!Date_Checker(EventDate))
        {
            ClearLine(30, 18, 60);
            ClearLine(30, 19, 60);
            ClearLine(30, 20, 69);

            gotoxy(30, 18);
            cout << "Invalid date format.";
            gotoxy(30, 19);
            cout << "Date must be in MM/DD/YY format. Please try again.";

            ClearLine(62, 16, 20);
            continue;
        }

        ClearLine(30, 18, 60);
        ClearLine(30, 19, 60);
        ClearLine(30, 20, 69);

        // Check if date is in the past
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm *local_time = std::localtime(&now_time);

        // Parse the entered date (assuming MM/DD/YY format)
        std::tm input_tm = {};
        std::istringstream ss(EventDate);
        char delimiter;
        ss >> input_tm.tm_mon >> delimiter >> input_tm.tm_mday >> delimiter >> input_tm.tm_year;

        input_tm.tm_mon -= 1;    // Month is 0-11 in tm structure
        input_tm.tm_year += 100; // Assuming 20YY (add 100 for years 2000+)
        input_tm.tm_hour = 0;
        input_tm.tm_min = 0;
        input_tm.tm_sec = 0;

        std::time_t input_time = std::mktime(&input_tm);

        // Compare dates (ignoring time component)
        local_time->tm_hour = 0;
        local_time->tm_min = 0;
        local_time->tm_sec = 0;
        std::time_t today = std::mktime(local_time);

        if (input_time < today)
        {
            ClearLine(30, 18, 60);
            ClearLine(30, 19, 60);

            gotoxy(30, 18);
            cout << "Event Date can't be in the past, Must be in the future.";

            ClearLine(62, 16, 20);
            continue;
        }

        ClearLine(30, 18, 60);
        ClearLine(30, 19, 60);

        string resolved = ResolveCSVPath(csvToUse);
        if (!IsCSVReadable(resolved))
        {
            ClearLine(30, 22, 60);
            ClearLine(30, 24, 60);
            ClearLine(30, 25, 60);
            ClearLine(30, 26, 60);

            gotoxy(30, 22);
            cout << "Warning: Bookings CSV not readable.";
            gotoxy(30, 24);
            cout << "Enter a different CSV path/filename: ";

            gotoxy(30, 25);
            string userInput;
            getline(cin, userInput);

            if (!userInput.empty())
            {
                csvToUse = userInput;
                continue;
            }
            else
            {
                ClearLine(30, 26, 60);
                gotoxy(30, 26);
                cout << "No input entered. Please try again.";
                continue;
            }
        }

        ClearLine(30, 22, 60);
        ClearLine(30, 24, 60);
        ClearLine(30, 25, 60);
        ClearLine(30, 26, 60);

        if (IsDateTaken(NormalizeDate(EventDate), resolved))
        {
            ClearLine(30, 20, 60);
            ClearLine(30, 23, 60);

            gotoxy(30, 20);
            cout << "Entered date is already taken. Please enter another date (MM/DD/YY)";
            gotoxy(30, 23);
            ClearLine(62, 16, 20);
            continue;
        }

        ClearLine(30, 20, 69);
        ClearLine(30, 23, 60);
        break;
    }

    // Event Time validation
    while (true)
    {
        gotoxy(30, 17);
        cout << "Enter Event Time (HH:MM-HH:MM Military Time): ";
        gotoxy(76, 17);
        getline(cin, EventTime);

        // Remove leading/trailing whitespace
        EventTime.erase(0, EventTime.find_first_not_of(" \t\n\r"));
        EventTime.erase(EventTime.find_last_not_of(" \t\n\r") + 1);

        if (EventTime.empty())
        {
            ClearLine(30, 19, 60);
            ClearLine(30, 20, 60);
            ClearLine(30, 21, 69);

            gotoxy(30, 19);
            cout << "Event time cannot be empty!";
            gotoxy(30, 21);
            cout << "Time must be in HH:MM-HH:MM MILITARY TIME format. Please try again.";

            ClearLine(69, 17, 20);
            continue;
        }

        if (!Time_Checker(EventTime))
        {
            ClearLine(30, 19, 60);
            ClearLine(30, 20, 60);
            ClearLine(30, 21, 69);

            gotoxy(30, 19);
            cout << "Invalid Time Format.";
            gotoxy(30, 21);
            cout << "Time must be in HH:MM-HH:MM MILITARY TIME format. Please try again.";

            ClearLine(76, 17, 20);

            continue;
        }

        ClearLine(30, 19, 60);
        ClearLine(30, 20, 60);
        ClearLine(30, 21, 69);
        break;
    }

    // Venue validation - cannot be empty
    while (true)
    {
        gotoxy(30, 18);
        cout << "Enter Venue: ";
        gotoxy(44, 18);
        getline(cin, Venue);

        // Remove leading/trailing whitespace
        Venue.erase(0, Venue.find_first_not_of(" \t\n\r"));
        Venue.erase(Venue.find_last_not_of(" \t\n\r") + 1);

        if (!Venue.empty())
        {
            ClearLine(30, 20, 60);
            break;
        }
        else
        {
            gotoxy(30, 20);
            cout << "Venue cannot be empty! Please enter a valid venue.";
            ClearLine(44, 18, 40);
        }
    }

    // Landmarks validation - cannot be empty
    while (true)
    {
        gotoxy(30, 19);
        cout << "Enter Landmarks: ";
        gotoxy(48, 19);
        getline(cin, ClientLandmarks);

        // Remove leading/trailing whitespace
        ClientLandmarks.erase(0, ClientLandmarks.find_first_not_of(" \t\n\r"));
        ClientLandmarks.erase(ClientLandmarks.find_last_not_of(" \t\n\r") + 1);

        if (!ClientLandmarks.empty())
        {
            ClearLine(30, 21, 60);
            break;
        }
        else
        {
            gotoxy(30, 21);
            cout << "Landmarks cannot be empty! Please enter landmarks.";
            ClearLine(48, 19, 40);
        }
    }

    while (true)
    {
        gotoxy(30, 20);
        cout << "Enter Number of Pax: ";
        gotoxy(52, 20);
        cin >> PaxAmount;

        if (cin.fail() || PaxAmount < 60 || PaxAmount % 10 != 0)
        {
            gotoxy(30, 21);
            cout << "Invalid pax! Pax minimum of 60 and in multiples of 10.";

            // Clear error state and ignore invalid input
            cin.clear();
            Clear_Getline();

            // Clear previous input
            ClearLine(52, 20, 10);
        }
        else
        {
            // Clear any previous error messages
            ClearLine(30, 21, 60);
            break;
        }
    }
    Clear_Getline();
    gotoxy(30, 22);
    cout << "Event Successfully Created - Client ID: " << ClientID;
    gotoxy(30, 23);
    cout << "Press Enter to proceed to Service Allocation Menu...";
    cin.get();
    ServiceAllocationMenu();
}

void ResetBookingData()
{
    // Reset client information
    ClientName.clear();
    ClientNum.clear();
    ClientAddress.clear();
    EventType.clear();
    EventDate.clear();
    EventTime.clear();
    Venue.clear();
    ClientLandmarks.clear();
    PaxAmount = 0;

    // Reset costs
    TotalServiceCost = 0.0;
    baseCateringCost = 0.0;
    emceeCost = 0.0;
    photoboothCost = 0.0;
    venueSetupCost = 0.0;
    manualExpenseCost = 0.0;

    // Clear catering selections
    chosenEntrees.clear();
    chosenAppetizers.clear();
    chosenDrinks.clear();
    chosenDesserts.clear();

    // Clear emcee selections
    chosenEmcee.clear();
    chosenEmceeRate.clear();

    // Clear photobooth selections
    chosenPhotoboothPackage.clear();
    chosenPhotoboothRate.clear();

    // Clear venue setup selections
    designNotes.clear();
    chosendesignCost.clear();

    // Clear manual expenses
    manualExpenseEntry.clear();
    manualExpenseAmount.clear();

    // Reset payment data
    paymentHistory.clear();
    PayID.clear();
    PayDate.clear();
    PayAmount.clear();
    PayRemarks.clear();
    PayStatus.clear();
    totalPaid = 0.0;
    paymentCounter = 0;
}

void ServiceAllocationMenu()
{
    Clear_Terminal();

    while (true)
    {
        Border(20, 4, 80, 23);
        string line(71, '=');

        // Header
        gotoxy(25, 6);
        cout << line;
        gotoxy(35, 7);
        cout << "YNARICH EMS: SERVICE ALLOCATION MENU";
        gotoxy(25, 8);
        cout << line;

        // Current cost display
        gotoxy(30, 11);
        cout << "Current Estimated Total Cost: P" << fixed << setprecision(2) << TotalServiceCost;

        // Menu options
        gotoxy(30, 13);
        cout << "[1] Catering";
        gotoxy(30, 14);
        cout << "[2] Emcee (Supplier-Based)";
        gotoxy(30, 15);
        cout << "[3] Photobooth (Supplier-Based)";
        gotoxy(30, 16);
        cout << "[4] Venue Set-Up / Stage Decoration";
        gotoxy(30, 17);
        cout << "[5] Add Manual Expense (Cakes, Equipment, Labor)";
        gotoxy(30, 18);
        cout << "[6] View/Process Payments";
        gotoxy(30, 19);
        cout << "[7] Save & Return to Main Menu";

        // Input

        gotoxy(30, 21);
        cout << "Select a service option [1-7]: ";
        gotoxy(62, 21);
        cin >> SAchoice;

        if (cin.fail())
        {
            cin.clear();
            Clear_Getline();
            gotoxy(30, 22);
            cout << "Invalid input! Please enter a number.";
            ClearLine(62, 21, 10);
            continue;
        }

        if (SAchoice >= 1 && SAchoice <= 7)
        {
            // Clear any previous error messages
            ClearLine(30, 22, 60);
        }
        else
        {
            gotoxy(30, 22);
            cout << "Invalid choice! Please select a valid option.";

            // Clear previous input
            ClearLine(62, 21, 10);
            continue;
        }
        switch (SAchoice)
        {
        case 1:
            Clear_Terminal();
            CateringMenu();
            Clear_Terminal();
            break;
        case 2:
            Clear_Terminal();
            EmceeMenu();
            Clear_Terminal();
            break;
        case 3:
            Clear_Terminal();
            PhotoboothMenu();
            Clear_Terminal();
            break;
        case 4:
            Clear_Terminal();
            VenueSetupMenu();
            Clear_Terminal();
            break;
        case 5:
            Clear_Terminal();
            ManualExpenseLedger();
            Clear_Terminal();
            break;
        case 6:
            Clear_Terminal();
            FinancialControlMenu();
            break;
        case 7:
            Clear_Terminal();
            AppendToCSV(csvToUse);
            cout << "\nSaving and returning to Main Menu...\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            Clear_Terminal();
            return;
        }
    }
}

void CateringMenu()
{
    size_t row;
    char confirmChoice;
    string chosenCateringPackage;

    Clear_Terminal();
    Border(10, 1, 99, 30);

    // CHECK IF CATERING IS ALREADY SELECTED
    if (!chosenCateringPackage.empty())
    {
        Clear_Terminal();
        Border(10, 1, 99, 30);

        gotoxy(15, 2);
        cout << string(86, '=');
        gotoxy(42, 3);
        cout << "YNARICH EMS: CATERING MENU SELECTION";
        gotoxy(15, 4);
        cout << string(86, '=');

        gotoxy(18, 7);
        cout << "!!! WARNING: You have already selected a catering package!";
        gotoxy(18, 9);
        cout << "Current Selection: " << chosenCateringPackage;
        gotoxy(18, 10);
        cout << "Current Rate: P" << fixed << setprecision(2) << baseCateringCost;

        char changeChoice;
        while (true)
        {
            gotoxy(18, 12);
            cout << "Do you want to change your catering selection? [Y/N]: ";
            gotoxy(71, 12);
            cin >> changeChoice;
            changeChoice = toupper(changeChoice);

            if (changeChoice == 'Y' || changeChoice == 'N')
                break;

            gotoxy(18, 14);
            cout << "Invalid input! Please enter 'Y' or 'N'.";
            ClearLine(71, 12, 10);
        }

        if (changeChoice == 'N')
        {
            gotoxy(18, 16);
            cout << "Returning to Service Allocation Menu...";
            gotoxy(18, 17);
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        chosenCateringPackage.clear();
        chosenEntrees.clear();
        chosenAppetizers.clear();
        chosenDrinks.clear();
        chosenDesserts.clear();
        TotalServiceCost -= baseCateringCost;
        baseCateringCost = 0.0;
    }

    string line(86, '=');
    gotoxy(15, 2);
    cout << line;
    gotoxy(42, 3);
    cout << "YNARICH EMS: CATERING MENU SELECTION";
    gotoxy(15, 4);
    cout << line;

    // LOAD PACKAGES FROM CSV
    const string packageFile = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Catering_package.csv";
    vector<CateringPackage> cateringList = loadCateringFromCSV(packageFile);

    if (cateringList.empty())
    {
        gotoxy(18, 6);
        cout << "ERROR: No catering packages found in CSV!";
        gotoxy(18, 7);
        cout << "Press Enter to return to Service Allocation Menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // LOAD MENU ITEMS FROM CSV
    const string menuFile = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\CATERING_Menu.csv";
    vector<CateringMenuItem> menuItems = loadCateringMenuFromCSV(menuFile);

    // ORGANIZE MENU ITEMS BY CATEGORY
    vector<string> entreeList, appetizerList, drinkList, dessertList;

    for (const auto &item : menuItems)
    {
        string catLower = item.category;
        transform(catLower.begin(), catLower.end(), catLower.begin(), ::tolower);

        if (catLower == "entree" || catLower == "entrees")
            entreeList.push_back(item.itemName);
        else if (catLower == "appetizer" || catLower == "appetizers")
            appetizerList.push_back(item.itemName);
        else if (catLower == "drink" || catLower == "drinks" || catLower == "beverage" || catLower == "beverages")
            drinkList.push_back(item.itemName);
        else if (catLower == "dessert" || catLower == "desserts")
            dessertList.push_back(item.itemName);
    }

    // DISPLAY PACKAGE SELECTION
    gotoxy(18, 6);
    cout << "CURRENT ESTIMATED TOTAL (Pre-Catering): P" << fixed << setprecision(2) << TotalServiceCost;
    gotoxy(15, 7);
    cout << string(86, '-');

    int y = 9;
    for (size_t i = 0; i < cateringList.size(); ++i)
    {
        gotoxy(18, y);
        cout << "[" << (i + 1) << "] " << cateringList[i].name;
        gotoxy(25, y + 1);
        cout << "Rate: P" << fixed << setprecision(2) << cateringList[i].ratePerPax << " per pax";
        gotoxy(25, y + 2);
        cout << "Includes: " << cateringList[i].description;
        y += 4;
    }
    gotoxy(15, y);
    cout << string(86, '-');

    // PACKAGE CHOICE
    int choice;
    while (true)
    {
        gotoxy(18, y + 2);
        cout << "Enter Package Choice [1-" << cateringList.size() << "]: ";
        gotoxy(46, y + 2);
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > (int)cateringList.size())
        {
            cin.clear();
            Clear_Getline();
            gotoxy(18, y + 4);
            cout << "Invalid input! Please enter a valid package number.";
            ClearLine(46, y + 2, 10);
            continue;
        }
        break;
    }

    CateringPackage selectedCatering = cateringList[choice - 1];
    chosenCateringPackage = selectedCatering.name;
    baseCateringCost = selectedCatering.ratePerPax * PaxAmount;
    TotalServiceCost += baseCateringCost;

    ClearLine(18, y + 4, 55);
    gotoxy(18, y + 4);
    cout << ">> " << selectedCatering.name << " selected: P" << selectedCatering.ratePerPax << " x " << PaxAmount << " Pax";
    gotoxy(18, y + 5);
    cout << "   Catering Subtotal: P" << fixed << setprecision(2) << baseCateringCost;
    gotoxy(18, y + 6);
    cout << "   Current Estimated Total Cost: P" << fixed << setprecision(2) << TotalServiceCost;

    gotoxy(18, y + 7);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cin.clear();

    int input;

    do
    {
        chosenEntrees.clear();
        chosenAppetizers.clear();
        chosenDrinks.clear();
        chosenDesserts.clear();

        Clear_Terminal();
        Border(10, 1, 99, 45);
        gotoxy(15, 2);
        cout << line;
        gotoxy(43, 3);
        cout << "YNARICH EMS: CATERING MENU SELECTION";
        gotoxy(15, 4);
        cout << line;
        gotoxy(18, 6);
        cout << "Includes " << selectedCatering.entreeCount << " Entrees, " << selectedCatering.appetizerCount << " Appetizer(s), "
             << selectedCatering.beverageCount << " Drink(s), " << selectedCatering.dessertCount << " Dessert(s)";

        gotoxy(23, 8);
        cout << "CATEGORY";
        gotoxy(65, 8);
        cout << "MENU";
        gotoxy(15, 9);
        cout << string(86, '-');

        row = 10;

        // DISPLAY ENTREE MENU FROM CSV
        if (!entreeList.empty())
        {
            gotoxy(23, row);
            cout << "ENTREES";

            for (size_t i = 0; i < entreeList.size(); i += 2)
            {
                gotoxy(38, row);
                cout << "[" << (i + 1) << "] " << entreeList[i];

                if (i + 1 < entreeList.size())
                {
                    gotoxy(70, row);
                    cout << "[" << (i + 2) << "] " << entreeList[i + 1];
                }
                row++;
            }
            row += 2;
        }

        // DISPLAY APPETIZER MENU FROM CSV
        if (!appetizerList.empty())
        {
            gotoxy(23, row);
            cout << "APPETIZERS";

            for (size_t i = 0; i < appetizerList.size(); i += 2)
            {
                gotoxy(38, row);
                cout << "[" << (i + 1) << "] " << appetizerList[i];

                if (i + 1 < appetizerList.size())
                {
                    gotoxy(70, row);
                    cout << "[" << (i + 2) << "] " << appetizerList[i + 1];
                }
                row++;
            }
            row += 2;
        }

        // DISPLAY DRINK MENU FROM CSV
        if (!drinkList.empty())
        {
            gotoxy(23, row);
            cout << "BEVERAGES";

            for (size_t i = 0; i < drinkList.size(); i += 2)
            {
                gotoxy(38, row);
                cout << "[" << (i + 1) << "] " << drinkList[i];

                if (i + 1 < drinkList.size())
                {
                    gotoxy(70, row);
                    cout << "[" << (i + 2) << "] " << drinkList[i + 1];
                }
                row++;
            }
            row += 2;
        }

        // DISPLAY DESSERT MENU FROM CSV
        if (!dessertList.empty())
        {
            gotoxy(23, row);
            cout << "DESSERTS";

            for (size_t i = 0; i < dessertList.size(); i += 2)
            {
                gotoxy(38, row);
                cout << "[" << (i + 1) << "] " << dessertList[i];

                if (i + 1 < dessertList.size())
                {
                    gotoxy(70, row);
                    cout << "[" << (i + 2) << "] " << dessertList[i + 1];
                }
                row++;
            }
            row += 2;
        }

        gotoxy(15, row);
        cout << string(86, '-');
        row++;

        // ENTREE SELECTION
        for (int i = 0; i < selectedCatering.entreeCount; ++i)
        {
            gotoxy(18, row);
            cout << "Enter Entree #" << (i + 1) << " [1-" << entreeList.size() << "]: ";
            gotoxy(42, row);
            cin >> input;

            if (cin.fail() || input < 1 || input > (int)entreeList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(18, row + 1);
                cout << "Invalid input! Please try again.";
                ClearLine(42, row, 10);
                i--;
                row--;
            }
            else
            {
                ClearLine(18, row + 1, 40);
                gotoxy(44, row);
                cout << entreeList[input - 1] << " selected.";
                chosenEntrees.push_back(entreeList[input - 1]);
            }
            row++;
        }

        // APPETIZER SELECTION
        for (int i = 0; i < selectedCatering.appetizerCount; ++i)
        {
            gotoxy(18, row);
            cout << "Enter Appetizer #" << (i + 1) << " [1-" << appetizerList.size() << "]: ";
            gotoxy(45, row);
            cin >> input;

            if (cin.fail() || input < 1 || input > (int)appetizerList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(18, row + 1);
                cout << "Invalid input! Please try again.";
                ClearLine(45, row, 10);
                i--;
                row--;
            }
            else
            {
                ClearLine(18, row + 1, 40);
                gotoxy(47, row);
                cout << appetizerList[input - 1] << " selected.";
                chosenAppetizers.push_back(appetizerList[input - 1]);
            }
            row++;
        }

        // DRINKS SELECTION
        for (int i = 0; i < selectedCatering.beverageCount; ++i)
        {
            gotoxy(18, row);
            cout << "Enter Beverage #" << (i + 1) << " [1-" << drinkList.size() << "]: ";
            gotoxy(44, row);
            cin >> input;

            if (cin.fail() || input < 1 || input > (int)drinkList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(18, row + 1);
                cout << "Invalid input! Please try again.";
                ClearLine(44, row, 10);
                i--;
                row--;
            }
            else
            {
                ClearLine(18, row + 1, 40);
                gotoxy(46, row);
                cout << drinkList[input - 1] << " selected.";
                chosenDrinks.push_back(drinkList[input - 1]);
            }
            row++;
        }

        // DESSERTS SELECTION
        for (int i = 0; i < selectedCatering.dessertCount; ++i)
        {
            gotoxy(18, row);
            cout << "Enter Dessert #" << (i + 1) << " [1-" << dessertList.size() << "]: ";
            gotoxy(43, row);
            cin >> input;

            if (cin.fail() || input < 1 || input > (int)dessertList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(18, row + 1);
                cout << "Invalid input! Please try again.";
                ClearLine(43, row, 10);
                i--;
                row--;
            }
            else
            {
                ClearLine(18, row + 1, 40);
                gotoxy(45, row);
                cout << dessertList[input - 1] << " selected.";
                chosenDesserts.push_back(dessertList[input - 1]);
            }
            row++;
        }

        while (true)
        {
            gotoxy(18, row + 1);
            cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(53, row + 1);
            cin >> confirmChoice;

            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(18, row + 3);
            cout << "Invalid input! Please type C or E.";
            ClearLine(53, row + 1, 30);
        }

    } while (confirmChoice == 'E' || confirmChoice == 'e');

    ClearLine(18, row + 3, 30);
    gotoxy(18, row + 3);
    cout << "Catering confirmed. Press Enter to return to Service Allocation Menu";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void EmceeMenu()
{
    char confirmChoice;
    int EMchoice;
    int y;

    const string emceeFile = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Emcee.csv";
    vector<Emcee> EmceeList = loadEmceesFromCSV(emceeFile);

    if (EmceeList.empty())
    {
        Clear_Terminal();
        Border(10, 1, 99, 26);
        gotoxy(13, 6);
        cout << "ERROR: No emcees found in CSV!";
        gotoxy(13, 7);
        cout << "Press Enter to return to Service Allocation Menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // CHECK IF EMCEE IS ALREADY SELECTED
    if (!chosenEmcee.empty())
    {
        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(40, 3);
        cout << "YNARICH EMS: EMCEE SELECTION MENU";
        gotoxy(15, 4);
        cout << line;

        gotoxy(13, 6);
        cout << "!!! WARNING: You have already selected an emcee!";
        gotoxy(13, 8);
        cout << "Current Selection: " << chosenEmcee[0];
        gotoxy(13, 9);
        cout << "Current Rate: P" << fixed << setprecision(2) << chosenEmceeRate[0];

        char changeChoice;
        while (true)
        {
            gotoxy(13, 11);
            cout << "Do you want to change your emcee selection? [Y/N]: ";
            gotoxy(64, 11);
            cin >> changeChoice;
            changeChoice = toupper(changeChoice);

            if (changeChoice == 'Y' || changeChoice == 'N')
                break;

            gotoxy(13, 13);
            cout << "Invalid choice! Please enter 'Y' or 'N'.";
            ClearLine(64, 11, 20);
        }

        if (changeChoice == 'N')
        {
            gotoxy(13, 13);
            cout << "Returning to Service Allocation Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        emceeCost -= chosenEmceeRate[0];
        TotalServiceCost -= chosenEmceeRate[0];
        chosenEmcee.clear();
        chosenEmceeRate.clear();
    }

    double previousEmceeRate = 0.0;

    do
    {
        y = 10;

        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(40, 3);
        cout << "YNARICH EMS: EMCEE SELECTION MENU";
        gotoxy(15, 4);
        cout << line;

        gotoxy(13, 6);
        cout << "AVAILABLE EMCEES:";
        string line2(90, '-');
        gotoxy(13, 7);
        cout << line2;

        gotoxy(13, 8);
        cout << "No.";
        gotoxy(30, 8);
        cout << "Emcee Name";
        gotoxy(70, 8);
        cout << "Rate";
        gotoxy(13, 9);
        cout << line2;

        for (size_t i = 0; i < EmceeList.size(); ++i)
        {
            gotoxy(13, y);
            cout << "[" << (i + 1) << "]";
            gotoxy(30, y);
            cout << EmceeList[i].name;
            gotoxy(70, y);
            cout << "P" << fixed << setprecision(2) << EmceeList[i].rate;
            y++;
        }

        gotoxy(30, y);
        cout << "[0] Cancel & Back to Service Allocation Menu";
        gotoxy(13, y + 1);
        cout << line2;

        while (true)
        {
            gotoxy(13, y + 3);
            cout << "Select Emcee [0-" << EmceeList.size() << "] (0 to go back): ";
            gotoxy(48, y + 3);
            cin >> EMchoice;

            if (cin.fail() || EMchoice < 0 || EMchoice > (int)EmceeList.size())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                gotoxy(13, y + 5);
                cout << "Invalid input! Please enter a valid number.";
                ClearLine(48, y + 3, 20);
                continue;
            }

            ClearLine(13, y + 5, 60);

            if (EMchoice == 0)
            {
                gotoxy(13, y + 5);
                cout << "Returning to Service Allocation Menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                return;
            }

            string selectedEmcee = EmceeList[EMchoice - 1].name;
            double selectedEmceeRate = EmceeList[EMchoice - 1].rate;

            if (previousEmceeRate != 0)
            {
                emceeCost -= previousEmceeRate;
                TotalServiceCost -= previousEmceeRate;
            }

            previousEmceeRate = selectedEmceeRate;

            chosenEmcee.clear();
            chosenEmceeRate.clear();
            chosenEmcee.push_back(selectedEmcee);
            chosenEmceeRate.push_back(selectedEmceeRate);
            emceeCost += selectedEmceeRate;
            TotalServiceCost += selectedEmceeRate;

            gotoxy(13, y + 5);
            cout << ">> You selected " << selectedEmcee
                 << " - P" << fixed << setprecision(2) << selectedEmceeRate;
            break;
        }

        gotoxy(13, y + 7);
        cout << "Current Estimated Total Cost: P"
             << fixed << setprecision(2) << TotalServiceCost;

        while (true)
        {
            gotoxy(13, y + 9);
            cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(47, y + 9);
            cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(13, y + 11);
            cout << "Invalid choice! Please enter 'C' to Confirm or 'E' to Edit.";
            ClearLine(47, y + 9, 20);
        }

    } while (confirmChoice == 'E');

    gotoxy(13, y + 11);
    cout << "Emcee confirmed. Press Enter to return to Service Allocation Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void PhotoboothMenu()
{
    char confirmChoice;
    int PBchoice;
    int y;

    // LOAD PHOTOBOOTHS FROM CSV
    const string photoboothFile = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Photobooth.csv";
    vector<Photobooth> PBList = loadPhotoboothsFromCSV(photoboothFile);

    if (PBList.empty())
    {
        Clear_Terminal();
        Border(10, 1, 99, 26);
        gotoxy(13, 6);
        cout << "ERROR: No photobooth packages found in CSV!";
        gotoxy(13, 7);
        cout << "Press Enter to return to Service Allocation Menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // CHECK IF PHOTOBOOTH IS ALREADY SELECTED
    if (!chosenPhotoboothPackage.empty())
    {
        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(40, 3);
        cout << "YNARICH EMS: PHOTOBOOTH SELECTION MENU";
        gotoxy(15, 4);
        cout << line;

        gotoxy(13, 6);
        cout << "!!! WARNING: You have already selected a photobooth package!";
        gotoxy(13, 8);
        cout << "Current Selection: " << chosenPhotoboothPackage[0];
        gotoxy(13, 9);
        cout << "Current Rate: P" << fixed << setprecision(2) << chosenPhotoboothRate[0];

        char changeChoice;
        while (true)
        {
            gotoxy(13, 11);
            cout << "Do you want to change your photobooth selection? [Y/N]: ";
            gotoxy(69, 11);
            cin >> changeChoice;
            changeChoice = toupper(changeChoice);

            if (changeChoice == 'Y' || changeChoice == 'N')
                break;

            gotoxy(13, 13);
            cout << "Invalid choice! Please enter 'Y' or 'N'.";
            ClearLine(69, 11, 20);
        }

        if (changeChoice == 'N')
        {
            gotoxy(13, 13);
            cout << "Returning to Service Allocation Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        photoboothCost -= chosenPhotoboothRate[0];
        TotalServiceCost -= chosenPhotoboothRate[0];
        chosenPhotoboothPackage.clear();
        chosenPhotoboothRate.clear();
    }

    double previousPBRate = 0.0;

    do
    {
        y = 10;

        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(40, 3);
        cout << "YNARICH EMS: PHOTOBOOTH SELECTION MENU";
        gotoxy(15, 4);
        cout << line;

        gotoxy(13, 6);
        cout << "AVAILABLE PHOTOBOOTH PACKAGES:";
        string line2(90, '-');
        gotoxy(13, 7);
        cout << line2;

        gotoxy(13, 8);
        cout << "No.";
        gotoxy(30, 8);
        cout << "Package";
        gotoxy(80, 8);
        cout << "Rate";
        gotoxy(13, 9);
        cout << line2;

        for (size_t i = 0; i < PBList.size(); ++i)
        {
            gotoxy(13, y);
            cout << "[" << (i + 1) << "]";
            gotoxy(30, y);
            cout << PBList[i].name;
            gotoxy(80, y);
            cout << "P" << fixed << setprecision(2) << PBList[i].rate;
            y++;
        }

        gotoxy(13, y + 1);
        cout << line2;

        while (true)
        {
            gotoxy(13, y + 3);
            cout << "Select Photobooth Package [1-" << PBList.size() << "]: ";
            gotoxy(46, y + 3);
            cin >> PBchoice;

            if (cin.fail() || PBchoice < 1 || PBchoice > (int)PBList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(13, y + 5);
                cout << "Invalid input! Please enter a valid number.";
                ClearLine(46, y + 3, 20);
                continue;
            }

            ClearLine(13, y + 5, 60);

            if (previousPBRate != 0)
            {
                photoboothCost -= previousPBRate;
                TotalServiceCost -= previousPBRate;
            }

            string selectedPhotobooth = PBList[PBchoice - 1].name;
            double selectedPBRate = PBList[PBchoice - 1].rate;

            previousPBRate = selectedPBRate;

            chosenPhotoboothPackage.clear();
            chosenPhotoboothRate.clear();
            chosenPhotoboothPackage.push_back(selectedPhotobooth);
            chosenPhotoboothRate.push_back(selectedPBRate);
            photoboothCost += selectedPBRate;
            TotalServiceCost += selectedPBRate;

            gotoxy(13, y + 5);
            cout << ">> You selected " << selectedPhotobooth
                 << " - P" << fixed << setprecision(2) << selectedPBRate;
            break;
        }

        gotoxy(13, y + 7);
        cout << "Current Estimated Total Cost: P"
             << fixed << setprecision(2) << TotalServiceCost;

        while (true)
        {
            gotoxy(13, y + 9);
            cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(47, y + 9);
            cin >> confirmChoice;

            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(13, y + 11);
            cout << "Invalid choice! Please enter 'C' to Confirm or 'E' to Edit.";
            ClearLine(47, y + 9, 20);
        }

    } while (confirmChoice == 'E');

    gotoxy(13, y + 11);
    cout << "Photobooth confirmed. Press Enter to return to Service Allocation Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void VenueSetupMenu()
{
    // CHECK IF VENUE SETUP IS ALREADY SELECTED
    if (!designNotes.empty() || !chosendesignCost.empty())
    {
        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(38, 3);
        cout << "YNARICH EMS: VENUE SETUP AND DESIGN MENU";
        gotoxy(15, 4);
        cout << line;

        gotoxy(13, 6);
        cout << "!!! WARNING: You have already set up venue design!";
        gotoxy(13, 8);
        cout << "Current Theme: " << (designNotes.empty() ? "None" : designNotes[0]);
        gotoxy(13, 9);
        cout << "Current Cost: P" << fixed << setprecision(2) << venueSetupCost;

        char changeChoice;
        while (true)
        {
            gotoxy(13, 11);
            cout << "Do you want to change your venue setup? [Y/N]: ";
            gotoxy(61, 11);
            cin >> changeChoice;
            changeChoice = toupper(changeChoice);

            if (changeChoice == 'Y' || changeChoice == 'N')
                break;

            gotoxy(13, 13);
            cout << "Invalid choice! Please enter 'Y' or 'N'.";
            ClearLine(61, 11, 20);
        }

        if (changeChoice == 'N')
        {
            gotoxy(13, 13);
            cout << "Returning to Service Allocation Menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }

        TotalServiceCost -= venueSetupCost;
        designNotes.clear();
        chosendesignCost.clear();
        venueSetupCost = 0.0;
    }

    Clear_Getline();
    Clear_Terminal();
    Border(10, 1, 99, 25);
    string line(90, '=');
    gotoxy(15, 2);
    cout << line;
    gotoxy(38, 3);
    cout << "YNARICH EMS: VENUE SETUP AND DESIGN MENU";
    gotoxy(15, 4);
    cout << line;
    gotoxy(13, 6);
    cout << "Current Estimated Total Cost: P" << fixed << setprecision(2) << TotalServiceCost;
    gotoxy(13, 8);
    cout << "THEME";

    string themeTitle;
    // EMPTY INPUT VALIDATION FOR THEME
    while (true)
    {
        gotoxy(13, 10);
        cout << "Enter THEME Title (e.g., Rustic Chic): ";
        gotoxy(52, 10);
        getline(cin, themeTitle);
        
        // Trim whitespace
        themeTitle.erase(0, themeTitle.find_first_not_of(" \t\n\r"));
        themeTitle.erase(themeTitle.find_last_not_of(" \t\n\r") + 1);
        
        if (themeTitle.empty())
        {
            gotoxy(13, 11);
            cout << "ERROR: Theme title cannot be empty! Please enter a valid theme.";
            ClearLine(52, 10, 50);
            continue;
        }
        break;
    }

    int y = 14;

    designNotes.push_back("Theme: " + themeTitle);

    ClearLine(13, 11, 70);
    gotoxy(13, y + 1);
    cout << "---- COST ALLOCATION ----";
    gotoxy(13, y + 3);
    cout << "Enter Flat Fee for Design Labor & Materials: P";

    double designCost;
    while (true)
    {
        gotoxy(60, y + 3);
        cin >> designCost;
        if (cin.fail() || designCost < 0)
        {
            cin.clear();
            Clear_Getline();
            gotoxy(13, y + 4);
            cout << "Invalid input! Please enter a valid number.";
            ClearLine(60, y + 3, 20);
            continue;
        }
        break;
    }

    Clear_Getline();

    chosendesignCost.push_back(designCost);
    venueSetupCost = designCost;
    TotalServiceCost += designCost;

    gotoxy(13, y + 6);
    cout << ">> Design Notes saved successfully.";
    gotoxy(13, y + 7);
    cout << ">> SERVICE COST ADDED: P" << fixed << setprecision(2) << designCost;
    gotoxy(13, y + 8);
    cout << ">> NEW ESTIMATED TOTAL: P" << fixed << setprecision(2) << TotalServiceCost;
    string line2(90, '-');
    gotoxy(13, y + 9);
    cout << line2;
    gotoxy(13, y + 10);
    cout << "Press ENTER to return to Service Allocation Menu...";
    cin.get();
}

void ManualExpenseLedger()
{
    int MEchoice, ExpenseAmount;
    string ExpenseEntry;

    while (true)
    {
        Clear_Terminal();
        Border(10, 1, 99, 50);

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(43, 3);
        cout << "YNARICH EMS: MANUAL EXPENSE LEDGER";
        gotoxy(15, 4);
        cout << line;

        gotoxy(13, 6);
        cout << "Current Estimated Total Cost: P"
             << fixed << setprecision(2) << TotalServiceCost;
        gotoxy(13, 7);
        cout << "Current Manual Expenses Logged: P"
             << fixed << setprecision(2) << manualExpenseCost;

        string line2(90, '-');
        gotoxy(13, 9);
        cout << "LEDGER OPTIONS:";
        gotoxy(13, 10);
        cout << line2;
        gotoxy(13, 11);
        cout << "[1] Add New Expense Entry";
        gotoxy(13, 12);
        cout << "[2] Return to Service Allocation Menu";

        gotoxy(13, 14);
        cout << "Select an option [1-2]: ";

        while (true)
        {
            gotoxy(37, 14);
            cin >> MEchoice;

            if (cin.fail() || MEchoice < 1 || MEchoice > 2)
            {
                cin.clear();
                Clear_Getline();
                gotoxy(13, 15);
                cout << "Invalid input! Please enter 1 or 2.";
                ClearLine(37, 14, 5);
                continue;
            }
            break;
        }

        ClearLine(13, 15, 30);

        Clear_Getline();

        if (MEchoice == 2)
        {
            return;
        }

        Clear_Terminal();
        Border(15, 2, 85, 20);
        string line3(76, '=');
        gotoxy(20, 3);
        cout << line3;
        gotoxy(39, 4);
        cout << "YNARICH EMS: ADDING NEW EXPENSE ENTRY";
        gotoxy(20, 5);
        cout << line3;

        gotoxy(25, 8);
        cout << "Enter Expense Description: ";
        gotoxy(52, 8);
        getline(cin, ExpenseEntry);

        gotoxy(25, 11);
        cout << "Enter Amount: P";
        while (true)
        {
            gotoxy(40, 11);
            cin >> ExpenseAmount;
            if (cin.fail() || ExpenseAmount < 0)
            {
                cin.clear();
                Clear_Getline();
                gotoxy(25, 12);
                cout << "Invalid input! Please enter a positive number.";
                ClearLine(40, 11, 15);
                continue;
            }
            break;
        }

        ClearLine(25, 12, 55);

        Clear_Getline();

        manualExpenseCost += ExpenseAmount;
        TotalServiceCost += ExpenseAmount;

        manualExpenseEntry.push_back(ExpenseEntry);
        manualExpenseAmount.push_back(ExpenseAmount);

        gotoxy(25, 13);
        cout << ">> New Manual Expense (P" << fixed << setprecision(2)
             << ExpenseAmount << ") added.";
        gotoxy(25, 14);
        cout << ">> Total Manual Expense updated to P"
             << fixed << setprecision(2) << manualExpenseCost;
        gotoxy(25, 15);
        cout << ">> New Estimated Total Cost: P"
             << fixed << setprecision(2) << TotalServiceCost;
        gotoxy(25, 17);
        cout << "Press Enter to continue...";
        cin.get();
    }
}