#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <conio.h>

using namespace std;

const string USER_DATA_FILE = "user_data.txt";
const string PASSWORD_FILE = "private_info.txt";

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
    UserData() : recyclablesCount(0.0), nonRecyclablesCount(0.0) {}

    // Getter for recyclables count
    double getRecyclablesCount() const
    {
        return recyclablesCount;
    }

    // Getter for non-recyclables count
    double getNonRecyclablesCount() const
    {
        return nonRecyclablesCount;
    }

    // Method to increment the recyclables count
    void incrementRecyclablesCount(double count)
    {
        recyclablesCount += count;
    }

    // Method to increment the non-recyclables count
    void incrementNonRecyclablesCount(double count)
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
    double recyclablesCount;    // Store the count of recyclables
    double nonRecyclablesCount; // Store the count of non-recyclables
    string name;                // Store the user name
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

// Function to track user waste data
void trackWaste(map<int, UserData> &userDatabase, int userID)
{
    while (true)
    {
        // Find the user in the database
        auto it = userDatabase.find(userID);

        // Check if the user exists
        if (it != userDatabase.end())
        {
            cout << "Enter type of trash (or 'q' to return to main menu): ";
            string trashType;
            getline(cin, trashType);

            if (trashType == "q" || trashType == "Q")
            {
                break;
            }

            cout << "Enter amount of waste (lbs): ";
            double trashAmount;
            cin >> trashAmount;
            cin.ignore(); // Ignore newline character

            vector<string> recyclableTrashTypes = {
                "jug",
                "jugs",
                "glass",
                "paper",
                "cardboard",
                "cardboards",
                "plastic",
                "yard waste",
                "jar",
                "jars",
                "bottle",
                "bottles",
                "can",
                "cans",
                "newspaper",
                "newspapers"};

            vector<string> nonRecyclableTrashTypes = {
                "food",
                "trash",
                "electronics",
                "batteries",
                "paper towel",
                "paper towels",
                "chemicals",
                "pizza box",
                "paper towls",
                "styrofoam",
                "bubble wrap",
                "aerosol can",
                "aerosol cans",
                "mirror",
                "cloth hanger",
                "cloth hangers",
                "toys"};

            // Check if the entered trash type is in the non-recyclable list
            bool isNonRecyclable = false;
            for (const string &nonRecyclableType : nonRecyclableTrashTypes)
            {
                if (trashType == nonRecyclableType)
                {
                    isNonRecyclable = true;
                    break;
                }
            }

            bool validTrashType = false;

            // Update user's waste data based on recyclability
            if (isNonRecyclable)
            {
                it->second.incrementNonRecyclablesCount(trashAmount);
                validTrashType = true;
            }
            else
            {
                // Check if the entered trash type is in the recyclable list
                bool isRecyclable = false;
                for (const string &recyclableType : recyclableTrashTypes)
                {
                    if (trashType == recyclableType)
                    {
                        isRecyclable = true;
                        break;
                    }
                }

                if (isRecyclable)
                {
                    it->second.incrementRecyclablesCount(trashAmount);
                    validTrashType = true;
                }
                else
                {
                    cerr << "Error: Invalid trash type entered.\n";
                }
            }

            if (validTrashType)
            {
                cout << "Waste tracked successfully for User ID" << userID << ".\n";
            }

            // Save user data to file
            ofstream outputFile(USER_DATA_FILE, ofstream::out | ofstream::trunc);
            if (outputFile.is_open())
            {
                // Write each user data to entry
                for (const auto &entry : userDatabase)
                {
                    outputFile << entry.first << " \"" << entry.second.getName() << "\" " << entry.second.getRecyclablesCount() << " " << entry.second.getNonRecyclablesCount() << endl;
                }
                outputFile.close();
            }
        }
        else
        {
            cerr << "Error: User ID not found.\n";
        }
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

    cout << "\n\t-----     WasteWatch Pro 1.0     -----\n"
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

string getPasswordFromFile(const string &filename)
{
    ifstream passwordFile(filename);
    if (passwordFile)
    {
        string password;
        getline(passwordFile, password);
        return password;
    }
    else
    {
        cerr << "Error: Unable to open password file." << endl;
        exit(1);
    }
}

// Utility function to mask user input for password
string getPasswordInput()
{
    string password = "";
    char ch;

    while (true)
    {
        ch = _getch();
        if (ch == '\r' || ch == '\n')
        {
            break;
        }
        else if (ch == '\b' && password.length() > 0)
        {                    // Backspace key
            cout << "\b \b"; // Remove characters from console
            password.pop_back();
        }
        else
        {
            cout << '*';
            password += ch;
        }
    }
    cout << endl;
    return password;
}

bool authenticateUser(const string &actualPassowrd)
{
    const int MAX_ATTEMPTS = 3;

    for (int i = 0; i < MAX_ATTEMPTS; i++)
    {
        cout << "Enter password (" << MAX_ATTEMPTS - i << " attempts remaining): ";
        string inputPassword = getPasswordInput();

        if (inputPassword == actualPassowrd)
            return true; // authenticated
    }

    return false; // authentication failed after 3 attempts
}

// Function to print out report of all users
void generatedWasteReport(const map<int, UserData> &userDatabase)
{
    double totalRecyclables = 0.0, totalNonRecyclables = 0.0;

    for (const auto &entry : userDatabase)
    {
        totalRecyclables += entry.second.getRecyclablesCount();
        totalNonRecyclables += entry.second.getNonRecyclablesCount();
    }

    double totalWaste = totalRecyclables + totalNonRecyclables;
    double recyclablePercentage = (totalRecyclables / totalWaste) * 100;

    cout << "\n------- Waste Report -------" << endl;
    cout << "Total Recyclable Waste: " << totalRecyclables << " lbs" << endl;
    cout << "Total Non-Recyclable Waste: " << totalNonRecyclables << " lbs" << endl;
    cout << "Total Waste Generated: " << totalWaste << " lbs" << endl;
    cout << "Percentage of Recyclables: " << recyclablePercentage << "%" << endl;
    cout << "----------------------------\n"
         << endl;
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
            int userID;
            cout << "Enter your User ID: ";
            cin >> userID;
            cin.ignore();

            trackWaste(userDatabase, userID);
        }
        else if (menuSelection == "3")
        {
            cout << "1. Report for a specific user" << endl;
            cout << "2. Report for all users" << endl;
            cout << "Enter your choice (1 or 2): ";
            string reportChoice;
            cin >> reportChoice;

            if (reportChoice == "1")
            {
                handleWasteTracking(userDatabase);
            }
            else if (reportChoice == "2")
            {
                string actualPassword = getPasswordFromFile(PASSWORD_FILE);

                if (authenticateUser(actualPassword))
                {
                    generatedWasteReport(userDatabase);
                }
                else
                {
                    cout << "Access denied. Incorrect password." << endl;
                }
            }
            else
            {
                cout << "Invalid choice. Please select 1 or 2." << endl;
            }
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