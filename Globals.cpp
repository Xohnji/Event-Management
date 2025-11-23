#include "Headers/Globals.h"

#include <string>

// Definition of the global variable with initial value
std::string csvToUse = ("C:\\Users\\DarkS\\Downloads\\Proj files\\SP\\Code Catalyst\\Final Please finish\\1.0.8\\Mock_Data.csv");

// Global variable definitions
int MMchoice, SAchoice;
std::string ClientName, ClientNum, ClientAddress;
std::string EventType, EventDate, EventTime, Venue, ClientLandmarks;
int PaxAmount, ClientID;
double TotalServiceCost, baseCateringCost, emceeCost, photoboothCost, venueSetupCost, manualExpenseCost;

std::vector<std::string> chosenEntrees, chosenAppetizers, chosenDrinks, chosenDesserts;
std::vector<std::string> chosenEmcee;
std::vector<double> chosenEmceeRate;
std::vector<std::string> chosenPhotoboothPackage;
std::vector<double> chosenPhotoboothRate;
std::vector<std::string> designNotes;
std::vector<double> chosendesignCost;
std::vector<std::string> manualExpenseEntry;
std::vector<double> manualExpenseAmount;


std::vector<PaymentLog> paymentHistory;
std::vector<int> PayID;
std::vector<std::string> PayDate;
std::vector<double> PayAmount;
std::vector<std::string> PayRemarks;
std::vector<std::string> PayStatus;

double totalPaid = 0;
int paymentCounter = 0;
