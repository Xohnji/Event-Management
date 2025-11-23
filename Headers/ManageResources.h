#ifndef MANAGERESOURCES_H
#define MANAGERESOURCES_H

#include <vector>
#include <string>

using std::string;
using std::vector;

struct Emcee {
    string name;
    double rate;
};

struct Photobooth {
    string name;
    double rate;
};

struct CateringPackage
{
    string name;
    double ratePerPax;
    string description;
    int appetizerCount;
    int entreeCount;
    int beverageCount;
    int dessertCount;
};

struct CateringMenuItem
{
    string category;
    string itemName;
};

vector<CateringMenuItem> loadCateringMenuFromCSV(const string& filename);
vector<CateringPackage> loadCateringFromCSV(const string& filename);
vector<Emcee> loadEmceesFromCSV(const string& filename);
vector<Photobooth> loadPhotoboothsFromCSV(const string& filename);

vector<CateringMenuItem> loadCateringMenuFromCSV(const string& filename);
void saveCateringMenuToCSV(const string& filename, const vector<CateringMenuItem>& menu);
void addNewCateringMenuItem(vector<CateringMenuItem>& menu, const string& filename);
void deleteCateringMenuItem(vector<CateringMenuItem>& menu, const string& filename);

vector<CateringPackage> loadCateringFromCSV(const string& filename);
void saveCateringToCSV(const string& filename, const vector<CateringPackage>& packages);
void addNewCateringPackage(vector<CateringPackage>& packages, const string& filename);
void deleteCateringPackage(vector<CateringPackage>& packages, const string& filename);
void displayCateringPackagesList(const vector<CateringPackage>& packages, int startX, int startY);

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

#endif