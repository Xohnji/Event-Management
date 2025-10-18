#include <iostream>
#include <cstdlib>
#include <vector>
#include <cctype> // for toupper
#include <limits> // for numeric_limits
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

// Universal Initialization for Important Infos
std::string ClientName, ClientAddress, ClientInfo, Venue, Schedule, Resources, EventTime, EventDate;
std::string ClientNum, EventType, ClientLandmarks;
int MainDishCounter, DrinksCounter, DessertsCounter, AppetizersCounter, i, PaxAmount;
char PackageChoice, MainDish, CateringChoice;

// Storage for chosen menu items
std::vector<std::string> chosenMainDish;
std::vector<std::string> chosenDrinks;
std::vector<std::string> chosenAppetizers;
std::vector<std::string> chosenDesserts;

// Void Prototypes
void Clear_Terminal();
void Create_EventId();
void pressEnterToContinue();
void ExportBookingToCSV();
void View_Booking_Calendar();
#pragma region NewBooking
void New_Booking();
void CateringMain();
void Booking_Slip();
void Date_Checker();
void ChooseService();
void CateringValidation();
void CateringSelection();
void CateringMenu();
#pragma endregion

// Enum for Menu Options
enum class MenuOptions
{
    Create_Event = 1,
    View_Update_Bookings = 2,
    Manage_Suppliers_Resources = 3,
    View_Booking_Calendar = 4,
    Run_Financial_Reports = 5,
    Exit_System = 6
};

// Menu Category Struct
struct MenuCategory
{
    std::string name;
    std::vector<std::string> options;
};

