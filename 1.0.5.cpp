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

// Database (CSV) linking || Put the CSV File Directory here!
string csvToUse = ("C:\\Users\\Axel Carl Nadera\\Desktop\\CP1-project\\Mock_Data.csv");

// Global Variables
int MMchoice; // Main Menu choice variable
int SAchoice; // Service Allocation Menu choice variable

// Client Information Variables
string ClientName, ClientNum, ClientAddress;

// Event Details Variables
string EventType, EventDate, EventTime, Venue, ClientLandmarks;
int PaxAmount;

int ClientID = 10; // Placeholder Client ID

// Service Allocation Variable
double TotalServiceCost = 0.0;

// Global Initialization for chosen menu items storage
vector<string> chosenMainDish;
vector<string> chosenDrinks;
vector<string> chosenAppetizers;
vector<string> chosenDesserts;
vector<string> chosenEmcee;
vector<double> chosenEmceeRate;
vector<string> chosenPhotoboothPackage;
vector<double> chosenPhotoboothPackagePrice;
vector<string> designNotes;

// Catering Variables
int PackageChoice;
int MainDishCounter, DrinksCounter, DessertsCounter, AppetizersCounter, i;
string Package, EntreeChoice;
float BaseCateringCost = 0;
int CMchoice; // Catering menu choice variable

// Manual Expense Variables
string ExpenseEntry, ExpenseDate;
double ExpenseAmount = 0.0, TotalExpenseAmount = 0.0; // FIXED: Initialize TotalExpenseAmount
int MEchoice;

// Venue Setup Variables
double VenueSetupCost = 0.0; // FIXED: Added variable to track venue setup cost

// Function Prototypes
void Clear_Terminal();
void Clear_Getline();
void ClearLine(int x, int y, int length);
void gotoxy(int x, int y);
void Border(int left, int top, int width, int height);
void verticalLine(int x, int yStart, int yEnd);
void drawVerticalBars(int y, const vector<int> &xPositions);
// New Booking
void NewBooking();
void ServiceAllocationMenu();
void ChoosePackage();
void CateringMenu();
void EmceeMenu();
void PhotoboothMenu();
void VenueSetupMenu();
void ManualExpenseLedger();
// append
void AppendToCSV(const string &csvToUse);
// Update/View
void ViewUpdateBookings();
void Service_Allocation_Menu();
// Manage suppliers & Resources
void ManageSuppliersANDResources();
void ManageEmcee();
void ManagePhotobooth();
void ManageCateringItems();
void ManageDecorations();
// Calendar Viewer
void View_Booking_Calendar();
// Validators/Checkers
bool Date_Checker(const string &dateStr);
bool Time_Checker(const string &timeStr);
string ResolveCSVPath(const string &csvPath);
string NormalizeDate(const string &dateStr);
bool IsCSVReadable(const string &csvPath);
bool IsDateTaken(const string &dateStr, const string &csvPath);
void AppendBookingToCSV(const string &csvPath);

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
            // Manage Suppliers & Resources
            break;
        case 4:
            Clear_Terminal();
            View_Booking_Calendar();
            Clear_Terminal();
            break;
        case 5:
            Clear_Terminal();
            // Run Financial Reports
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

// Design Functions
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ClearLine(int x, int y, int length)
{
    gotoxy(x, y);
    cout << string(length, ' '); // overwrite with spaces
}

void Border(int left, int top, int width, int height)
{
    // Draw corners
    gotoxy(left, top);
    cout << "O";
    gotoxy(left + width, top);
    cout << "O";
    gotoxy(left, top + height);
    cout << "O";
    gotoxy(left + width, top + height);
    cout << "O";

    // Draw top and bottom edges
    for (int x = left + 1; x < left + width; x++)
    {
        gotoxy(x, top);
        cout << "-";
        gotoxy(x, top + height);
        cout << "-";
    }

    // Draw left and right edges
    for (int y = top + 1; y < top + height; y++)
    {
        gotoxy(left, y);
        cout << "|";
        gotoxy(left + width, y);
        cout << "|";
    }
}

// Clear Terminal Function
void Clear_Terminal()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Clear Getline Input Buffer
void Clear_Getline()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void verticalLine(int x, int yStart, int yEnd)
{
    for (int y = yStart; y <= yEnd; ++y)
    {
        gotoxy(x, y);
        cout << "|";
    }
}

void drawVerticalBars(int y, const vector<int> &xPositions)
{
    for (int x : xPositions)
    {
        gotoxy(x, y);
        cout << "|";
    }
}

