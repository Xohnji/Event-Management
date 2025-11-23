#include "Headers/ManageResources.h"
#include "Headers/Globals.h"
#include "Headers/Ui_Utils.h"

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

using namespace std;



vector<Emcee> loadEmceesFromCSV(const string& filename) {
    vector<Emcee> emcees;
    ifstream file(filename);
    if (!file.is_open()) return emcees;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string name, rateStr;
        getline(ss, name, ',');
        getline(ss, rateStr, ',');
        if (!name.empty() && !rateStr.empty()) {
            emcees.push_back({ name, stod(rateStr) });
        }
    }
    return emcees;
}

void saveEmceesToCSV(const string& filename, const vector<Emcee>& emcees) {
    ofstream file(filename);
    file << "Name,Rate\n";
    for (const auto& e : emcees)
        file << e.name << "," << e.rate << "\n";
}

vector<Photobooth> loadPhotoboothsFromCSV(const string& filename) {
    vector<Photobooth> booths;
    ifstream file(filename);
    if (!file.is_open()) return booths;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string name, rateStr;
        getline(ss, name, ',');
        getline(ss, rateStr, ',');
        if (!name.empty() && !rateStr.empty()) {
            booths.push_back({ name, stod(rateStr) });
        }
    }
    return booths;
}

void savePhotoboothsToCSV(const string& filename, const vector<Photobooth>& booths) {
    ofstream file(filename);
    file << "Name,Rate\n";
    for (const auto& b : booths)
        file << b.name << "," << b.rate << "\n";
}

// === Display Helpers ===
void displayEmceesList(const vector<Emcee>& emcees, int startX, int startY) {
    gotoxy(startX, startY);
    cout << "Existing Emcees:";
    if (emcees.empty()) {
        gotoxy(startX, startY + 1);
        cout << "  [No data found]";
        return;
    }
    for (size_t i = 0; i < emcees.size(); ++i) {
        gotoxy(startX, startY + 1 + i);
        cout << "  " << i + 1 << ". " << emcees[i].name << " - " << emcees[i].rate;
    }
}

void displayPhotoboothList(const vector<Photobooth>& booths, int startX, int startY) {
    gotoxy(startX, startY);
    cout << "Existing Photobooth Packages:";
    if (booths.empty()) {
        gotoxy(startX, startY + 1);
        cout << "  [No data found]";
        return;
    }
    for (size_t i = 0; i < booths.size(); ++i) {
        gotoxy(startX, startY + 1 + i);
        cout << "  " << i + 1 << ". " << booths[i].name << " - " << booths[i].rate;
    }
}


// PARA SA EMCEE MANAGEMENT
void ManageEmcee()
{
    string filename = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Photobooth.csv";
    vector<Emcee> emcees = loadEmceesFromCSV(filename);
    int choice = 0;

    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(53, 8); cout << "MANAGE EMCEE";
        gotoxy(25, 9); cout << line;

        displayEmceesList(emcees, 30, 10);
        gotoxy(30, 12 + emcees.size());
        cout << "[1] Add Emcee";
        gotoxy(30, 13 + emcees.size());
        cout << "[2] Remove Emcee";
        gotoxy(30, 14 + emcees.size());
        cout << "[3] Back";
        gotoxy(30, 16 + emcees.size());
        cout << "Select an option [1-3]: ";
        cin >> choice;
        Clear_Getline();

        switch (choice) {
        case 1: addNewEmcee(emcees, filename); break;
        case 2: deleteEmcee(emcees, filename); break;
        case 3: return;
        default:
            gotoxy(30, 18 + emcees.size());
            cout << "Invalid choice! Press ENTER...";
            cin.get();
        }
        emcees = loadEmceesFromCSV(filename);
    }
}

