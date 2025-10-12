#include <iostream>
#include <cstdlib>

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

int Choice;
std::string ClientName, ClientAddress, ClientInfo, Venue, Schedule, Resources, EventTime, EventDate;
std::string ClientNum;

void Clear_Terminal();
void Booking();
void Checkk_Bookings();
void Manage_Bookings();
void Upcoming_Calendar();

int main() {
    while (true) {
        std::cout << CYAN << "=========================================" << RESET << std::endl;
        std::cout << BOLD << GREEN << "|            SYSTEM TESTING             |" << RESET << std::endl;
        std::cout << CYAN << "=========================================" << RESET << std::endl;
        std::cout << YELLOW << "| 1. New Bookings.                      |" << RESET << std::endl;
        std::cout << YELLOW << "| 2. Manage Bookings.                   |" << RESET << std::endl;
        std::cout << YELLOW << "| 3. Calendar.                          |" << RESET << std::endl;
        std::cout << YELLOW << "| 4. Exit System.                       |" << RESET << std::endl;
        std::cout << CYAN << "=========================================" << RESET << std::endl;
        std::cout << std::endl;
        std::cout << BOLD << "Select an option: " << RESET;

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            Choice = 0;
        } else {
            Choice = std::stoi(input);
        }

        std::cout << std::endl;

        switch (Choice) {
            case 1:
                Clear_Terminal();
                Booking();
                break;

            case 2:
                Clear_Terminal();
                Manage_Bookings();
                break;

            case 3:
                Clear_Terminal();
                Upcoming_Calendar();
                break;

            case 4:
                Clear_Terminal();
                return 0;

            default:
                Clear_Terminal();
                std::cout << RED << "Number is not assigned to any choices / Choice is not an option. " << RESET << std::endl;
                break;
        }
    }

    return 0;
}

void Clear_Terminal() {
#ifdef _WIN32
    system("cls");
#else 
    system("clear");
#endif
}

void Booking() {
    std::cout << CYAN << "=========================================" << RESET << std::endl;
    std::cout << BOLD << GREEN << "|        CLIENT INFORMATION             |" << RESET << std::endl;
    std::cout << CYAN << "=========================================" << RESET << std::endl;

    std::cout << BOLD << "Enter Client Name: " << RESET;
    std::getline(std::cin, ClientName);

    std::cout << BOLD << "Enter Contact Number: " << RESET;
    std::getline(std::cin, ClientNum);

    std::cout << BOLD << "Enter Client Address: " << RESET;
    std::getline(std::cin, ClientAddress);

    std::cout << std::endl;
    std::cout << CYAN << "=========================================" << RESET << std::endl;
    std::cout << BOLD << GREEN << "|           EVENT DETAILS               |" << RESET << std::endl;
    std::cout << CYAN << "=========================================" << RESET << std::endl;

    std::cout << BOLD << "Enter Venue: " << RESET;
    std::getline(std::cin, Venue);

    std::cout << BOLD << "Enter Date: " << RESET;
    std::getline(std::cin, EventDate);

    std::cout << BOLD << "Enter Time: " << RESET;
    std::getline(std::cin, EventTime);
}

void Checkk_Bookings() {
    //Insert Data Base. Wait for data base.
}

void Manage_Bookings() {
    std::string input;
    int ChoiceManage;

    std::cout << CYAN << "=========================================" << RESET << std::endl;
    std::cout << BOLD << GREEN << "|          MANAGE BOOKINGS              |" << RESET << std::endl;
    std::cout << CYAN << "=========================================" << RESET << std::endl;
    std::cout << YELLOW << "| 1. Check Bookings                     |" << RESET << std::endl;
    std::cout << YELLOW << "| 2. Update Bookings                    |" << RESET << std::endl;
    std::cout << YELLOW << "| 3. Back to menu                       |" << RESET << std::endl;
    std::cout << CYAN << "=========================================" << RESET << std::endl;
    std::cout << std::endl;

    std::cout << BOLD << "Select an option: " << RESET;
    std::getline(std::cin, input);
    if (input.empty()) return;
    ChoiceManage = std::stoi(input);

    std::cout << std::endl;

    switch (ChoiceManage) {
        case 1:
            Clear_Terminal();
            std::cout << CYAN << "=========================================" << RESET << std::endl;
            std::cout << BOLD << GREEN << "|           CHECK BOOKINGS              |" << RESET << std::endl;
            std::cout << CYAN << "=========================================" << RESET << std::endl;
            Checkk_Bookings();
            break;

        case 2:
            Clear_Terminal();
            std::cout << CYAN << "=========================================" << RESET << std::endl;
            std::cout << BOLD << GREEN << "|           UPDATE BOOKINGS             |" << RESET << std::endl;
            std::cout << CYAN << "=========================================" << RESET << std::endl;
            break;

        case 3:
            Clear_Terminal();
            break;

        default:
            Clear_Terminal();
            std::cout << RED << "Number is not assigned to any choices / Choice is not an option. " << RESET << std::endl;
            break;
    }
}

void Upcoming_Calendar() {
    std::cout << CYAN << "=========================================" << RESET << std::endl;
    std::cout << BOLD << GREEN << "|               CALENDAR                |" << RESET << std::endl;
    std::cout << CYAN << "=========================================" << RESET << std::endl;
}
