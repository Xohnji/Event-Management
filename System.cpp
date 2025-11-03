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
string csvToUse = ("C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Mock_Data.csv");

// Global Variables
int MMchoice; // Main Menu choice variable
int SAchoice; // Service Allocation Menu choice variable

// Client Information Variables
string ClientName, ClientNum, ClientAddress;

// Event Details Variables
string EventType, EventDate, EventTime, Venue, ClientLandmarks;
int PaxAmount;

int ClientID = 10; // Placeholder Client ID

// Service Allocation VariableS
double TotalServiceCost = 0.0; //TOTAL
double baseCateringCost = 0.0; //CATERING 
double emceeCost = 0.0; //EMCEE
double photoboothCost = 0.0; //PHOTOBOOTH
double venueSetupCost = 0.0; //VENUE SETUP
double manualExpenseCost = 0.0; //MANUAL EXPENSE LEDGER


// Global Initialization for chosen ITEMS storage:
//CATERING:
vector<string> chosenEntrees, chosenAppetizers, chosenDrinks, chosenDesserts;
//EMCEE
vector<string> chosenEmcee;
vector<double> chosenEmceeRate;
//PHOTOBOOTH:
vector<string> chosenPhotoboothPackage;
vector<double> chosenPhotoboothRate;
//VENUE SETUP
vector<string> designNotes;
vector<double> chosendesignCost;
//MANUAL EXPENSE LEDGER
vector<string> manualExpenseEntry;
vector<double> manualExpenseAmount;

//FINANCIAL CONTROL MENU INITIALIZATION

struct PaymentLog {
    int paymentID;
    string date;
    double amount;
    string remarks;
    string status;
};

    double totalPaid = 0.0;
    int paymentCounter = 1;