void addNewEmcee(vector<Emcee>& emcees, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(53, 8); cout << "ADD NEW EMCEE";
        gotoxy(25, 9); cout << line;

        displayEmceesList(emcees, 30, 11);
        gotoxy(30, 13 + emcees.size());
        cout << "[0] Go Back";
        gotoxy(30, 14 + emcees.size());
        cout << "Enter Emcee Name: ";
        Emcee e;
        getline(cin, e.name);
        if (e.name == "0") return;
        gotoxy(30, 15 + emcees.size());
        cout << "Enter Rate: ";
        if (!(cin >> e.rate)) {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();
        emcees.push_back(e);
        saveEmceesToCSV(filename, emcees);
        gotoxy(30, 17 + emcees.size());
        cout << "Added successfully! Press ENTER...";
        cin.get();
        return;
    }
}

void deleteEmcee(vector<Emcee>& emcees, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(53, 8); cout << "REMOVE EMCEE";
        gotoxy(25, 9); cout << line;

        displayEmceesList(emcees, 30, 10);
        gotoxy(30, 12 + emcees.size());
        cout << "[0] Go Back";
        gotoxy(30, 13 + emcees.size());
        cout << "Enter number to delete: ";
        int idx; cin >> idx; Clear_Getline();
        if (idx == 0) return;
        if (idx < 1 || idx > (int)emcees.size()) continue;
        emcees.erase(emcees.begin() + idx - 1);
        saveEmceesToCSV(filename, emcees);
        gotoxy(30, 15 + emcees.size());
        cout << "Deleted successfully! Press ENTER...";
        cin.get();
        return;
    }
}



// PARA SA PHOTOBOOTH MANAGEMENT
void ManagePhotobooth()
{
    string filename = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Photobooth.csv";
    vector<Photobooth> booths = loadPhotoboothsFromCSV(filename);
    int choice = 0;

    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(51, 8);
        cout << "MANAGE PHOTOBOOTH";
        gotoxy(25, 9);
        cout << line;

        displayPhotoboothList(booths, 30, 10);
        gotoxy(30, 12 + booths.size());
        cout << "[1] Add Photobooth";
        gotoxy(30, 13 + booths.size());
        cout << "[2] Remove Photobooth";
        gotoxy(30, 14 + booths.size());
        cout << "[3] Back";
        gotoxy(30, 16 + booths.size());
        cout << "Select [1-3]: ";
        cin >> choice;
        Clear_Getline();

        switch (choice)
        {
        case 1:
            addNewPhotobooth(booths, filename);
            break;
        case 2:
            deletePhotobooth(booths, filename);
            break;
        case 3:
            Clear_Terminal();
            return;
        default:
            gotoxy(30, 18 + booths.size());
            cout << "Invalid choice! Press ENTER...";
            cin.get();
            break;
        }
        booths = loadPhotoboothsFromCSV(filename);
    }
}

void addNewPhotobooth(vector<Photobooth>& booths, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(51, 8);
        cout << "ADD NEW PHOTOBOOTH";
        gotoxy(25, 9);
        cout << line;

        displayPhotoboothList(booths, 30, 11);
        gotoxy(30, 13 + booths.size());
        cout << "[0] Go Back";
        gotoxy(30, 14 + booths.size());
        cout << "Enter Package Name: ";
        Photobooth p;
        getline(cin, p.name);
        if (p.name == "0") return;
        gotoxy(30, 15 + booths.size());
        cout << "Enter Rate: ";
        if (!(cin >> p.rate)) {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();
        booths.push_back(p);
        savePhotoboothsToCSV(filename, booths);
        gotoxy(30, 17 + booths.size());
        cout << "Added successfully! Press ENTER...";
        cin.get();
        return;
    }
}

