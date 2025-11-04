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
using namespace std;


struct Emcee {
    string name;
    double rate;
};

struct Photobooth {
    string name;
    double rate;
};


vector<Emcee> loadEmceesFromCSV(const string& filename);
void saveEmceesToCSV(const string& filename, const vector<Emcee>& emcees);
vector<Photobooth> loadPhotoboothsFromCSV(const string& filename);
void savePhotoboothsToCSV(const string& filename, const vector<Photobooth>& booths);

void ManageEmcee();
void ManagePhotobooth();
void ManageCateringItems();
void ManageSuppliersANDResources();

void addNewEmcee(vector<Emcee>& emcees, const string& filename);
void deleteEmcee(vector<Emcee>& emcees, const string& filename);
void addNewPhotobooth(vector<Photobooth>& booths, const string& filename);
void deletePhotobooth(vector<Photobooth>& booths, const string& filename);


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
    cout << string(length, ' ');
}

void Border(int left, int top, int width, int height)
{
    gotoxy(left, top); cout << "O";
    gotoxy(left + width, top); cout << "O";
    gotoxy(left, top + height); cout << "O";
    gotoxy(left + width, top + height); cout << "O";

    for (int x = left + 1; x < left + width; x++) {
        gotoxy(x, top); cout << "-";
        gotoxy(x, top + height); cout << "-";
    }

    for (int y = top + 1; y < top + height; y++) {
        gotoxy(left, y); cout << "|";
        gotoxy(left + width, y); cout << "|";
    }
}

void Clear_Terminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Clear_Getline()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


vector<Emcee> loadEmceesFromCSV(const string& filename)
{
    vector<Emcee> emcees;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return emcees;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, rateStr;
        getline(ss, name, ',');
        getline(ss, rateStr, ',');

        if (!name.empty() && !rateStr.empty()) {
            try {
                emcees.push_back({ name, stod(rateStr) });
            } catch (...) {
                cerr << "Skipping malformed line: " << line << endl;
            }
        }
    }

    file.close();
    return emcees;
}

void saveEmceesToCSV(const string& filename, const vector<Emcee>& emcees)
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "Name,Rate\n";
    for (const auto& e : emcees) {
        file << e.name << "," << e.rate << "\n";
    }

    file.close();
}


vector<Photobooth> loadPhotoboothsFromCSV(const string& filename)
{
    vector<Photobooth> booths;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return booths;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, rateStr;
        getline(ss, name, ',');
        getline(ss, rateStr, ',');

        if (!name.empty() && !rateStr.empty()) {
            try {
                booths.push_back({ name, stod(rateStr) });
            } catch (...) {
                cerr << "Skipping malformed line: " << line << endl;
            }
        }
    }

    file.close();
    return booths;
}

void savePhotoboothsToCSV(const string& filename, const vector<Photobooth>& booths)
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "Name,Rate\n";
    for (const auto& b : booths) {
        file << b.name << "," << b.rate << "\n";
    }

    file.close();
}


void ManageEmcee()
{
    string filename = "C:\\Users\\Axel Carl Nadera\\Desktop\\CP1-project\\Emcees.csv";
    vector<Emcee> emcees = loadEmceesFromCSV(filename);
    int choice = 0;

    while (true) {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(54, 8); cout << "MANAGE EMCEE";
        gotoxy(25, 9); cout << line;
        gotoxy(30, 11); cout << "[1] Add Emcee";
        gotoxy(30, 12); cout << "[2] Remove Emcee";
        gotoxy(30, 13); cout << "[3] Back to Resources Menu";
        gotoxy(30, 15); cout << "Select an option [1-3]: ";
        gotoxy(55, 15);
        cin >> choice;
        Clear_Getline();

        switch (choice) {
        case 1:
            addNewEmcee(emcees, filename);
            break;
        case 2:
            deleteEmcee(emcees, filename);
            break;
        case 3:
            return;
        default:
            gotoxy(30, 17);
            cout << "Invalid choice! Press ENTER...";
            cin.get();
            break;
        }
    }
}


