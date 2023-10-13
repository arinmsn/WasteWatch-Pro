#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class MenuOptions
{
    REGISTRATION,
    WASTE_TRACKING,
    REPORTS,
    ENVIRONMENTAL_IMPACT,
    ETHICAL_CONSIDERATIONS,
    DATA_STORAGE_PRIVACY,
    HELP,
    EXIT
};

// Function to dsiplay the menu
void displayMenu()
{
    // Define menu options
    vector<string> menuOptions = {
        "1) User registration",
        "2) Waste tracking",
        "3) Reports",
        "4) Environmental Impact Information",
        "5) Ethical Considerations",
        "6) Data Storage and Privacy",
        "7) Help",
        "8) Exit"};

    cout << "\n\t-----     WastWath Pro 1.0     -----\n"
         << endl;
    for (const string &option : menuOptions)
    {
        cout << option << endl;
    }
}

int main()
{
    // Display the menu to user
    displayMenu();

    // Get the user's menu selection
    string menuSelection;
    while (true)
    {
        cout << "\nEnter a menu option: ";
        cin >> menuSelection;

        if (menuSelection == "1")
        {
            cout << "You chose User registration." << endl;
        }
        else if (menuSelection == "2")
        {
            cout << "You chose Waste tracking." << endl;
        }
        else if (menuSelection == "3")
        {
            cout << "You chose Reports." << endl;
        }
        else if (menuSelection == "4")
        {
            cout << "You chose Environmental Impact Information." << endl;
        }
        else if (menuSelection == "5")
        {
            cout << "You chose Ethical Considerations." << endl;
        }
        else if (menuSelection == "6")
        {
            cout << "You chose Data Storage and Privacy." << endl;
        }
        else if (menuSelection == "7" || menuSelection == "help" || menuSelection == "Help" || menuSelection == "?")
        {
            cout << "\nTo choose a menu option, simply enter the number of the option you want." << endl;
            cout << "For example, to choose User registration, you would enter \"1\".\n"
                 << endl;
            cout << "To exit, you can also press \"8\", \"q\", \"quit\", or \"exit\".\n"
                 << endl;
            cout << "Additionally, for help you can type \"help\", \"Help\", \"?\" for help)" << endl;
        }
        else if (menuSelection == "8" || menuSelection == "q" || menuSelection == "quit" || menuSelection == "exit")
        {
            // Exit the program
            cout << "Exiting..." << endl;
            break;
        }
        else
        {
            cout << "\nInvalid menu selection! Please try again.\n"
                 << endl;
        }
    }
    return 0;
};