void deletePhotobooth(vector<Photobooth>& booths, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(51, 8);
        cout << "REMOVE PHOTOBOOTH";
        gotoxy(25, 9);
        cout << line;

        displayPhotoboothList(booths, 30, 10);
        gotoxy(30, 12 + booths.size());
        cout << "[0] Go Back";
        gotoxy(30, 13 + booths.size());
        cout << "Enter number to delete: ";
        int idx; cin >> idx; Clear_Getline();
        if (idx == 0) return;
        if (idx < 1 || idx > (int)booths.size()) continue;
        booths.erase(booths.begin() + idx - 1);
        savePhotoboothsToCSV(filename, booths);
        gotoxy(30, 15 + booths.size());
        cout << "Deleted successfully! Press ENTER...";
        cin.get();
        return;
    }
}



// PARA SA CATERING PACKAGE
// struct helper para sa csv manipulation


vector<CateringPackage> loadCateringFromCSV(const string& filename)
{
    vector<CateringPackage> packages;
    ifstream file(filename);
    if (!file.is_open()) return packages;
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string name, rateStr, desc, appStr, entStr, bevStr, desStr;
        getline(ss, name, ',');
        getline(ss, rateStr, ',');
        getline(ss, desc, ',');
        getline(ss, appStr, ',');
        getline(ss, entStr, ',');
        getline(ss, bevStr, ',');
        getline(ss, desStr, ',');
        if (!name.empty() && !rateStr.empty())
        {
            packages.push_back({ name, stod(rateStr), desc,
                                 stoi(appStr), stoi(entStr),
                                 stoi(bevStr), stoi(desStr) });
        }
    }
    return packages;
}

void saveCateringToCSV(const string& filename, const vector<CateringPackage>& packages)
{
    ofstream file(filename);
    file << "Name,Rate Per Pax,Description,Appetizer Count,Entree Count,Beverage Count,Dessert Count\n";
    for (const auto& p : packages)
        file << p.name << "," << p.ratePerPax << "," << p.description << ","
             << p.appetizerCount << "," << p.entreeCount << ","
             << p.beverageCount << "," << p.dessertCount << "\n";
}

void displayCateringPackagesList(const vector<CateringPackage>& packages, int startX, int startY)
{
    gotoxy(startX, startY);
    cout << "Existing Catering Packages:";
    if (packages.empty()) {
        gotoxy(startX, startY + 1);
        cout << "  [No data found]";
        return;
    }
    for (size_t i = 0; i < packages.size(); ++i) {
        gotoxy(startX, startY + 1 + (i * 2));
        cout << "  " << i + 1 << ". " << packages[i].name << " - " << packages[i].ratePerPax;
        gotoxy(startX, startY + 2 + (i * 2));
        cout << "     " << packages[i].description;
    }
}

void addNewCateringPackage(vector<CateringPackage>& packages, const string& filename)
{
    while (true) {
        Clear_Terminal();
        Border(20, 5, 80, 20);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(47, 8);
        cout << "ADD NEW CATERING PACKAGE";
        gotoxy(25, 9);
        cout << line;

        displayCateringPackagesList(packages, 30, 11);

        gotoxy(30, 13 + packages.size() * 2);
        cout << "[0] Go Back";
        gotoxy(30, 14 + packages.size() * 2);
        cout << "Enter Package Name: ";
        CateringPackage p;
        getline(cin, p.name);
        if (p.name == "0") return;

        gotoxy(30, 15 + packages.size() * 2);
        cout << "Enter Rate Per Pax: ";
        if (!(cin >> p.ratePerPax))
        {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();

        gotoxy(30, 16 + packages.size() * 2);
        cout << "Enter Description: ";
        getline(cin, p.description);

        gotoxy(30, 17 + packages.size() * 2);
        cout << "Number of Appetizers: ";
        cin >> p.appetizerCount;
        gotoxy(30, 18 + packages.size() * 2);
        cout << "Number of Entrees: ";
        cin >> p.entreeCount;
        gotoxy(30, 19 + packages.size() * 2);
        cout << "Number of Beverages: ";
        cin >> p.beverageCount;
        gotoxy(30, 20 + packages.size() * 2);
        cout << "Number of Desserts: ";
        cin >> p.dessertCount;
        Clear_Getline();

        packages.push_back(p);
        saveCateringToCSV(filename, packages);
        gotoxy(30, 22 + packages.size() * 2);
        cout << "Added successfully! Press ENTER...";
        cin.get();
        return;
    }
}

void deleteCateringPackage(vector<CateringPackage>& packages, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 18);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(48, 8); cout << "REMOVE CATERING PACKAGE";
        gotoxy(25, 9); cout << line;

        displayCateringPackagesList(packages, 30, 10);
        gotoxy(30, 12 + packages.size() * 2);
        cout << "[0] Go Back";
        gotoxy(30, 13 + packages.size() * 2);
        cout << "Enter number to delete: ";

        int idx; 
        if (!(cin >> idx))
        {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();
        if (idx == 0) return;
        if (idx < 1 || idx > (int)packages.size()) continue;

        packages.erase(packages.begin() + idx - 1);
        saveCateringToCSV(filename, packages);
        gotoxy(30, 15 + packages.size() * 2);
        cout << "Deleted successfully! Press ENTER...";
        cin.get();
        return;
    }
}