void addNewEmcee(vector<Emcee>& emcees, const string& filename)
{
    Emcee newEmcee;

    Clear_Terminal();
    Border(25, 6, 70, 15);
    string line(61, '=');
    gotoxy(30, 8); cout << line;
    gotoxy(55, 9); cout << "ADD NEW EMCEE";
    gotoxy(30, 10); cout << line;

    gotoxy(35, 12); cout << "Enter Emcee Name: ";
    getline(cin, newEmcee.name);

    while (newEmcee.name.empty()) {
        gotoxy(35, 13); cout << "Name cannot be empty!";
        gotoxy(35, 12); ClearLine(35, 12, 50);
        gotoxy(35, 12); cout << "Enter Emcee Name: ";
        getline(cin, newEmcee.name);
    }

    gotoxy(35, 14); cout << "Enter Emcee Rate: ";
    while (!(cin >> newEmcee.rate)) {
        cin.clear();
        Clear_Getline();
        gotoxy(35, 15); cout << "Invalid input. Try again: ";
        gotoxy(35, 14); ClearLine(35, 14, 50);
        gotoxy(35, 14); cout << "Enter Emcee Rate: ";
    }
    Clear_Getline();

    emcees.push_back(newEmcee);
    saveEmceesToCSV(filename, emcees);

    gotoxy(35, 16);
    cout << "New emcee added successfully!";
    gotoxy(35, 18);
    cout << "Press ENTER to return...";
    cin.get();
}


void deleteEmcee(vector<Emcee>& emcees, const string& filename)
{
    if (emcees.empty()) {
        Clear_Terminal();
        Border(25, 6, 70, 10);
        gotoxy(40, 10);
        cout << "No emcees to delete.";
        gotoxy(40, 12);
        cout << "Press ENTER to return...";
        cin.get();
        return;
    }

    Clear_Terminal();
    Border(20, 4, 85, 22);
    string line(75, '=');
    gotoxy(25, 6); cout << line;
    gotoxy(55, 7); cout << "REMOVE EMCEE";
    gotoxy(25, 8); cout << line;

    for (size_t i = 0; i < emcees.size(); ++i) {
        gotoxy(30, 10 + i);
        cout << i + 1 << ". " << emcees[i].name << " - " << emcees[i].rate;
    }

    gotoxy(30, 11 + emcees.size());
    cout << "Enter number to delete: ";

    int index;
    cin >> index;
    Clear_Getline();

    if (index < 1 || index > (int)emcees.size()) {
        gotoxy(30, 13 + emcees.size());
        cout << "Invalid selection.";
        gotoxy(30, 15 + emcees.size());
        cout << "Press ENTER to continue...";
        cin.get();
        return;
    }

    string deleted = emcees[index - 1].name;
    emcees.erase(emcees.begin() + index - 1);
    saveEmceesToCSV(filename, emcees);

    gotoxy(30, 13 + emcees.size());
    cout << "Deleted Emcee: " << deleted;
    gotoxy(30, 15 + emcees.size());
    cout << "Press ENTER to continue...";
    cin.get();
}


void ManagePhotobooth()
{
    string filename = "C:\\Users\\Axel Carl Nadera\\Desktop\\CP1-project\\Photobooth.csv";
    vector<Photobooth> booths = loadPhotoboothsFromCSV(filename);
    int choice = 0;

    while (true) {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(52, 8); cout << "MANAGE PHOTOBOOTH";
        gotoxy(25, 9); cout << line;
        gotoxy(30, 11); cout << "[1] Add Photobooth";
        gotoxy(30, 12); cout << "[2] Remove Photobooth";
        gotoxy(30, 13); cout << "[3] Back to Resources Menu";
        gotoxy(30, 15); cout << "Select an option [1-3]: ";
        gotoxy(55, 15);
        cin >> choice;
        Clear_Getline();

        switch (choice) {
        case 1:
            addNewPhotobooth(booths, filename);
            break;
        case 2:
            deletePhotobooth(booths, filename);
            break;
        case 3:
            return;
        default:
            gotoxy(30, 17);
            cout << "Invalid choice! Press ENTER...";
            cin.get();
            break;
        }
    }
}