vector<PaymentLog> paymentHistory;


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
void FinancialControlMenu();
// append
void AppendToCSV(const string &csvToUse);
// Update/View
void ViewUpdateBookings();
void Service_Allocation_Menu();
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
    gotoxy(30, 9);
    cout << "Enter Client Name: ";
    gotoxy(50, 9);
    getline(cin, ClientName);
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

    gotoxy(30, 11);
    cout << "Enter Client Address: ";
    gotoxy(53, 11);
    getline(cin, ClientAddress);
    gotoxy(30, 13);
    cout << "EVENT DETAILS";
    gotoxy(30, 15);
    cout << "Enter Event Type: ";
    gotoxy(49, 15);
    getline(cin, EventType);

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

    gotoxy(30, 18);
    cout << "Enter Venue: ";
    gotoxy(44, 18);
    getline(cin, Venue);
    gotoxy(30, 19);
    cout << "Enter Landmarks: ";
    gotoxy(48, 19);
    getline(cin, ClientLandmarks);

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
            FinancialCotrolMenu();
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
    size_t row; //for dynamic vertical positioning
    char confirmChoice;

    Clear_Terminal();
    Border(10, 1, 99, 30);

    string line(86, '=');
    gotoxy(15, 2); cout << line;
    gotoxy(42, 3); cout << "YNARICH EMS: CATERING MENU SELECTION";
    gotoxy(15, 4); cout << line;

    // ====== STRUCTS AND TEMPORARY DATA ======
    struct CateringPackage 
    {
        string packageName;
        double ratePerPax;
        string description;
        int appetizers;
        int entrees;
        int drinks;
        int desserts;
    };

    // Temporary packages
    vector<CateringPackage> cateringList = 
    {
        {"BRONZE PACKAGE", 400.00, "1 Appetizer, 2 Entrees, 1 Beverage, 1 Dessert", 1, 2, 1, 1},
        {"SILVER PACKAGE", 580.00, "2 Appetizers, 3 Entrees, 2 Beverages, 2 Desserts", 2, 3, 2, 2}
    };

    // Menu options per category
    vector<string> entreeList = {"Roasted Herb Chicken", "Chicken Cordon Bleu", "Honey-Glazed Ham", "Roast Beef Tenderloin", "Butter Tilapia Fillets", "Pan-Seared Sea Bass"};
    vector<string> appetizerList = {"Spring Rolls", "Stuffed Mushrooms", "Dumplings", "Honey Crisps"};
    vector<string> drinkList = {"Red Iced Tea", "Blue Lemonade"};
    vector<string> dessertList = {"Chocolate Brownies", "Mini Egg Tarts", "Cheesecake Bites", "Creme Brulee"};

    // ====== DISPLAY PACKAGE SELECTION ======
    gotoxy(18, 6);
    cout << "CURRENT ESTIMATED TOTAL (Pre-Catering): P" << fixed << setprecision(2) << TotalServiceCost;
    gotoxy(15, 7); cout << string(86, '-');

    int y = 9;
    for (size_t i = 0; i < cateringList.size(); ++i)
    {
        gotoxy(18, y); cout << "[" << (i + 1) << "] " << cateringList[i].packageName;
        gotoxy(25, y + 1); cout << "Rate: P" << fixed << setprecision(2) << cateringList[i].ratePerPax << " per pax";
        gotoxy(25, y + 2); cout << "Includes: " << cateringList[i].description;
        y += 4;
    }
    gotoxy(15, y); cout << string(86, '-');

    // ====== PACKAGE CHOICE ======
    int choice;
    while (true)
    {
        gotoxy(18, y + 2); cout << "Enter Package Choice [1-" << cateringList.size() << "]: ";
        gotoxy(46, y + 2); cin >> choice;

        if (cin.fail() || choice < 1 || choice >(int)cateringList.size())
        {
            cin.clear();
            Clear_Getline();
            gotoxy(18, y + 4); cout << "Invalid input! Please enter a valid package number.";
            ClearLine(46, y + 2, 10);
            continue;
        }
        break;
    }

    CateringPackage selectedCatering = cateringList[choice - 1];
    baseCateringCost = selectedCatering.ratePerPax * PaxAmount;
    TotalServiceCost += baseCateringCost;

    ClearLine(18, y + 4, 55);
    gotoxy(18, y + 4); cout << ">> " << selectedCatering.packageName << " selected: P" << selectedCatering.ratePerPax << " x " << PaxAmount << " Pax";
    gotoxy(18, y + 5); cout << "   Catering Subtotal: P" << fixed << setprecision(2) << baseCateringCost;
    gotoxy(18, y + 6); cout << "   Current Estimated Total Cost: P" << fixed << setprecision(2) << TotalServiceCost;

    gotoxy(18, y + 7); cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    cin.clear();
    
    int input;

      do 
    {
        // Clear previous selections
        chosenEntrees.clear();
        chosenAppetizers.clear();
        chosenDrinks.clear();
        chosenDesserts.clear();
        
    Clear_Terminal();
    Border(10, 1, 99, 45);
    gotoxy(15, 2); cout << line;
    gotoxy(43, 3); cout << "YNARICH EMS: CATERING MENU SELECTION";
    gotoxy(15, 4); cout << line;
    gotoxy(18, 6); cout << "Includes " << selectedCatering.entrees << " Entrees, " << selectedCatering.appetizers << " Appetizer(s), "
                         << selectedCatering.drinks << " Drink(s), " << selectedCatering.desserts << " Dessert(s)";
    
    // === HEADER === 
    gotoxy(23, 8); cout << "CATEGORY";
    gotoxy(65, 8); cout << "MENU";
    gotoxy(15, 9); cout << string(86, '-');

    row = 10;

    // ====== DISPLAY ENTREE MENU ======
    gotoxy(23, 10); cout << "ENTREES";

    for (size_t i = 0; i < entreeList.size(); i += 2)
    {
        // Left column
        gotoxy(38, row);
        cout << "[" << (i + 1) << "] " << entreeList[i];

        // Right column (only if next item exists)
        if (i + 1 < entreeList.size())
        {
            gotoxy(70, row); 
            cout << "[" << (i + 2) << "] " << entreeList[i + 1];
        }

        row++;
    }

    row += 2; // Leaves space for next menu

    // DISPLAY APPETIZER MENU

    gotoxy(23, row); cout << "APPETIZERS";
    
    for (size_t i = 0; i < appetizerList.size(); i += 2)
    {
        // Left column
        gotoxy(38, row);
        cout << "[" << (i + 1) << "] " << appetizerList[i];

        // Right column (only if next item exists)
        if (i + 1 < appetizerList.size())
        {
            gotoxy(70, row); 
            cout << "[" << (i + 2) << "] " << appetizerList[i + 1];
        }

        row++;
    }

    row += 2; // Leaves space for next menu

    // DISPLAY DRINK MENU

    gotoxy(23, row); cout << "BEVERAGES";
    
    for (size_t i = 0; i < drinkList.size(); i += 2)
    {
        // Left column
        gotoxy(38, row);
        cout << "[" << (i + 1) << "] " << drinkList[i];

        // Right column (only if next item exists)
        if (i + 1 < drinkList.size())
        {
            gotoxy(70, row); 
            cout << "[" << (i + 2) << "] " << drinkList[i + 1];
        }

        row++;
    }

    row += 2; // Leaves space for next menu

    // DISPLAY DESSERT MENU

    gotoxy(23, row); cout << "DESSERTS";
    
    for (size_t i = 0; i < dessertList.size(); i += 2)
    {
       // Left column
        gotoxy(38, row);
        cout << "[" << (i + 1) << "] " << dessertList[i];

        // Right column (only if next item exists)
        if (i + 1 < dessertList.size())
        {
            gotoxy(70, row); 
            cout << "[" << (i + 2) << "] " << dessertList[i + 1];
        }

        row++;
    }

    gotoxy(15, row); cout << string(86, '-'); row++;

    //ENTREE SELECTION

    for (int i = 0; i < selectedCatering.entrees; ++i)
    {
        gotoxy(18, row); cout << "Enter Entree #" << (i + 1) << " [1-" << entreeList.size() << "]: ";
        gotoxy(42, row); cin >> input;
        
        if (cin.fail() || input < 1 || input >(int)entreeList.size())
        {   
            cin.clear();
            Clear_Getline();
            gotoxy(18, row + 1); cout << "Invalid input! Please try again.";
            ClearLine(42, row, 10);
            i--;
            row--;
        }

        else 
        {   ClearLine(18, row + 1, 40);
            gotoxy(44, row); cout << entreeList[input - 1] << " selected.";
            chosenEntrees.push_back(entreeList[input - 1]);
        }
        
        row++;

    }

    //APPETIZER SELECTION

    for (int i = 0; i < selectedCatering.appetizers; ++i)
    {
        gotoxy(18, row); cout << "Enter Appetizer #" << (i + 1) << " [1-" << appetizerList.size() << "]: ";
        gotoxy(45, row); cin >> input;
        
        if (cin.fail() || input < 1 || input >(int)appetizerList.size())
        {
            cin.clear();
            Clear_Getline();
            gotoxy(18, row + 1); cout << "Invalid input! Please try again.";
            ClearLine(45, row, 10);
            i--;
            row--;
        }

        else 
        {   ClearLine(18, row + 1, 40);
            gotoxy(47, row); cout << appetizerList[input - 1] << " selected.";
            chosenAppetizers.push_back(appetizerList[input - 1]);
        }

        row++;

    }

    //DRINKS SELECTION

    for (int i = 0; i < selectedCatering.drinks; ++i)
    {
        gotoxy(18, row); cout << "Enter Beverage #" << (i + 1) << " [1-" << drinkList.size() << "]: ";
        gotoxy(44, row); cin >> input;
        
        if (cin.fail() || input < 1 || input >(int)drinkList.size())
        {
            cin.clear();
            Clear_Getline();
            gotoxy(18, row + 1); cout << "Invalid input! Please try again.";
            ClearLine(44, row, 10);
            i--;
            row--;
        }

        else 
        {   ClearLine(18, row + 1, 40);
            gotoxy(46, row); cout << drinkList[input - 1] << " selected.";
            chosenDrinks.push_back(drinkList[input - 1]);
        }

        row++;

    }

    //DESSERTS SELECTION

    for (int i = 0; i < selectedCatering.desserts; ++i)
    {
        gotoxy(18, row); cout << "Enter Dessert #" << (i + 1) << " [1-" << dessertList.size() << "]: ";
        gotoxy(43, row); cin >> input;
        
        if (cin.fail() || input < 1 || input >(int)dessertList.size())
        {
            cin.clear();
            Clear_Getline();
            gotoxy(18, row + 1); cout << "Invalid input! Please try again.";
            ClearLine(43, row, 10);
            i--;
            row--;
        }

        else 
        {   ClearLine(18, row + 1, 40);
            gotoxy(45, row); cout << dessertList[input - 1] << " selected.";
            chosenDesserts.push_back(dessertList[input - 1]);
        }

        row++;

    }

    while (true)
        {

            gotoxy(18, row + 1); cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(53, row + 1); cin >> confirmChoice;

            // Convert to uppercase for easier comparison
            confirmChoice = toupper(confirmChoice);

            // Check if input is valid
            if (confirmChoice == 'C' || confirmChoice == 'E')
                break; // valid input, exit loop

            // Invalid input handling
            gotoxy(18, row + 3); cout << "Invalid input! Please type C or E.";
            ClearLine(53, row + 1, 30); // clear input area
        }

    } while (confirmChoice == 'E' || confirmChoice == 'e');

    ClearLine(18, row + 3, 30);
    gotoxy(18, row + 3); cout << "Catering confirmed. Press Enter to return to Service Allocation Menu";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void EmceeMenu()
{
    char confirmChoice;
    int EMchoice;;
    int y; //for dynamic line positioning

    struct EmceePackage
    {
        string EmceeNames;
        double EmceeRates;
    };

    vector<EmceePackage> EmceeList {
        {"Rico Hernandez", 3000.00},
        {"Mara Dela Cruz", 4500.00 },
        {"Kevin Santos", 6000.00}
    };

    do
    {   y = 10;
        double previousEmceeRate;
        chosenEmcee.clear();
        chosenEmceeRate.clear();

        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2); cout << line;
        gotoxy(40, 3); cout << "YNARICH EMS: EMCEE SELECTION MENU";
        gotoxy(15, 4); cout << line;

        gotoxy(13, 6); cout << "AVAILABLE EMCEES:";
        string line2(90, '-');
        gotoxy(13, 7); cout << line2;

        gotoxy(13, 8); cout << "No.";
        gotoxy(30, 8); cout << "Emcee Name";
        gotoxy(70, 8); cout << "Rate";
        gotoxy(13, 9); cout << line2;

        for (size_t i = 0; i < EmceeList.size(); ++i)
        {
            gotoxy(13, y); cout << "[" << (i + 1) << "]";
            gotoxy(30, y); cout << EmceeList[i].EmceeNames;
            gotoxy(70, y); cout << "P" << fixed << setprecision(2) << EmceeList[i].EmceeRates;
            y++;
        }

        gotoxy(13, y + 1); cout << line2;

        while (true)
        {
            gotoxy(13, y + 3); cout << "Select Emcee [1-" << EmceeList.size() << "]: ";
            gotoxy(33, y + 3); cin >> EMchoice;

            if (cin.fail() || EMchoice < 1 || EMchoice > (int)EmceeList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(13, y + 5); cout << "Invalid input! Please enter a valid number.";
                ClearLine(33, y + 3, 20);
                continue;
            }

            ClearLine(13, y + 5, 60);

            if (previousEmceeRate !=0 )
            {
                emceeCost -= previousEmceeRate;
                TotalServiceCost -= previousEmceeRate;
            }

            string selectedEmcee = EmceeList[EMchoice - 1].EmceeNames;
            double selectedEmceeRate = EmceeList[EMchoice - 1].EmceeRates;

            previousEmceeRate = selectedEmceeRate;

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
            gotoxy(13, y + 9); cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(47, y + 9); cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(13, y + 11); cout << "Invalid choice! Please enter 'C' to Confirm or 'E' to Edit.";
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
    int y; //for dynamic line positioning

    struct Photobooth {
        string PBPackage;
        double PBRate;
    };

    vector<Photobooth> PBList{
        {"Basic Package (2 Hours, 500 Prints)", 2500.00},
        {"Standard Package (3 Hours, Unlimited Prints)", 4000.00},
        {"Premium Package (Full Event, Unlimited Prints)", 6500.00},
    };

    do
    {
        y = 10;
        double previousPBRate; // store new rate for possible replacement later

        chosenPhotoboothPackage.clear();
        chosenPhotoboothRate.clear();

        Clear_Terminal();
        Border(10, 1, 99, 26);

        string line(90, '=');
        gotoxy(15, 2); cout << line;
        gotoxy(40, 3); cout << "YNARICH EMS: PHOTOBOOTH SELECTION MENU";
        gotoxy(15, 4); cout << line;

        gotoxy(13, 6); cout << "AVAILABLE PHOTOBOOTH PACKAGES:";
        string line2(90, '-');
        gotoxy(13, 7); cout << line2;

        gotoxy(13, 8); cout << "No.";
        gotoxy(30, 8); cout << "Package";
        gotoxy(80, 8); cout << "Rate";
        gotoxy(13, 9); cout << line2;

        for (size_t i = 0; i < PBList.size(); ++i)
        {
            gotoxy(13, y); cout << "[" << (i + 1) << "]";
            gotoxy(30, y); cout << PBList[i].PBPackage;
            gotoxy(80, y); cout << "P" << fixed << setprecision(2) << PBList[i].PBRate;
            y++;
        }

        gotoxy(13, y + 1); cout << line2;

        while (true)
        {
            gotoxy(13, y + 3); cout << "Select Photobooth Package [1-" << PBList.size() << "]: ";
            gotoxy(46, y + 3); cin >> PBchoice;

            if (cin.fail() || PBchoice < 1 || PBchoice > (int)PBList.size())
            {
                cin.clear();
                Clear_Getline();
                gotoxy(13, y + 5); cout << "Invalid input! Please enter a valid number.";
                ClearLine(46, y + 3, 20);
                continue;
            }

            ClearLine(13, y + 5, 60);

            //Prevents Readding value every edit selection
            if (previousPBRate != 0)
            {
            photoboothCost -= previousPBRate;
            TotalServiceCost -= previousPBRate;
            }

            string selectedPhotobooth = PBList[PBchoice - 1].PBPackage;
            double selectedPBRate = PBList[PBchoice - 1].PBRate;

            previousPBRate = selectedPBRate; // store new rate for possible replacement later


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
            gotoxy(13, y + 9); cout << "Confirm or Edit Selection? [C/E]: ";
            gotoxy(47, y + 9); cin >> confirmChoice;
            confirmChoice = toupper(confirmChoice);

            if (confirmChoice == 'C' || confirmChoice == 'E')
                break;

            gotoxy(13, y + 11); cout << "Invalid choice! Please enter 'C' to Confirm or 'E' to Edit.";
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
    chosendesignCost.push_back(designCost);
    venueSetupCost = designCost; // FIXED: Store in variable
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
        manualExpenseCost += ExpenseAmount;
        TotalServiceCost += ExpenseAmount;

        manualExpenseEntry.push_back(ExpenseEntry);
        manualExpenseAmount.push_back(ExpenseAmount);
        // (append to vector or CSV here)

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
    }
    
}

// ----- HELPER FUNCTIONS -----
// Date validation: MM/DD/YY format
bool ValidateDate(const string& date) {
    regex datePattern(R"(^\d{2}/\d{2}/\d{2}$)");
    return regex_match(date, datePattern);
}

string GetPaymentStatus(double totalPaid, double totalCost) {
    double paidRatio = totalPaid / totalCost;
    if (paidRatio == 1.0) return "FULLY PAID (100%)";
    if (paidRatio < 1.0 && paidRatio > 0.50) return "PARTIAL FULFILLMENT (50% - 100%)";
    if (paidRatio >= 0.50) return "FOLLOW-UP PAID (50%)";
    if (paidRatio < 0.50 && paidRatio > 0.10) return "PARTIAL FOLLOW-UP (10% - 50%)";
    if (paidRatio >= 0.10) return "DOWNPAYMENT PAID (10%)";
    if (paidRatio < 0.10 && paidRatio > 0.0) return "PARTIAL DOWNPAYMENT (0% - 10%)";
    if (paidRatio == 0.0) return "INQUIRY (0%)";
}


// ----- MAIN FUNCTION -----
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

//---------------------------------------------UPDATE BOOKINGS-----------------------------------

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
    cols[11] = csvEscape(join(chosenEntree, ";"));
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
    cols[24] = manualExpenseCost > 0 ? to_string(manualExpenseCost) : ""; 
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
