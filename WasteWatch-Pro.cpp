#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class MenuOptions
{
    OPTION_1,
    OPTION_2,
    OPTION_3,
    HELP,
    EXIT
};

// Function to dsiplay the menu
void displayMenu()
{
    // Define menu options
    vector<string> menuOptions = {
        "1. Option 1",
        "2. Option 2",
        "3. Option 3",
        "4. Help",
        "5. Exit"};

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
            cout << "You chose option 1." << endl;
        }
        else if (menuSelection == "2")
        {
            cout << "You chose option 2." << endl;
        }
        else if (menuSelection == "3")
        {
            cout << "You chose option 3." << endl;
        }
        else if (menuSelection == "4" || menuSelection == "help" || menuSelection == "Help" || menuSelection == "?")
        {
            cout << "\nTo choose a menu option, simply enter the number of the option you want." << endl;
            cout << "For example, to choose Option 1, you would enter \"1\".\n"
                 << endl;
            cout << "To exit, you can also press \"q\", \"quit\", or \"exit\".\n"
                 << endl;
            cout << "Additionally, for help you can type \"help\", \"Help\", \"?\" for help)";
        }
        else if (menuSelection == "5" || menuSelection == "q" || menuSelection == "quit" || menuSelection == "exit")
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