#pragma region MainMenu
int main()
{

    int ChoiceNum;

    while (true)
    {

        std::cout << "=========================================";
        std::cout << "\n|            SYSTEM PROTOTYPE          |";
        std::cout << "\n=========================================";
        std::cout << "\n| [1]. Create New Event.               |";
        std::cout << "\n| [2]. View/Update Booked Events.      |";
        std::cout << "\n| [3]. Manage Suppliers & Resources .  |";
        std::cout << "\n| [4]. View Booking Calendar.          |";
        std::cout << "\n| [5]. Run Financial Reports.          |";
        std::cout << "\n| [6]. Exit System.                    |";
        std::cout << "\n=========================================";
        std::cout << "\nEnter Choice (1 - 6): ";
        std::cin >> ChoiceNum;

        MenuOptions option = static_cast<MenuOptions>(ChoiceNum); // Put user input to the enum

        switch (option)
        {
        case MenuOptions::Create_Event:
            Clear_Terminal();
            New_Booking();
            Booking_Slip();
            break;

        case MenuOptions::View_Update_Bookings:
            Clear_Terminal();
            break;

        case MenuOptions::Manage_Suppliers_Resources:
            Clear_Terminal();
            break;

        case MenuOptions::View_Booking_Calendar:
            Clear_Terminal();
            View_Booking_Calendar();
            break;

        case MenuOptions::Run_Financial_Reports:
            Clear_Terminal();
            break;

        case MenuOptions::Exit_System:
            Clear_Terminal();
            return 0;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}

#pragma endregion

#pragma region Clear
void Clear_Terminal()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
#pragma endregion

#pragma region newBookingCatering
void New_Booking()
{
    std::cout << "\n=========================================";
    std::cout << "\n|   YNARICH EMS: 1. CREATE NEW EVEN    |";
    std::cout << "\n=========================================\n";

    // Client Informations
    std::cout << "\n<-----------CLIENT INFORMATION----------->\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter Client Name: ";
    std::getline(std::cin, ClientName);
    
    std::cout << "Enter Contact Number: ";
    std::getline(std::cin, ClientNum);
    while (ClientNum.length() != 11 || ClientNum.substr(0, 2) != "09") {
        std::cout << "Invalid contact number! Must be 11 digits starting with '09'. Please try again.\n";
        std::cout << "Enter Contact Number: ";
        std::getline(std::cin, ClientNum);
    }
    
    std::cout << "Enter Client Address: ";
    std::getline(std::cin, ClientAddress);

    // Event Details
    std::cout << "\n<-----------EVENT DETAILS----------->\n";
    std::cout << "Enter Event Type: ";
    std::getline(std::cin, EventType);
    std::cout << "Enter Event Date (MM/DD/YY): ";
    std::getline(std::cin, EventDate);

    // Date Checker Function Call
    std::cout << "\n<-----------Date Checker----------->\n";
    Date_Checker();

    std::cout << "\n<-----------EVENT DETAILS----------->\n";
    std::cout << "Enter Venue Name (e.g., THe Blue Leaf): ";
    std::getline(std::cin, Venue);
    
    std::cout << "Enter Key Landmarks (for logistics): ";
    std::getline(std::cin, ClientLandmarks);
    
    std::cout << "Enter Estimated Pax (Min. 60): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin >> PaxAmount;
    while (PaxAmount < 60 || PaxAmount % 10 != 0)
    {
        std::cout << "Invalid Inputttt!!!\n";
        std::cout << "Enter Estimated Pax (Min. 60): ";
        std::cin >> PaxAmount;
    }
    std::cout << "PaxAmount = " << PaxAmount << '\n';
    
    std::cout << "\n<------------------------------------->\n";
    Create_EventId();

    std::cout << "**Next Step: Budgeting and Service Allocation.**\n";
    pressEnterToContinue();
    Clear_Terminal();
    CateringMain();
    ExportBookingToCSV();
}

void Date_Checker()
{
    std::cout << "Status: Date is AVAILABLE\n";
    // Function to check date validity can be implemented here
}
void Create_EventId()
{
    std::cout << "Event ID succesfully created: moewmoewtestnumber\n";
    // Function to create a unique event ID can be implemented here
}

void CateringMain()
{
    std::cout << "Include Catering? [Y/N]: ";
    std::cin >> CateringChoice;
    CateringChoice = static_cast<char>(std::toupper(static_cast<unsigned char>(CateringChoice)));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (CateringChoice == 'Y')
    {
        ChooseService();
        CateringValidation();
        CateringMenu();
        CateringSelection();
    }
}
void ChooseService()
{
    std::cout << "Package Inclusions:\n";
    std::cout << "_________________________________________________\n";
    std::cout << "|Package 1:            |Package 2:              |\n";
    std::cout << "|Premium Catering      |Standard Catering       |\n";
    std::cout << "|Emcee                 |Venue Set-Up            |\n";
    std::cout << "|Venue Set-Up          |3 Hrs Stndrd Photoboot  |\n";
    std::cout << "|Stage Decoration      |                        |\n";
    std::cout << "|3 Hrs Unli Photobooth |                        |\n";
    std::cout << "_________________________________________________\n";
    std::cout << "Catering Package Inclusions:\n";
    std::cout << "=================================================\n";
    std::cout << "|Premium Catering:     |Standard Catering:      |\n";
    std::cout << "|5 Main Dish           |2 Main Dish             |\n";
    std::cout << "|2 Drinks              |1 Drink                 |\n";
    std::cout << "|3 Appetizers          |1 Appetizer             |\n";
    std::cout << "|3 Desserts            |2 Desserts              |\n";
    std::cout << "=================================================\n";
    std::cout << "Choose Package:\n";
    std::cout << "[A]Package 1\n";
    std::cout << "[B]Package 2\n";
    std::cout << "[C]Custom Package\n\n";
    std::cout << "Enter Package Choice: ";
    std::cin >> PackageChoice;
    // normalize to uppercase and clear newline for getline
    PackageChoice = static_cast<char>(std::toupper(static_cast<unsigned char>(PackageChoice)));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void CateringValidation()
{
    switch (PackageChoice)
    {
    case 'A':
        MainDishCounter = 5;
        DrinksCounter = 2;
        AppetizersCounter = 3;
        DessertsCounter = 3;
        break;

    case 'B':
        MainDishCounter = 2;
        DrinksCounter = 1;
        AppetizersCounter = 1;
        DessertsCounter = 2;
        break;

    case 'C':
        std::cout << "Enter QTY of Main Dish: ";
        std::cin >> MainDishCounter;
        std::cout << "Enter QTY of Drinks: ";
        std::cin >> DrinksCounter;
        std::cout << "Enter QTY of Appetizers: ";
        std::cin >> AppetizersCounter;
        std::cout << "Enter QTY of Dessert: ";
        std::cin >> DessertsCounter;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;

    default:
        // If user entered unexpected char, default to Package A
        MainDishCounter = 5;
        DrinksCounter = 2;
        AppetizersCounter = 3;
        DessertsCounter = 3;
        break;
    }
}

void CateringMenu()
{
    std::cout << "_________________________________________________\n\n";
    std::cout << "Catering Inclusions:\n";
    std::cout << "_________________________________________________\n";
    std::cout << "|                     Menu:                     |\n";
    std::cout << "=================================================\n";
    std::cout << "|Main Dish:             |Drinks:                |\n";
    std::cout << "|[A]Pork Adobo          |[A]Red Iced Tea        |\n";
    std::cout << "|[B]Baby Back Ribs      |[B]Blue Lemonade       |\n";
    std::cout << "|[C]Spaghetti           |[C]Ginger Ale          |\n";
    std::cout << "=================================================\n";
    std::cout << "|Desserts:              |Appetizers:            |\n";
    std::cout << "|[A]Creme Brulee        |[A]Chili Oil           |\n";
    std::cout << "|[B]Choco Mousse        |[B]Fortune Cookie      |\n";
    std::cout << "|[C]Buko Pandan         |[C]Cashews             |\n";
    std::cout << "=================================================\n";
}

void CateringSelection()
{
    char choice;

    // Main Dish
    for (i = 1; i <= MainDishCounter; i++)
    {
        std::cout << "Enter Main Dish " << i << " (A/B/C): ";
        std::cin >> choice;
        choice = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
        switch (choice)
        {
        case 'A':
            chosenMainDish.push_back("Pork Adobo");
            break;
        case 'B':
            chosenMainDish.push_back("Baby Back Ribs");
            break;
        case 'C':
            chosenMainDish.push_back("Spaghetti");
            break;
        default:
            std::cout << "Invalid choice!\n";
            i--;
            break;
        }
    }
    std::cout << "_________________________________________________\n";

    // Drinks
    for (i = 1; i <= DrinksCounter; i++)
    {
        std::cout << "Enter Drink " << i << " (A/B/C): ";
        std::cin >> choice;
        choice = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
        switch (choice)
        {
        case 'A':
            chosenDrinks.push_back("Red Iced Tea");
            break;
        case 'B':
            chosenDrinks.push_back("Blue Lemonade");
            break;
        case 'C':
            chosenDrinks.push_back("Ginger Ale");
            break;
        default:
            std::cout << "Invalid choice!\n";
            i--;
            break;
        }
    }
    std::cout << "_________________________________________________\n";

    // Appetizers
    for (i = 1; i <= AppetizersCounter; i++)
    {
        std::cout << "Enter Appetizer " << i << " (A/B/C): ";
        std::cin >> choice;
        choice = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
        switch (choice)
        {
        case 'A':
            chosenAppetizers.push_back("Chili Oil");
            break;
        case 'B':
            chosenAppetizers.push_back("Fortune Cookie");
            break;
        case 'C':
            chosenAppetizers.push_back("Cashews");
            break;
        default:
            std::cout << "Invalid choice!\n";
            i--;
            break;
        }
    }
    std::cout << "_________________________________________________\n";

    // Desserts
    for (i = 1; i <= DessertsCounter; i++)
    {
        std::cout << "Enter Dessert " << i << " (A/B/C): ";
        std::cin >> choice;
        choice = static_cast<char>(std::toupper(static_cast<unsigned char>(choice)));
        switch (choice)
        {
        case 'A':
            chosenDesserts.push_back("Creme Brulee");
            break;
        case 'B':
            chosenDesserts.push_back("Choco Mousse");
            break;
        case 'C':
            chosenDesserts.push_back("Buko Pandan");
            break;
        default:
            std::cout << "Invalid choice!\n";
            i--;
            break;
        }
    }
    // clear leftover newline before any possible getline later
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Booking_Slip()
{
    // ===================== BOOKING SLIP =====================
    Clear_Terminal();
    std::cout << "\n================= BOOKING SLIP =================\n";
    std::cout << "Client Name   : " << ClientName << "\n";
    std::cout << "Contact Number: " << ClientNum << "\n";
    std::cout << "Address       : " << ClientAddress << "\n";
    std::cout << "Venue         : " << Venue << "\n";
    std::cout << "Date          : " << EventDate << "\n";
    std::cout << "Time          : " << EventTime << "\n";

    std::cout << "\n================= MENU SUMMARY =================\n";

    std::cout << "\nMain Dishes:\n";
    if (chosenMainDish.empty())
        std::cout << "- (none)\n";
    for (auto &dish : chosenMainDish)
        std::cout << "- " << dish << std::endl;

    std::cout << "\nDrinks:\n";
    if (chosenDrinks.empty())
        std::cout << "- (none)\n";
    for (auto &drink : chosenDrinks)
        std::cout << "- " << drink << std::endl;

    std::cout << "\nAppetizers:\n";
    if (chosenAppetizers.empty())
        std::cout << "- (none)\n";
    for (auto &app : chosenAppetizers)
        std::cout << "- " << app << std::endl;

    std::cout << "\nDesserts:\n";
    if (chosenDesserts.empty())
        std::cout << "- (none)\n";
    for (auto &dessert : chosenDesserts)
        std::cout << "- " << dessert << std::endl;

    std::cout << "====================================================\n\n";
}

#pragma endregion

void pressEnterToContinue()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nPress Enter to proceed...";
    std::cin.get();
}

// Helper: replace chars not suitable for filenames
static std::string SanitizeFileName(const std::string &name)
{
    std::string out = name;
    // Replace spaces with underscores and remove problematic chars
    std::replace(out.begin(), out.end(), ' ', '_');
    const std::string forbidden = "\\/:?\"<>|*";
    out.erase(std::remove_if(out.begin(), out.end(), [&](char c)
                             { return forbidden.find(c) != std::string::npos; }),
              out.end());
    return out;
}

void ExportBookingToCSV()
{
    // Create filename using client name and date
    std::string filename = "booking_" + SanitizeFileName(ClientName) + "_" + SanitizeFileName(EventDate) + ".csv";

    // Open file for writing (will create or overwrite)
    std::ofstream ofs(filename);
    if (!ofs)
    {
        std::cerr << "Failed to create CSV file: " << filename << std::endl;
        return;
    }

    // Write header rows
    ofs << "Client Name,Contact Number,Address,Venue,Date,Time,Event Type,Pax" << '\n';
    ofs << '"' << ClientName << '"' << ','
        << '"' << ClientNum << '"' << ','
        << '"' << ClientAddress << '"' << ','
        << '"' << Venue << '"' << ','
        << '"' << EventDate << '"' << ','
        << '"' << EventTime << '"' << ','
        << '"' << EventType << '"' << ','
        << '"' << PaxAmount << '"' << '\n';

    // Menu sections: write each category as a semicolon-separated list inside a quoted field
    auto join = [](const std::vector<std::string> &v)
    {
        std::ostringstream ss;
        for (size_t i = 0; i < v.size(); ++i)
        {
            if (i)
                ss << "; ";
            ss << v[i];
        }
        return ss.str();
    };

    ofs << "Main Dishes,Drinks,Appetizers,Desserts" << '\n';
    ofs << '"' << join(chosenMainDish) << '"' << ','
        << '"' << join(chosenDrinks) << '"' << ','
        << '"' << join(chosenAppetizers) << '"' << ','
        << '"' << join(chosenDesserts) << '"' << '\n';

    ofs.close();

    std::cout << "Booking exported to CSV: " << filename << std::endl;
}


// Event Calendar
// Axel: Cout palang sya walang datas sa tables,
// bahala na si James mag operate ng function neto
// dahil wala akong alam sa CSV kung pano i rerekta ung data from CSV to terminal.
void View_Booking_Calendar()
{
    Clear_Terminal();
    std::cout << "==============================================\n";
    std::cout << "|       MAIN MENU: 4. VIEW BOOKING CALENDAR   |\n";
    std::cout << "==============================================\n";
    std::cout << "Current Date: 10/18/2025\n\n";

    std::cout << "--- CONFIRMED & PENDING EVENT SCHEDULE ---\n";
    std::cout << "|   DATE   | EVENT ID |   CLIENT NAME   |         STATUS        | TOTAL GUEST |\n";
    std::cout << "|----------|-----------|----------------|-----------------------|--------------|\n";
    std::cout << "|          |           |                |                       |              |\n";
    std::cout << "|          |           |                |                       |              |\n";
    std::cout << "|          |           |                |                       |              |\n";
    std::cout << "---------------------------------------------------------------------------------\n";

    std::cout << "\n--- CALENDAR ACTIONS ---\n";
    std::cout << "1. Filter Calendar (Month/Year)\n";
    std::cout << "2. View All Inquiries (Includes dates on soft hold)\n";
    std::cout << "3. Return to Main Menu\n";

    std::cout << "Enter Choice (1-3): ";
}