void addNewPhotobooth(vector<Photobooth>& booths, const string& filename)
{
    Photobooth newBooth;

    Clear_Terminal();
    Border(25, 6, 70, 15);
    string line(61, '=');
    gotoxy(30, 8); cout << line;
    gotoxy(52, 9); cout << "ADD NEW PHOTOBOOTH";
    gotoxy(30, 10); cout << line;

    gotoxy(35, 11); cout << "Format: Package Name (Hrs, Prints)";
    gotoxy(35, 12); cout << "Enter Photobooth Package: ";
    getline(cin, newBooth.name);

    while (newBooth.name.empty()) {
        gotoxy(35, 13); cout << "Name cannot be empty!";
        gotoxy(35, 12); ClearLine(35, 12, 50);
        gotoxy(35, 12); cout << "Enter Photobooth Package: ";
        getline(cin, newBooth.name);
    }

    gotoxy(35, 14); cout << "Enter Photobooth Rate: ";
    while (!(cin >> newBooth.rate)) {
        cin.clear();
        Clear_Getline();
        gotoxy(35, 15); cout << "Invalid input. Try again: ";
        gotoxy(35, 14); ClearLine(35, 14, 50);
        gotoxy(35, 14); cout << "Enter Photobooth Rate: ";
    }
    Clear_Getline();

    booths.push_back(newBooth);
    savePhotoboothsToCSV(filename, booths);

    gotoxy(35, 16);
    cout << "New photobooth added successfully!";
    gotoxy(35, 18);
    cout << "Press ENTER to return...";
    cin.get();
}


void deletePhotobooth(vector<Photobooth>& booths, const string& filename)
{
    if (booths.empty()) {
        Clear_Terminal();
        Border(25, 6, 70, 10);
        gotoxy(40, 10);
        cout << "No photobooths to delete.";
        gotoxy(40, 12);
        cout << "Press ENTER to return...";
        cin.get();
        return;
    }

    Clear_Terminal();
    Border(20, 4, 85, 22);
    string line(75, '=');
    gotoxy(25, 6); cout << line;
    gotoxy(52, 7); cout << "REMOVE PHOTOBOOTH";
    gotoxy(25, 8); cout << line;

    for (size_t i = 0; i < booths.size(); ++i) {
        gotoxy(30, 10 + i);
        cout << i + 1 << ". " << booths[i].name << " - " << booths[i].rate;
    }

    gotoxy(30, 11 + booths.size());
    cout << "Enter number to delete: ";

    int index;
    cin >> index;
    Clear_Getline();

    if (index < 1 || index > (int)booths.size()) {
        gotoxy(30, 13 + booths.size());
        cout << "Invalid selection.";
        gotoxy(30, 15 + booths.size());
        cout << "Press ENTER to continue...";
        cin.get();
        return;
    }

    string deleted = booths[index - 1].name;
    booths.erase(booths.begin() + index - 1);
    savePhotoboothsToCSV(filename, booths);

    gotoxy(30, 13 + booths.size());
    cout << "Deleted Photobooth: " << deleted;
    gotoxy(30, 15 + booths.size());
    cout << "Press ENTER to continue...";
    cin.get();
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
        gotoxy(30, 15); cout << "[4] Back to Main Menu";
        gotoxy(30, 17); cout << "Select an option [1-4]: ";
        gotoxy(55, 17);
        cin >> MSR_choice;
        Clear_Getline();

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
            return;
        default:
            gotoxy(30, 19);
            cout << "Invalid input. Please Try again.";
            cin.get();
            break;
        }
    }
}


void ManageCateringItems()
{
    Border(30, 10, 60, 10);
    gotoxy(45, 14);
    cout << "[Catering Management Coming Soon]";
    cin.get();
}


int main()
{
    ManageSuppliersANDResources();
    return 0;
}
