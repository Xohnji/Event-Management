#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <vector>

extern std::string csvToUse;
extern int MMchoice, SAchoice, ClientID;
extern std::string ClientName, ClientNum, ClientAddress;
extern std::string EventType, EventDate, EventTime, Venue, ClientLandmarks;
extern int PaxAmount;
extern double TotalServiceCost;
extern double baseCateringCost;
extern double emceeCost;
extern double photoboothCost;
extern double venueSetupCost;
extern double manualExpenseCost;


// Global Initialization for chosen ITEMS storage:
//CATERING:
extern std::vector<std::string>chosenEntrees, chosenAppetizers, chosenDrinks, chosenDesserts;
extern std::string chosenCateringPackage;
//EMCEE & PHOTOBOOTH:
extern std::vector<std::string> chosenEmcee;
//PHOTOBOOTH:
extern std::vector<std::string> chosenPhotoboothPackage;
//VENUE SETUP:
extern std::vector<std::string> designNotes;
//MANUAL EXPENSE LEDGER
extern std::vector<std::string> manualExpenseEntry;
extern std::vector<double> chosenEmceeRate, chosenPhotoboothRate, chosendesignCost, manualExpenseAmount;


//FINANCIAL CONTROL MENU INITIALIZATION
struct PaymentLog {
    int paymentID;
    std::string date;
    double amount;
    std::string remarks;
    std::string status;
};

extern std::vector<PaymentLog> paymentHistory;
extern std::vector<int> PayID;
extern std::vector<std::string> PayDate;
extern std::vector<double> PayAmount;
extern std::vector<std::string> PayRemarks;
extern std::vector<std::string> PayStatus;
extern double totalPaid;
extern int paymentCounter;

void ResetBookingData();

#endif
