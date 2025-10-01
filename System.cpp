#include <iostream>
#include <cstdlib>

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
        std::cout << "=========================================" << std::endl;
        std::cout << "|            SYSTEM TESTING            |" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "| 1. New Bookings.                     |" << std::endl;
        std::cout << "| 2. Manage Bookings.                  |" << std::endl;
        std::cout << "| 3. Calendar.                         |" << std::endl;
        std::cout << "| 4. Exit System.                      |" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << std::endl;
        std::cout << "Select an option: ";

        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
        Choice = 0;
        } else {
        Choice = std::stoi(input); //ibig sabihin ng 'stoi' is para i convert nya yung string to integer -AXEL.
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
                std::cout << "Number is not assigned to any choices / Choice is not an option. " << std::endl;
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
    std::cout << "=========================================" << std::endl;
    std::cout << "|        CLIENT INFORMATION            |" << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Enter Client Name: ";
    std::getline(std::cin, ClientName);

    std::cout << "Enter Contact Number: ";
    std::getline(std::cin, ClientNum);

    std::cout << "Enter Client Address: ";
    std::getline(std::cin, ClientAddress);

    std::cout << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "|           EVENT DETAILS              |" << std::endl;
    std::cout << "=========================================" << std::endl;

    std::cout << "Enter Venue: ";
    std::getline(std::cin, Venue);

    std::cout << "Enter Date: ";
    std::getline(std::cin, EventDate);

    std::cout << "Enter Time: ";
    std::getline(std::cin, EventTime);
}

void Checkk_Bookings() {
    //Insert Data Base. Wait for data base.
}

void Manage_Bookings() {
    std::string input;
    int ChoiceManage;

    std::cout << "=========================================" << std::endl;
    std::cout << "|          MANAGE BOOKINGS             |" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "| 1. Check Bookings                    |" << std::endl;
    std::cout << "| 2. Update Bookings                   |" << std::endl;
    std::cout << "| 3. Back to menu                      |" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Select an option: ";
    std::getline(std::cin, input);
    if (input.empty()) return;
    ChoiceManage = std::stoi(input);

    std::cout << std::endl;

    switch (ChoiceManage) {
        case 1:
            Clear_Terminal();
            std::cout << "=========================================" << std::endl;
            std::cout << "|           CHECK BOOKINGS             |" << std::endl;
            std::cout << "=========================================" << std::endl;
            Checkk_Bookings();
            break;

        case 2:
            Clear_Terminal();
            std::cout << "=========================================" << std::endl;
            std::cout << "|           UPDATE BOOKINGS            |" << std::endl;
            std::cout << "=========================================" << std::endl;
            break;

        case 3:
            Clear_Terminal();
            break;

        default:
            Clear_Terminal();
            std::cout << "Number is not assigned to any choices / Choice is not an option. " << std::endl;
            break;
    }
}

void Upcoming_Calendar() {
    std::cout << "=========================================" << std::endl;
    std::cout << "|               CALENDAR               |" << std::endl;
    std::cout << "=========================================" << std::endl;
}