void ManageCateringPackages()
{
    const string filename = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Catering_package.csv";
    vector<CateringPackage> packages = loadCateringFromCSV(filename);
    int choice = 0;

    while (true)
    {
        Clear_Terminal();
        Border(20, 5, 80, 22);
        string line(71, '=');
        gotoxy(25, 7); cout << line;
        gotoxy(50, 8); cout << "MANAGE CATERING PACKAGES";
        gotoxy(25, 9); cout << line;

        displayCateringPackagesList(packages, 30, 10);
        gotoxy(30, 12 + packages.size() * 2);
        cout << "[1] Add Package";
        gotoxy(30, 13 + packages.size() * 2);
        cout << "[2] Remove Package";
        gotoxy(30, 14 + packages.size() * 2);
        cout << "[3] Back";
        gotoxy(30, 16 + packages.size() * 2);
        cout << "Select [1-3]: ";

        cin >> choice;
        Clear_Getline();

        switch (choice)
        {
            case 1: addNewCateringPackage(packages, filename);
                break;
            case 2: deleteCateringPackage(packages, filename);
                break;
            case 3:
                return;
            default:
                gotoxy(30, 18 + packages.size() * 2);
                cout << "Invalid choice! Press ENTER...";
                cin.get();
                break;
        }
        packages = loadCateringFromCSV(filename);
    }
}





void displayCateringMenuList(const vector<CateringMenuItem>& menu, int startX, int startY)
{
    gotoxy(startX, startY);
    cout << "Existing Menu Items:";
    if (menu.empty()) {
        gotoxy(startX, startY + 1);
        cout << "  [No data found]";
        return;
    }
    for (size_t i = 0; i < menu.size(); ++i)
    {
        gotoxy(startX, startY + 1 + i);
        cout << "  " << i + 1 << ". [" << menu[i].category << "] " << menu[i].itemName;
    }
}

vector<CateringMenuItem> loadCateringMenuFromCSV(const string& filename)
{
    vector<CateringMenuItem> menu;
    ifstream file(filename);
    if (!file.is_open()) return menu;
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string category, item;
        getline(ss, category, ',');
        getline(ss, item, ',');
        if (!category.empty() && !item.empty())
            menu.push_back({ category, item });
    }
    return menu;
}

void saveCateringMenuToCSV(const string& filename, const vector<CateringMenuItem>& menu)
{
    ofstream file(filename);
    file << "Category,Item Name\n";
    for (const auto& m : menu)
        file << m.category << "," << m.itemName << "\n";
}

