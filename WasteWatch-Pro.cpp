#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

const string USER_DATA_FILE = "user_data.txt";

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

class UserData
{
public:
    // Constructor initializing counts to zero
    UserData() : recyclablesCount(0), nonRecyclablesCount(0) {}

    // Getter for recyclables count
    int getRecyclablesCount() const
    {
        return recyclablesCount;
    }

    // Getter for non-recyclables count
    int getNonRecyclablesCount() const
    {
        return nonRecyclablesCount;
    }

    // Method to increment the recyclables count
    void incrementRecyclablesCount(int count)
    {
        recyclablesCount += count;
    }

    // Method to increment the non-recyclables count
    void incrementNonRecyclablesCount(int count)
    {
        nonRecyclablesCount += count;
    }

    // Getter for user name
    const string &getName() const
    {
        return name;
    }

    // Setter for user name
    void setName(const string &n)
    {
        name = n;
    }

private:
    int recyclablesCount;    // Store the count of recyclables
    int nonRecyclablesCount; // Store the count of non-recyclables
    string name;             // Store the user name
};

// Function to register a new user
void registerUser(map<int, UserData> &userDatabase)
{

    string name;
    cout << "User Registration\n";
    cout << "Enter your name (or 'q' to quit): ";
    getline(cin, name);

    if (name == "q" || name == "Q")
    {
        // User wishes to quit the registration
        return;
    }

    // Determine next user ID
    int nextUserID = userDatabase.empty() ? 1000 : userDatabase.rbegin()->first + 1;

    // Create new user data and insert it into the map
    UserData newUser;
    newUser.setName(name);
    userDatabase[nextUserID] = newUser;
    cout << "User registered successfully with userID " << nextUserID << ".\n";

    // Give option to register another user
    cout << "Register another user? (Y/N): ";
    char choice;
    cin >> choice;
    cin.ignore();
    if (choice == 'y' || choice == 'Y')
    {
        registerUser(userDatabase);
    }
}

// Function to track user data
void trackUserData(const map<int, UserData> &userDatabase)
{
    int userID;
    cout << "Enter your User ID: ";
    cin >> userID;
    cin.ignore();

    // Find the user in the database
    auto it = userDatabase.find(userID);

    // Check if the user exists
    if (it != userDatabase.end())
    {
        cout << "User ID: " << it->first << "\n";
        cout << "Name: " << it->second.getName() << "\n";
        cout << "Recyclables Count: " << it->second.getRecyclablesCount() << "\n";
        cout << "Non-Recyclables Count: " << it->second.getNonRecyclablesCount() << "\n";
    }
    else
    {
        cerr << "Error: User ID not found.\n";
    }
}

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

// Function to handle Waste Tracking
void handleWasteTracking(map<int, UserData> &userDatabase)
{
    int userID;
    cout << "Enter your User ID: ";
    cin >> userID;
    cin.ignore();

    // Find the user in the database
    auto it = userDatabase.find(userID);

    // Check if the user exists
    if (it != userDatabase.end())
    {
        cout << "User ID: " << it->first << "\n";
        cout << "Name: " << it->second.getName() << "\n";
        cout << "Recyclables Count: " << it->second.getRecyclablesCount() << "\n";
        cout << "Non-Recyclables Count: " << it->second.getNonRecyclablesCount() << "\n";
    }
    else
    {
        cerr << "Error: User ID not found.\n";
    }
}

int main()
{
    map<int, UserData> userDatabase;

    // Read existing user data from file
    ifstream inputFile(USER_DATA_FILE);
    if (!inputFile.is_open())
    {
        cerr << "Error: Failed to open user data file." << endl;
        ofstream newFile(USER_DATA_FILE.c_str()); // Create a new file
        newFile.close();
    }

    if (inputFile.is_open())
    {
        string line;
        // Read each line of the file
        while (getline(inputFile, line))
        {
            istringstream lineStream(line);

            int userID, recyclablesCount, nonRecyclablesCount;
            string name;

            // Extract userID from line
            if (!(lineStream >> userID))
            {
                cerr << "Error: Failed to read userID from line: " << line << "\n";
                continue; // Skip to the next iteration
            }

            // Extract user name (enclosed in quotes) from line
            if (!(lineStream >> ws && getline(lineStream, name, '"') && getline(lineStream, name, '"')))
            {
                cerr << "Error: Failed to read name from line: " << line << "\n";
                continue; // Skip to the next iteration
            }

            // Extract recyclables and non-recyclables counts from line
            if (!(lineStream >> recyclablesCount >> nonRecyclablesCount))
            {
                cerr << "Error: Failed to read counts from line: " << line << "\n";
                continue; // Skip to the next iteration
            }

            // Populate the user data and insert it into the map
            UserData userData;
            userData.setName(name);
            userData.incrementRecyclablesCount(recyclablesCount);
            userData.incrementNonRecyclablesCount(nonRecyclablesCount);
            userDatabase[userID] = userData;
        }
        inputFile.close(); // Close the input file
    }

    while (true)
    {
        // Display the menu to user
        displayMenu();
        // Get the user's menu selection
        string menuSelection;
        cout << "\nEnter a menu option: ";
        cin >> menuSelection;
        cin.ignore(); // Ignore newline character

        if (menuSelection == "1")
        {
            // User registration
            registerUser(userDatabase);
        }
        else if (menuSelection == "2")
        {
            // Call the Waste Tracking function
            handleWasteTracking(userDatabase);
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
        else if (menuSelection == "7" || menuSelection == "help" || menuSelection == "Help" || menuSelection == "?" || menuSelection == "h")
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

    // Save user data to file and exit
    ofstream outputFile(USER_DATA_FILE, ofstream::out | ofstream::trunc);
    if (outputFile.is_open())
    {
        // Write each user data entry to the file
        for (const auto &entry : userDatabase)
        {
            outputFile << entry.first << " \"" << entry.second.getName() << "\" " << entry.second.getRecyclablesCount() << " " << entry.second.getNonRecyclablesCount() << endl;
        }
        outputFile.close();
    }
    else
    {
        cerr << "Error: Unable to open output file." << endl;
    }

    return 0;
};