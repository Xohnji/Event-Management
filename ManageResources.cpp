
// Manage suppliers & Resources
void ManageSuppliersANDResources();
void ManageEmcee();
void ManagePhotobooth();
void ManageCateringItems();
void ManageDecorations();




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