void addNewCateringMenuItem(vector<CateringMenuItem>& menu, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(10, 3, 120, 35);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(50, 8);
        cout << "ADD NEW MENU ITEM";
        gotoxy(25, 9);
        cout << line;

        displayCateringMenuList(menu, 30, 11);
        gotoxy(30, 13 + menu.size());
        cout << "[0] Go Back";
        gotoxy(30, 14 + menu.size());
        cout << "Enter Category: ";
        CateringMenuItem item;
        getline(cin, item.category);
        if (item.category == "0") return;
        gotoxy(30, 15 + menu.size());
        cout << "Enter Item Name: ";
        getline(cin, item.itemName);
        if (item.itemName == "0") return;
        if (item.category.empty() || item.itemName.empty()) continue;

        menu.push_back(item);
        saveCateringMenuToCSV(filename, menu);
        gotoxy(30, 17 + menu.size());
        cout << "Added successfully! Press ENTER...";
        cin.get();
        return;
    }
}

void deleteCateringMenuItem(vector<CateringMenuItem>& menu, const string& filename)
{
    while (true)
    {
        Clear_Terminal();
        Border(10, 3, 120, 35);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(49, 8);
        cout << "REMOVE MENU ITEM";
        gotoxy(25, 9);
        cout << line;

        displayCateringMenuList(menu, 30, 10);
        gotoxy(30, 12 + menu.size());
        cout << "[0] Go Back";
        gotoxy(30, 13 + menu.size());
        cout << "Enter number to delete: ";

        int idx;
        if (!(cin >> idx))
        {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();

        if (idx == 0) return;
        if (idx < 1 || idx > (int)menu.size()) continue;

        menu.erase(menu.begin() + idx - 1);
        saveCateringMenuToCSV(filename, menu);
        gotoxy(30, 15 + menu.size());
        cout << "Deleted successfully! Press ENTER...";
        cin.get();
        return;
    }
}

void ManageCateringItems()
{
    const string filename = "C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\CATERING_Menu.csv";
    vector<CateringMenuItem> menu = loadCateringMenuFromCSV(filename);
    int choice = 0;

    while (true)
    {
        Clear_Terminal();
        Border(10, 3, 120, 35);
        string line(71, '=');
        gotoxy(25, 7);
        cout << line;
        gotoxy(51, 8);
        cout << "MANAGE CATERING ITEMS";
        gotoxy(25, 9);
        cout << line;

        displayCateringMenuList(menu, 30, 10);

        gotoxy(30, 12 + menu.size());
        cout << "[1] Add Menu Item";
        gotoxy(30, 13 + menu.size());
        cout << "[2] Remove Menu Item";
        gotoxy(30, 14 + menu.size());
        cout << "[3] Back";
        gotoxy(30, 16 + menu.size());
        cout << "Select [1-3]: ";

        if (!(cin >> choice))
        {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();

        switch (choice)
        {
            case 1: addNewCateringMenuItem(menu, filename);
                break;
            case 2: deleteCateringMenuItem(menu, filename);
                break;
            case 3:
                return;
            default:
                gotoxy(30, 18 + menu.size());
                cout << "Invalid choice! Press ENTER...";
                cin.get();
                break;
        }
        menu = loadCateringMenuFromCSV(filename);
    }
}





void ManageSuppliersANDResources()
{
    int choice = 0;
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

        gotoxy(30, 11);
        cout << "[1] Manage Emcee";
        gotoxy(30, 12);
        cout << "[2] Manage Photobooth";
        gotoxy(30, 13);
        cout << "[3] Manage Catering Packages";
        gotoxy(30, 14);
        cout << "[4] Manage Catering Menu";
        gotoxy(30, 15);
        cout << "[5] Exit";
        gotoxy(30, 17);
        cout << "Select [1-5]: ";

        if (!(cin >> choice))
        {
            cin.clear();
            Clear_Getline();
            continue;
        }
        Clear_Getline();

        switch (choice)
        {
        case 1: ManageEmcee();
            break;
        case 2: ManagePhotobooth();
            break;
        case 3: ManageCateringPackages();
            break;
        case 4: ManageCateringItems();
            break;
        case 5:
            return;
        default:
            gotoxy(30, 19);
            cout << "Invalid choice! Press ENTER...";
            cin.get();
            break;
        }
    }
}