void NewBooking()
{
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



    // CLIENT NAME INPUT (WITH HANDLING)
    gotoxy(30, 9);
    cout << "Enter Client Name: ";
    gotoxy(49, 9);
    getline(cin, ClientName);
    while (ClientName.empty())
    {
        ClearLine(49, 9, 30);
        gotoxy(30, 10);
        cout << "Client name cannot be empty.";
        gotoxy(49, 9);
        getline(cin, ClientName);
    }
        ClearLine(30, 10, 60);


    // CLIENT NUM (WITH HANDLING)
    while (true)
    {
        gotoxy(30, 10);
        cout << "Enter Contact Number: ";
        gotoxy(53, 10);
        getline(cin, ClientNum);

        if (ClientNum.length() == 11 && ClientNum.substr(0, 2) == "09")
        {
            // Clear any previous error messages
            ClearLine(30, 12, 60);
            ClearLine(30, 13, 60);
            break;
        }
        else
        {
            gotoxy(30, 12);
            cout << "Invalid contact number!";
            gotoxy(30, 13);
            cout << "Must be 11 digits starting with '09'. Please try again.";

            // Clear previous input
            ClearLine(53, 10, 20);
        }
    }


    // ADDRESS INPUT (WITH HANDLING)
    gotoxy(30, 11);
    cout << "Enter Client Address: ";
    gotoxy(52, 11);
    getline(cin, ClientAddress);
    while (ClientAddress.empty())
    {
        ClearLine(52, 11, 30);
        gotoxy(30, 12);
        cout << "Client Address cannot be empty.";
        gotoxy(52, 11);
        getline(cin, ClientAddress);
    }
    ClearLine(30, 12, 60);


    gotoxy(30, 13);
    cout << "EVENT DETAILS";

    // EVENT TYPE INPUT (WITH HANDLING)
    gotoxy(30, 15);
    cout << "Enter Event Type: ";
    gotoxy(49, 15);
    getline(cin, EventType);
    while (EventType.empty())
    {
        ClearLine(49, 15, 30);
        gotoxy(30, 16);
        cout << "Event type cannot be empty.";
        gotoxy(49, 15);
        getline(cin, EventType);
    }
    ClearLine(30, 16, 60);


    // EVENT DATE VALIDATION (WITH HANDLING)
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

    while (true)
    { // Time validation
        gotoxy(30, 17);
        cout << "Enter Event Time (HH:MM-HH:MM AM/PM): ";
        gotoxy(69, 17);
        getline(cin, EventTime);

        if (!Time_Checker(EventTime))
        {
            ClearLine(30, 19, 60);
            ClearLine(30, 20, 60);
            ClearLine(30, 21, 69);

            gotoxy(30, 19);
            cout << "Invalid Time Format.";
            gotoxy(30, 21);
            cout << "Time must be in HH:MM-HH:MM AM/PM format. please try again.";

            ClearLine(69, 17, 20);

            continue;
        }
        ClearLine(30, 19, 60);
        ClearLine(30, 20, 60);
        ClearLine(30, 21, 69);
        break;
    }

    // VENUE INPUT (WITH HANDLING)
    gotoxy(30, 18);
    cout << "Enter Venue: ";
    gotoxy(44, 18);
    getline(cin, Venue);
    while (Venue.empty())
    {
        ClearLine(44, 18, 30);
        gotoxy(30, 20);
        cout << "Venue cannot be empty.";
        gotoxy(44, 18);
        getline(cin, Venue);
    }
    ClearLine(30, 20, 60);


    // LANDMARKS INPUT (WITH HANDLING)
    gotoxy(30, 19);
    cout << "Enter Landmarks: ";
    gotoxy(48, 19);
    getline(cin, ClientLandmarks);
    while (ClientLandmarks.empty())
    {
        ClearLine(48, 19, 30);
        gotoxy(30, 20);
        cout << "Landmarks cannot be empty.";
        gotoxy(48, 19);
        getline(cin, ClientLandmarks);
    }
    ClearLine(30, 20, 60);


    // PAX NUMBER INPUT (WITH HANDLING)
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
    cout << "Event Successfully Created - Client ID: " << ClientID; // FIXED: Display actual ClientID
    gotoxy(30, 23);
    cout << "Press Enter to proceed to Service Allocation Menu...";
    cin.get();
    ServiceAllocationMenu();
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
        cout << "Current Estimated Total Cost: P" << fixed << setprecision(2) << TotalServiceCost; // FIXED: Added formatting

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
            continue; // FIXED: Added continue to retry
        }
        switch (SAchoice)
        {
        case 1:
            Clear_Terminal();
            ChoosePackage();
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

void ChoosePackage()
{
    Clear_Terminal();
    Border(20, 2, 80, 25); // Draws a bordered box

    string line(71, '=');
    gotoxy(25, 4);
    cout << line;
    gotoxy(41, 5);
    cout << "YNARICH EMS: CATERING PACKAGE SELECTION";
    gotoxy(25, 6);
    cout << line;
    gotoxy(30, 8);
    cout << "CURRENT ESTIMATED TOTAL (Pre-Catering): P" << fixed << setprecision(2) << TotalServiceCost; // FIXED: Changed from BaseCateringCost
    gotoxy(30, 10);
    cout << "[1] BRONZE Package (P400.00/pax)";
    gotoxy(33, 11);
    cout << "- Includes: 1 Appetizer, 2 Entrees,";
    gotoxy(45, 12);
    cout << "1 Beverage, 1 Dessert, Standard Service.";
    gotoxy(30, 14);
    cout << "[2] SILVER Package (P580.00/pax)";
    gotoxy(33, 15);
    cout << "- Includes: 2 Appetizers, 3 Entrees,";
    gotoxy(45, 16);
    cout << "2 Beverages, 2 Desserts, Full Service.";

    while (true)
    {
        gotoxy(30, 18);
        cout << "Enter Package Choice [1-2]: ";
        gotoxy(58, 18);
        cin >> PackageChoice;

        if (cin.fail())
        {
            cin.clear();     // reset input state
            Clear_Getline(); // discard invalid input
            gotoxy(30, 21);
            cout << "Invalid input! Please enter numbers only [1-2].";
            ClearLine(58, 18, 40); // clear input area for retry
            continue;
        }

        // ===== Valid numeric input =====
        if (PackageChoice == 1)
        {
            BaseCateringCost = 400 * PaxAmount;
            MainDishCounter = 2;
            DrinksCounter = 1;
            AppetizersCounter = 1;
            DessertsCounter = 1;
            gotoxy(30, 19);
            cout << ">> BRONZE Package Selected: P400.00 x " << PaxAmount << " Pax";
            break;
        }
        else if (PackageChoice == 2)
        {
            BaseCateringCost = 580 * PaxAmount;
            MainDishCounter = 3;
            DrinksCounter = 2;
            AppetizersCounter = 2;
            DessertsCounter = 2;
            gotoxy(30, 19);
            cout << ">> SILVER Package Selected: P580.00 x " << PaxAmount << " Pax";
            break;
        }
        else
        {
            ClearLine(30, 21, 60); // Clear previous invalid package message
            gotoxy(30, 21);
            cout << "Invalid choice! Please try again [1-2].";
            ClearLine(58, 18, 5);
        }
    }

    ClearLine(30, 21, 60); // Clear any previous error messages
    gotoxy(30, 21);
    cout << "Catering Subtotal (Base): P" << fixed << setprecision(2) << BaseCateringCost;

    TotalServiceCost += BaseCateringCost; // Update total service cost

    gotoxy(30, 23);
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void CateringMenu()
{
    char confirmChoice;

    do
    { // Clear previous selections
        chosenMainDish.clear();
        chosenAppetizers.clear();
        chosenDrinks.clear();
        chosenDesserts.clear();

        Clear_Terminal();
        if (PackageChoice == 1)
        {
            Border(10, 1, 99, 27);
        }
        else
        {
            Border(10, 1, 99, 30);
        }

        string line(90, '=');
        gotoxy(15, 2);
        cout << line;
        gotoxy(42, 3);
        cout << "YNARICH EMS: CATERING MENU SELECTION";
        gotoxy(15, 4);
        cout << line;
        gotoxy(23, 5);
        cout << "CATEGORY";
        gotoxy(70, 5);
        cout << "MENU";
        string line2(90, '-');
        gotoxy(15, 6);
        cout << line2;

        gotoxy(20, 7);
        cout << "Poultry Entrees";
        gotoxy(45, 7);
        cout << "[1] Roasted Herb Chicken";
        gotoxy(76, 7);
        cout << "[2] Chicken Cordon Bleu";

        gotoxy(20, 8);
        cout << "Beef/Pork Entrees";
        gotoxy(45, 8);
        cout << "[3] Honey-Glazed Ham";
        gotoxy(76, 8);
        cout << "[4] Roast Beef Tenderloin";

        gotoxy(20, 9);
        cout << "Seafood Entrees";
        gotoxy(45, 9);
        cout << "[5] Butter Tilapia Fillets";
        gotoxy(76, 9);
        cout << "[6] Pan-Seared Sea Bass";

        gotoxy(20, 11);
        cout << "Appetizers";
        gotoxy(45, 11);
        cout << "[1] Spring Rolls";
        gotoxy(76, 11);
        cout << "[2] Stuffed Mushrooms";
        gotoxy(45, 12);
        cout << "[3] Dumplings";
        gotoxy(76, 12);
        cout << "[4] Honey Crisps";

        gotoxy(20, 14);
        cout << "Beverages";
        gotoxy(45, 14);
        cout << "[1] Red Iced Tea";
        gotoxy(76, 14);
        cout << "[2] Blue Lemonade";

        gotoxy(20, 16);
        cout << "Desserts";
        gotoxy(45, 16);
        cout << "[1] Chocolate Brownies";
        gotoxy(76, 16);
        cout << "[3] Cheesecake Bites";
        gotoxy(45, 17);
        cout << "[2] Mini Egg Tarts";
        gotoxy(76, 17);
        cout << "[4] Creme Brulee";
        gotoxy(15, 18);
        cout << line2;

        // ===== MAIN ENTREES SELECTION =====
        for (i = 1; i <= MainDishCounter; i++)
        {
            gotoxy(20, 18 + i);
            cout << "Enter Entree #" << i << " [1-6]: ";
            ClearLine(44, 18 + i, 2); // Clear previous input area
            gotoxy(44, 18 + i);
            cin >> CMchoice;

            // Error Handling for Non-Numeric Input
            if (cin.fail())
            {
                cin.clear();     // reset error flag
                Clear_Getline(); // discard bad input
                gotoxy(46, 18 + i);
                cout << "Invalid input! Numbers only.";
                i--; // repeat same entree number
                continue;
            }

            switch (CMchoice)
            {
            case 1:
                ClearLine(46, 18 + i, 45); // Clear previous error message
                gotoxy(46, 18 + i);
                cout << "Roasted Herb Chicken selected.";
                chosenMainDish.push_back("Roasted Herb Chicken");
                break;

            case 2:
                ClearLine(46, 18 + i, 45);
                gotoxy(46, 18 + i);
                cout << "Chicken Cordon Bleu selected."; // FIXED: Was showing "Honey-Glazed Ham"
                chosenMainDish.push_back("Chicken Cordon Bleu");
                break;

            case 3:
                ClearLine(46, 18 + i, 45);
                gotoxy(46, 18 + i);
                cout << "Honey-Glazed Ham selected."; // FIXED: Was showing "Butter Tilapia Fillets"
                chosenMainDish.push_back("Honey-Glazed Ham");
                break;

            case 4:
                ClearLine(46, 18 + i, 45);
                gotoxy(46, 18 + i);
                cout << "Roast Beef Tenderloin selected."; // FIXED: Was showing "Chicken Cordon Bleu"
                chosenMainDish.push_back("Roast Beef Tenderloin");
                break;

            case 5:
                ClearLine(46, 18 + i, 45);
                gotoxy(46, 18 + i);
                cout << "Butter Tilapia Fillets selected."; // FIXED: Was showing "Roast Beef Tenderloin"
                chosenMainDish.push_back("Butter Tilapia Fillets");
                break;

            case 6:
                ClearLine(46, 18 + i, 45);
                gotoxy(46, 18 + i);
                cout << "Pan-Seared Sea Bass selected.";
                chosenMainDish.push_back("Pan-Seared Sea Bass");
                break;

            default:
                ClearLine(46, 18 + i, 45);
                gotoxy(46, 18 + i);
                cout << "Invalid choice! Try Again";
                ClearLine(44, 18 + i, 2);
                i--;
                break;
            }
        }

        int n; // initializing n for dynamic line positioning

        // ===== APPETIZERS SELECTION =====
        for (i = 1; i <= AppetizersCounter; i++)
        {
            if (PackageChoice == 1)
            {
                n = 20;
            }
            else
            {
                n = 21;
            }

            gotoxy(20, n + i);
            cout << "Enter Appetizer #" << i << " [1-4]: ";
            ClearLine(47, n + i, 2); // Clear previous input area
            gotoxy(47, n + i);
            cin >> CMchoice;

            // Error Handling for Non-Numeric Input
            if (cin.fail())
            {
                cin.clear();     // reset error flag
                Clear_Getline(); // discard bad input
                gotoxy(49, n + i);
                cout << "Invalid input! Numbers only.";
                i--; // repeat same entree number
                continue;
            }

            switch (CMchoice)
            {
            case 1:
                ClearLine(49, n + i, 45); // Clear previous error message
                gotoxy(49, n + i);
                cout << "Spring Rolls selected.";
                chosenAppetizers.push_back("Spring Rolls");
                break;

            case 2:
                ClearLine(49, n + i, 45);
                gotoxy(49, n + i);
                cout << "Stuffed Mushrooms selected.";
                chosenAppetizers.push_back("Stuffed Mushrooms");
                break;

            case 3:
                ClearLine(49, n + i, 45);
                gotoxy(49, n + i);
                cout << "Dumplings selected.";
                chosenAppetizers.push_back("Dumplings");
                break;

            case 4:
                ClearLine(49, n + i, 45);
                gotoxy(49, n + i);
                cout << "Honey Crisps selected.";
                chosenAppetizers.push_back("Honey Crisps");
                break;

            default:
                ClearLine(49, n + i, 45);
                gotoxy(49, n + i);
                cout << "Invalid choice! Try Again";
                ClearLine(47, n + i, 2);
                i--;
                break;
            }
        }

        // ===== BEVERAGES SELECTION =====
        for (i = 1; i <= DrinksCounter; i++)
        {
            if (PackageChoice == 1)
            {
                n = 21;
            }
            else
            {
                n = 23;
            }

            gotoxy(20, n + i);
            cout << "Enter Beverage #" << i << " [1-2]: ";
            ClearLine(46, n + i, 2); // Clear previous input area
            gotoxy(46, n + i);
            cin >> CMchoice;

            // Error Handling for Non-Numeric Input
            if (cin.fail())
            {
                cin.clear();     // reset error flag
                Clear_Getline(); // discard bad input
                gotoxy(48, n + i);
                cout << "Invalid input! Numbers only.";
                i--; // repeat same entree number
                continue;
            }

            switch (CMchoice)
            {
            case 1:
                ClearLine(48, n + i, 45); // Clear previous error message
                gotoxy(48, n + i);
                cout << "Red Iced Tea selected.";
                chosenDrinks.push_back("Red Iced Tea");
                break;

            case 2:
                ClearLine(48, n + i, 45);
                gotoxy(48, n + i);
                cout << "Blue Lemonade selected.";
                chosenDrinks.push_back("Blue Lemonade");
                break;

            default:
                ClearLine(48, n + i, 45);
                gotoxy(48, n + i);
                cout << "Invalid choice! Try Again";
                ClearLine(46, n + i, 2);
                i--;
                break;
            }
        }

        // ===== DESSERTS SELECTION =====
        for (i = 1; i <= DessertsCounter; i++)
        {
            if (PackageChoice == 1)
            {
                n = 22;
            }
            else
            {
                n = 25;
            }
            gotoxy(20, n + i);
            cout << "Enter Dessert #" << i << " [1-4]: ";
            ClearLine(44, n + i, 2); // Clear previous input area
            gotoxy(44, n + i);
            cin >> CMchoice;

            // Error Handling for Non-Numeric Input
            if (cin.fail())
            {
                cin.clear();     // reset error flag
                Clear_Getline(); // discard bad input
                gotoxy(46, n + i);
                cout << "Invalid input! Numbers only.";
                i--; // repeat same entree number
                continue;
            }

            switch (CMchoice)
            {
            case 1:
                ClearLine(46, n + i, 45); // Clear previous error message
                gotoxy(46, n + i);
                cout << "Chocolate Brownies selected.";
                chosenDesserts.push_back("Chocolate Brownies");
                break;

            case 2:
                ClearLine(46, n + i, 45);
                gotoxy(46, n + i);
                cout << "Mini Egg Tarts selected.";
                chosenDesserts.push_back("Mini Egg Tarts");
                break;

            case 3:
                ClearLine(46, n + i, 45);
                gotoxy(46, n + i);
                cout << "Cheesecake Bites selected.";
                chosenDesserts.push_back("Cheesecake Bites");
                break;

            case 4:
                ClearLine(46, n + i, 45);
                gotoxy(46, n + i);
                cout << "Creme Brulee selected.";
                chosenDesserts.push_back("Creme Brulee");
                break;

            default:
                ClearLine(46, n + i, 45);
                gotoxy(46, n + i);
                cout << "Invalid choice! Try Again";
                ClearLine(44, n + i, 2);
                i--;
                break;
            }
        }

        while (true)
        {
            gotoxy(20, n + i + 1);
            cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(55, n + i + 1);
            cin >> confirmChoice;

            // Convert to uppercase for easier comparison
            confirmChoice = toupper(confirmChoice);

            // Check if input is valid
            if (confirmChoice == 'C' || confirmChoice == 'E')
                break; // valid input, exit loop

            // Invalid input handling
            gotoxy(20, n + i + 2);
            cout << "Invalid input! Please type C or E.";
            ClearLine(55, n + i + 1, 30); // clear input area
        }

    } while (confirmChoice == 'E' || confirmChoice == 'e');
}

void EmceeMenu()
{
    char confirmChoice;
    int EMchoice;
    double EMexpense = 0;
    int y = 10; // for dynamic line positioning

    // FIXED: Use global vectors instead of local ones
    // vector<string> chosenEmcee;
    // vector<double> chosenEmceeRate;

    // Temporary emcee data
    vector<string> EmceeNames = {"Rico Hernandez", "Mara Dela Cruz", "Kevin Santos"};
    vector<double> EmceeRates = {3000.00, 4500.00, 6000.00};

    do
    {
        chosenEmcee.clear();
        chosenEmceeRate.clear();
        EMexpense = 0; // FIXED: Reset expense when editing

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

        y = 10; // FIXED: Reset y position

        for (size_t i = 0; i < EmceeNames.size(); ++i)
        {
            gotoxy(13, y);
            cout << "[" << (i + 1) << "]";
            gotoxy(30, y);
            cout << EmceeNames[i];
            gotoxy(70, y);
            cout << "P" << fixed << setprecision(2) << EmceeRates[i];
            y++;
        }

        gotoxy(13, y + 1);
        cout << line2;

        while (true)
        {
            gotoxy(13, y + 3);
            cout << "Select Emcee [1-" << EmceeNames.size() << "]: ";
            gotoxy(40, y + 3); // FIXED: Adjusted position
            cin >> EMchoice;

            if (cin.fail() || EMchoice < 1 || EMchoice > (int)EmceeNames.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(13, y + 5);
                cout << "Invalid input! Please enter a valid number.";
                ClearLine(40, y + 3, 20);
                continue;
            }

            ClearLine(13, y + 5, 60);

            string selectedEmcee = EmceeNames[EMchoice - 1];
            double selectedRate = EmceeRates[EMchoice - 1];

            chosenEmcee.push_back(selectedEmcee);
            chosenEmceeRate.push_back(selectedRate);
            EMexpense += selectedRate;

            gotoxy(13, y + 5);
            cout << ">> You selected " << selectedEmcee
                 << " - P" << fixed << setprecision(2) << selectedRate;
            break;
        }

        gotoxy(13, y + 7);
        cout << "Emcee Cost: P" << fixed << setprecision(2) << EMexpense;
        gotoxy(13, y + 8);
        cout << "New Estimated Total Cost: P"
             << fixed << setprecision(2) << (TotalServiceCost + EMexpense);

        while (true)
        {
            gotoxy(13, y + 10);
            cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(47, y + 10);
            cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(13, y + 12);
            cout << "Invalid choice! Please enter 'C' to Confirm or 'E' to Edit.";
            ClearLine(47, y + 10, 20);
        }

        // FIXED: Only add to total if confirming, not when editing
        if (confirmChoice == 'E')
        {
            // Don't add to total yet, will re-select
            continue;
        }

    } while (confirmChoice == 'E');

    // FIXED: Add to total only after confirmation
    TotalServiceCost += EMexpense;

    gotoxy(13, y + 12);
    cout << "Emcee confirmed. Press Enter to return to Service Allocation Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void PhotoboothMenu()
{
    char confirmChoice;
    int PBchoice;
    double PBexpense = 0;
    int y = 10; // for dynamic line positioning

    // FIXED: Use global vectors instead of local ones
    // vector<string> chosenPhotoboothPackage;
    // vector<double> chosenPhotoboothPackagePrice;

    // Temporary Photobooth package data
    vector<string> PBPackages = {
        "Basic Package (2 Hours, 500 Prints)",
        "Standard Package (3 Hours, Unlimited Prints)",
        "Premium Package (Full Event, Unlimited Prints)"};

    vector<double> PBRates = {2500.00, 4000.00, 6500.00};

    do
    {
        chosenPhotoboothPackage.clear();
        chosenPhotoboothPackagePrice.clear();
        PBexpense = 0; // FIXED: Reset expense when editing

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

        y = 10; // FIXED: Reset y position

        for (size_t i = 0; i < PBPackages.size(); ++i)
        {
            gotoxy(13, y);
            cout << "[" << (i + 1) << "]";
            gotoxy(30, y);
            cout << PBPackages[i];
            gotoxy(80, y);
            cout << "P" << fixed << setprecision(2) << PBRates[i];
            y++;
        }

        gotoxy(13, y + 1);
        cout << line2;

        while (true)
        {
            gotoxy(13, y + 3);
            cout << "Select Photobooth Package [1-" << PBPackages.size() << "]: ";
            gotoxy(53, y + 3); // FIXED: Adjusted position
            cin >> PBchoice;

            if (cin.fail() || PBchoice < 1 || PBchoice > (int)PBPackages.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(13, y + 5);
                cout << "Invalid input! Please enter a valid number.";
                ClearLine(53, y + 3, 20);
                continue;
            }

            ClearLine(13, y + 5, 60);

            string selectedPackage = PBPackages[PBchoice - 1];
            double selectedRate = PBRates[PBchoice - 1];

            chosenPhotoboothPackage.push_back(selectedPackage);
            chosenPhotoboothPackagePrice.push_back(selectedRate);
            PBexpense += selectedRate;

            gotoxy(13, y + 5);
            cout << ">> You selected " << selectedPackage
                 << " - P" << fixed << setprecision(2) << selectedRate;
            break;
        }

        gotoxy(13, y + 7);
        cout << "Photobooth Cost: P" << fixed << setprecision(2) << PBexpense;
        gotoxy(13, y + 8);
        cout << "New Estimated Total Cost: P"
             << fixed << setprecision(2) << (TotalServiceCost + PBexpense);

        while (true)
        {
            gotoxy(13, y + 10);
            cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(47, y + 10);
            cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(13, y + 12);
            cout << "Invalid choice! Please enter 'C' to Confirm or 'E' to Edit.";
            ClearLine(47, y + 10, 20);
        }

        // FIXED: Only add to total if confirming, not when editing
        if (confirmChoice == 'E')
        {
            continue;
        }

    } while (confirmChoice == 'E');

    // FIXED: Add to total only after confirmation
    TotalServiceCost += PBexpense;

    gotoxy(13, y + 12);
    cout << "Photobooth confirmed. Press Enter to return to Service Allocation Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void VenueSetupMenu()
{
    Clear_Getline(); // FIXED: Clear input buffer before getline
    Clear_Terminal();
    Border(10, 1, 99, 50);
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
    cout << "THEME & DESIGN NOTES";

    string themeTitle;
    gotoxy(13, 10);
    cout << "Enter THEME Title (e.g., Rustic Chic): ";
    gotoxy(52, 10);
    getline(cin, themeTitle);

    gotoxy(13, 11);
    cout << "Enter detailed SET DESIGN / VENUE SET-UP Notes:";
    gotoxy(13, 12);
    cout << "(Type 'DONE' on a new line when finished)";

    // Gather multiline notes
    designNotes.clear(); // FIXED: Clear previous notes
    string note;
    int y = 14;
    
    // FIXED: Add theme title as first note
    if (!themeTitle.empty())
    {
        designNotes.push_back("Theme: " + themeTitle);
    }
    
    while (true)
    {
        gotoxy(15, y++);
        getline(cin, note);
        if (note == "DONE" || note == "done")
            break;
        if (!note.empty()) // FIXED: Only add non-empty notes
            designNotes.push_back(note);
    }

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

    // Clear input buffer
    Clear_Getline();

    // Save data
    VenueSetupCost = designCost; // FIXED: Store in variable
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
    while (true)
    {
        Clear_Terminal(); // ensures no residual text before showing menu
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
             << fixed << setprecision(2) << TotalExpenseAmount;

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

        // Expense List Load Below From CSV

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
                ClearLine(37, 14, 5); // clears wrong input only
                continue;
            }
            break;
        }

        ClearLine(13, 15, 30);

        Clear_Getline(); // clear newline

        if (MEchoice == 2)
        {
            // exit back to service allocation
            return;
        }

        // --- ADD NEW EXPENSE ENTRY ---
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


        // removed date entry (Not needed due to the date being entered earlier in booking)

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

        Clear_Getline(); // clear newline

        // --- UPDATE TOTALS ---
        TotalExpenseAmount += ExpenseAmount;
        TotalServiceCost += ExpenseAmount;

        // (append to vector or CSV here)

        gotoxy(25, 13);
        cout << ">> New Manual Expense (P" << fixed << setprecision(2)
             << ExpenseAmount << ") added.";
        gotoxy(25, 14);
        cout << ">> Total Manual Expense updated to P"
             << fixed << setprecision(2) << TotalExpenseAmount;
        gotoxy(25, 15);
        cout << ">> New Estimated Total Cost: P"
             << fixed << setprecision(2) << TotalServiceCost;
        gotoxy(25, 17);
        cout << "Press ENTER to return to Ledger Options...";
        cin.get(); // wait for enter
    }
}

// View Calendar
void View_Booking_Calendar()
{
    int left = 20, top = 1, width = 96, height = 25;
    Border(left, top, width, height);

    std::string line(71, '=');
    gotoxy(33, 3);
    std::cout << line;
    gotoxy(49, 4);
    std::cout << "MAIN MENU: 4. VIEW BOOKING CALENDAR";
    gotoxy(33, 5);
    std::cout << line;

    gotoxy(33, 6);
    std::cout << "Current Date: ";
    
    // FIXED: Add actual current date display
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* local_time = std::localtime(&now_time);
    gotoxy(47, 6);
    std::cout << std::put_time(local_time, "%m/%d/%Y");

    gotoxy(49, 9);
    std::cout << "--- CONFIRMED & PENDING EVENT SCHEDULE ---";
    gotoxy(25, 10);
    std::cout << "---------------------------------------------------------------------------------------";
    gotoxy(25, 11);
    std::cout << "|   DATE   | EVENT ID  |      CLIENT NAME      |         STATUS        |  TOTAL GUEST |";
    gotoxy(25, 12);
    std::cout << "|----------|-----------|-----------------------|-----------------------|--------------|";
    gotoxy(25, 13);
    std::cout << "|          |           |                       |                       |              |";

    gotoxy(25, 17);
    std::cout << "--- CALENDAR ACTIONS ---";
    gotoxy(25, 18);
    std::cout << "1. View All Inquiries";
    gotoxy(25, 19);
    std::cout << "2. Return to Main Menu";
    gotoxy(25, 20);
    std::cout << "3. Bye";
    gotoxy(25, 22);
    std::cout << "Enter Choice (1-3): ";

    gotoxy(46, 22);
    int VBC_choice;
    std::cin >> VBC_choice;
    
    // FIXED: Add input validation
    if (cin.fail())
    {
        cin.clear();
        Clear_Getline();
        gotoxy(25, 24);
        std::cout << "Invalid input! Press Enter to continue...";
        std::cin.get();
        View_Booking_Calendar();
        return;
    }

    switch (VBC_choice)
    {
    case 1:
        gotoxy(25, 24);
        std::cout << "Nothing to see here for now...";
        Clear_Getline();
        std::cin.get();
        View_Booking_Calendar();
        break;

    case 2:
        gotoxy(25, 24);
        std::cout << "Nothing to see here for now...";
        Clear_Getline();
        std::cin.get();
        View_Booking_Calendar();
        break;

    case 3:
        gotoxy(25, 24);
        std::cout << "Return back";
        Clear_Getline();
        std::cin.get();
        break;

    default:
        gotoxy(25, 24);
        std::cout << "Invalid choice! Please try again.";
        Clear_Getline();
        std::cin.get();
        View_Booking_Calendar();
        break;
    }
}

// View/Update
void ViewUpdateBookings()
{
    bool running = true;

    while (running)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');

        gotoxy(25, 7);
        cout << line;
        verticalLine(25, 8, 8);
        gotoxy(39, 8);
        cout << "EVENT DASHBOARD: VIEW/UPDATE BOOKED EVENTS";
        verticalLine(95, 8, 8);
        gotoxy(25, 9);
        cout << line;
        gotoxy(25, 10);
        cout << "Total Active Events: 3";
        gotoxy(25, 12);
        cout << "---Event Listing---";

        gotoxy(25, 13);
        cout << "| OPT | CLIENT NAME | EVENT TYPE | DATE | STATUS | OUTSTANDING BALANCE |";
        gotoxy(25, 14);
        cout << string(71, '-');

        // Placeholder data
        gotoxy(25, 15);
        cout << "[1] | John Doe   | Birthday  | 2023-10-15 | Confirmed | PHP 5000.00 |";
        gotoxy(25, 16);
        cout << "[2] | Jane Smith | Wedding   | 2023-12-01 | Pending   | PHP 10000.00 |";

        gotoxy(25, 18);
        cout << "---ACTION OPTIONS---";
        gotoxy(22, 20);
        cout << "Enter option [1-9] to Select Event or [M] to return to Main Menu:";
        gotoxy(88, 20);
        cout << "[ ]";
        gotoxy(89, 20);

        char option;
        cin >> option;

        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        option = toupper(option);

        switch (option)
        {
        case '1':
            Clear_Terminal();
            // Nothing yet
            break;
        case '2':
            Clear_Terminal();
            Service_Allocation_Menu();
            break;

        case 'M':
            running = false;
            Clear_Terminal();
            break;

        default:
            Clear_Terminal();
            gotoxy(30, 22);
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        if (running && option != 'M')
        {
            gotoxy(30, 22);
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void Service_Allocation_Menu()
{
    bool inMenu = true;

    while (inMenu)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');

        gotoxy(25, 7);
        cout << line;
        verticalLine(25, 8, 8);
        gotoxy(26, 8);
        cout << "Event ID 123: Name (Placeholder PX)";
        verticalLine(95, 8, 8);
        gotoxy(25, 9);
        cout << line;

        gotoxy(25, 10);
        cout << "Client Name: Placeholder | Event Date: Placeholder";
        gotoxy(25, 11);
        cout << "Current Estimated Total Cost: PHP 15,000.00";

        gotoxy(25, 13);
        cout << "--- SERVICE ALLOCATION MENU (Master Control) ---";
        gotoxy(25, 14);
        cout << "[1] (EDIT/VIEW) Catering (Current Cost: P6,000.00)";
        gotoxy(25, 15);
        cout << "[2] GO TO FINANCIAL CONTROL & PAYMENTS";
        gotoxy(25, 16);
        cout << "[3] Save & Return to Main Menu";

        gotoxy(25, 19);
        cout << "Enter Choice (1-3): ";
        char option;
        cin >> option;

        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option)
        {
        case '1':
            Clear_Terminal();
            cout << "Catering service selected (placeholder)...\n";
            break;

        case '2':
            Clear_Terminal();
            cout << "Financial control (placeholder)...\n";
            break;

        case '3':
            inMenu = false;
            break;

        default:
            Clear_Terminal();
            gotoxy(30, 22);
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        if (inMenu && option != '3')
        {
            gotoxy(30, 22);
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}
















































void ManageSuppliersANDResources()
{
    int MSR_choice = 0;
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(46, 8);
        cout << "MANAGE SUPPLIERS & RESOURCES";
        gotoxy(25, 9);
        cout << line;
        gotoxy(30, 11); cout << "[1] Manage Emcee";
        gotoxy(30, 12); cout << "[2] Manage Photobooth";
        gotoxy(30, 13); cout << "[3] Manage Catering Items";
        gotoxy(30, 14); cout << "[4] Manage Decorations";
        gotoxy(30, 15); cout << "[5] Back to Main Menu";
        gotoxy(30, 17); cout << "Select an option [1-5]: ";
        gotoxy(55, 17);
        cin >> MSR_choice;

        switch (MSR_choice)
        {
        case 1:
            Clear_Terminal();
            ManageEmcee();
            break;
        case 2:
            Clear_Terminal();
            ManagePhotobooth();
            break;
        case 3:
            Clear_Terminal();
            ManageCateringItems();
            break;
        case 4:
            Clear_Terminal();
            ManageDecorations();
            break;
        case 5:
            Clear_Terminal();
            return;
        default:
            gotoxy(30, 19);
            cout << "Invalid input. Please Try again.";
            cin.get();
            break;
        }
    }
}



void ManageEmcee()
{
    int ME_choice = 0;
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(54, 8);
        cout << "MANAGE EMCEE";
        gotoxy(25, 9);
        cout << line;
        gotoxy(30, 11);
        cout << "[1] Add Emcee";
        gotoxy(30, 12);
        cout << "[2] Remove Emcee";
        gotoxy(30, 13);
        cout << "[3] Back to Resources Menu";
        gotoxy(30, 15);
        cout << "Select an option [1-3]: ";
        gotoxy(55, 15);
        cin >> ME_choice;
        Clear_Getline();

        switch (ME_choice)
        {
        case 1:
        {
            gotoxy(30, 17);
            cout << "Add New Emcee: ";

            string emceeName;
            getline(cin, emceeName);

            while (emceeName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Emcee name cannot be empty.";
                gotoxy(30, 17);
                cout << "Add New Emcee: ";
                getline(cin, emceeName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Added Emcee: " << emceeName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 2:
        {
            gotoxy(30, 17);
            cout << "Remove Emcee: ";
            string emceeName;
            getline(cin, emceeName);

            while (emceeName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Emcee name cannot be empty.";
                gotoxy(30, 17);
                cout << "Remove Emcee: ";
                getline(cin, emceeName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Removed Emcee: " << emceeName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 3:
            return;
        default:
            gotoxy(30, 17);
            cout << "Invalid choice!";
            cin.get();
            break;
        }
    }
}



void ManagePhotobooth()
{
    int MP_choice = 0;
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(52, 8);
        cout << "MANAGE PHOTOBOOTH";
        gotoxy(25, 9);
        cout << line;
        gotoxy(30, 11);
        cout << "[1] Add Photobooth Package";
        gotoxy(30, 12);
        cout << "[2] Remove Photobooth Package";
        gotoxy(30, 13);
        cout << "[3] Back to Resources Menu";
        gotoxy(30, 15);
        cout << "Select an option [1-3]: ";
        gotoxy(55, 15);
        cin >> MP_choice;
        Clear_Getline();

        switch (MP_choice)
        {
        case 1:
        {
            gotoxy(30, 17);
            cout << "Add New Photobooth: ";
            string PhotoboothName;
            getline(cin, PhotoboothName);

            while (PhotoboothName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Package name cannot be empty.";
                gotoxy(30, 17);
                cout << "Add New Photobooth: ";
                getline(cin, PhotoboothName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Added Photobooth: " << PhotoboothName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 2:
        {
            gotoxy(30, 17);
            cout << "Remove Photobooth: ";
            string PhotoboothName;
            getline(cin, PhotoboothName);

            while (PhotoboothName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Package name cannot be empty.";
                gotoxy(30, 17);
                cout << "Remove Photobooth: ";
                getline(cin, PhotoboothName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Removed Photobooth: " << PhotoboothName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 3:
            return;

        default:
            gotoxy(30, 17);
            cout << "Invalid choice!";
            cin.get();
            break;
        }
    }
}



void ManageCateringItems()
{
    int MCI_choice = 0;
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(50, 8);
        cout << "MANAGE CATERING ITEMS";
        gotoxy(25, 9);
        cout << line;
        gotoxy(30, 11);
        cout << "[1] Add Catering Item";
        gotoxy(30, 12);
        cout << "[2] Remove Catering Item";
        gotoxy(30, 13);
        cout << "[3] Back to Resources Menu";
        gotoxy(30, 15);
        cout << "Select an option [1-3]: ";
        gotoxy(55, 15);
        cin >> MCI_choice;
        Clear_Getline();

        switch (MCI_choice)
        {
        case 1:
        {
            gotoxy(30, 17);
            cout << "Add New Catering Item: ";
            string CateringitemName;
            getline(cin, CateringitemName);

            while (CateringitemName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Item name cannot be empty.";
                gotoxy(30, 17);
                cout << "Add New Catering Item: ";
                getline(cin, CateringitemName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Added Catering Item: " << CateringitemName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 2:
        {
            gotoxy(30, 17);
            cout << "Remove Catering Item: ";
            string CateringitemName;
            getline(cin, CateringitemName);

            while (CateringitemName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Item name cannot be empty.";
                gotoxy(30, 17);
                cout << "Remove Catering Item: ";
                getline(cin, CateringitemName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Removed Catering Item: " << CateringitemName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 3:
            return;
        default:
            gotoxy(30, 17);
            cout << "Invalid choice!";
            cin.get();
            break;
        }
    }
}



void ManageDecorations()
{
    int MD_choice = 0;
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(51, 8);
        cout << "MANAGE DECORATIONS";
        gotoxy(25, 9);
        cout << line;
        gotoxy(30, 11);
        cout << "[1] Add Decoration";
        gotoxy(30, 12);
        cout << "[2] Remove Decoration";
        gotoxy(30, 13);
        cout << "[3] Back to Resources Menu";
        gotoxy(30, 15);
        cout << "Select an option [1-3]: ";
        gotoxy(55, 15);
        cin >> MD_choice;
        Clear_Getline();

        switch (MD_choice)
        {
        case 1:
        {
            gotoxy(30, 17);
            cout << "Add New Decoration: ";
            string decorationName;
            getline(cin, decorationName);

            while (decorationName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Decoration name cannot be empty.";
                gotoxy(30, 17);
                cout << "Add New Decoration: ";
                getline(cin, decorationName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Added Decoration: " << decorationName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 2:
        {
            gotoxy(30, 17);
            cout << "Remove Decoration: ";
            string decorationName;
            getline(cin, decorationName);

            while (decorationName.empty())
            {
                ClearLine(30, 17, 40);
                gotoxy(30, 18);
                cout << "Decoration name cannot be empty.";
                gotoxy(30, 17);
                cout << "Remove Decoration: ";
                getline(cin, decorationName);
            }
            ClearLine(30, 18, 40);
            gotoxy(30, 19);
            cout << "Removed Decoration: " << decorationName;
            gotoxy(30, 21);
            cout << "Press ENTER to continue...";
            cin.get();
            break;
        }
        case 3:
            return;
        default:
            gotoxy(30, 17);
            cout << "Invalid choice!";
            cin.get();
            break;
        }
    }
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
        R"(^((0[1-9]|1[0-2]):([0-5][0-9]))-((0[1-9]|1[0-2]):([0-5][0-9]))\s?(AM|PM)$)"); // HH:MM-HH:MM AM|PM
    return regex_match(timeStr, time_pattern);
}

string ResolveCSVPath(const string &csvPath)
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

// If CSV is Readable
bool IsCSVReadable(const string &csvPath)
{
    string pathToUse = ResolveCSVPath(csvPath);
    std::ifstream infile(pathToUse);
    if (!infile.is_open())
        return false;
    string tmp;
    return static_cast<bool>(getline(infile, tmp));
}

// Normalize Date
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

// Date is taken checker
bool IsDateTaken(const string &dateStr, const string &csvPath)
{
    string pathToUse = ResolveCSVPath(csvPath);
    std::ifstream infile(pathToUse);

    if (!infile.is_open())
        return false; // FIXED: Return false if file can't be opened

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
                out.push_back('"'); // adds double quote
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

    // prepare each of the columns to match the existing file format
    // Headers (approx): ClientID, ClientName, ContactNum, Address, Date, Time, Venue, Landmarks, EventType, Pax,(space), Main Dish, Drinks, Appetizers, Desserts,(space), EmceeName, Rate, (space), PhotoboothPackage, PhotoboothPrice, (space), DesignNotes, (space), VenueSetupCost, ManualExpenses, TotalCost
    vector<string> cols(27, "");
    cols[0] = to_string(ClientID); 
    cols[1] = csvEscape(ClientName);
    cols[2] = csvEscape(ClientNum);
    cols[3] = csvEscape(ClientAddress);
    cols[4] = csvEscape(NormalizeDate(EventDate)); 
    cols[5] = csvEscape(EventTime);
    cols[6] = csvEscape(Venue);
    cols[7] = csvEscape(ClientLandmarks);
    cols[8] = csvEscape(EventType);
    cols[9] = PaxAmount > 0 ? to_string(PaxAmount) : "";
    // cols[10] is empty space
    cols[11] = csvEscape(join(chosenMainDish, ";"));
    cols[12] = csvEscape(join(chosenDrinks, ";"));
    cols[13] = csvEscape(join(chosenAppetizers, ";"));
    cols[14] = csvEscape(join(chosenDesserts, ";"));
    // cols[15] is empty space
    cols[16] = csvEscape(join(chosenEmcee, ";"));
    cols[17] = joinDouble(chosenEmceeRate, ";"); 
    // cols[18] is empty space
    cols[19] = csvEscape(join(chosenPhotoboothPackage, ";"));
    cols[20] = joinDouble(chosenPhotoboothPackagePrice, ";"); 
    // cols[21] is empty space
    cols[22] = csvEscape(join(designNotes, ";")); 
    cols[23] = VenueSetupCost > 0 ? to_string(VenueSetupCost) : ""; 
    cols[24] = TotalExpenseAmount > 0 ? to_string(TotalExpenseAmount) : ""; 
    cols[25] = to_string(BaseCateringCost); 
    cols[26] = to_string(TotalServiceCost); 

    // Actually write to the CSV file
    std::ofstream outfile(csvToUse, std::ios::app); // append mode
    if (!outfile.is_open())
    {
        cout << "\nError: Could not open " << csvToUse << " for writing!\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    // Write the row
    for (size_t i = 0; i < cols.size(); ++i)
    {
        if (i > 0)
            outfile << ",";
        outfile << cols[i];
    }
    outfile << "\n";
    outfile.close();

    cout << "\nEvent successfully saved to " << csvToUse << "!\n";
}