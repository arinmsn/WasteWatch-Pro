#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "../WasteWatch-Pro/registerUser.cpp"
#include "../WasteWatch-Pro/user_data.h"

using namespace std;

// Test fixture for user registration
class RegisterUserTest : public ::testing::Test {
protected:
    map<int, UserData> userDatabase;
};


// Test case to verify that a user can be successfully registered
TEST_F(RegisterUserTest, UserRegistrationSuccess)
{
    // Set up input for the registration function
    istringstream input("John\nn\n");
    cin.rdbuf(input.rdbuf()); // Redirect cin to read from the stringstream

    registerUser(userDatabase);

    // Verify that the user was registered with the expected name
    ASSERT_EQ(userDatabase.size(), 1); // Check if there is one user in the database
    ASSERT_EQ(userDatabase.begin()->second.getName(), "John");
}

// Test case to verify that registration can be aborted with 'q'
TEST_F(RegisterUserTest, UserRegistrationAbortWithQ)
{
    // Set up input for the registration function
    istringstream input("q\n");
    cin.rdbuf(input.rdbuf()); 

    registerUser(userDatabase);

    // Verify that the user registration was aborted
    // Check if there are no users in the database
    ASSERT_EQ(userDatabase.size(), 0); 
}