#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>

#include "../WasteWatch-Pro/user_data.h"
#include "../WasteWatch-Pro/trackWaste.cpp"
#include "../WasteWatch-Pro/trackWaste.h"
#include "../WasteWatch-Pro/user_data.h"

using namespace std;

/*
    TrackWaste function
*/

class TrackWasteTest : public ::testing::Test
{
protected:
    map<int, UserData> userDatabase;

    void SetUp() override
    {
        UserData user1, user2;
        user1.setName("Mary");
        user1.incrementRecyclablesCount(5.0);
        user1.incrementNonRecyclablesCount(2.0);

        user2.setName("Jack");
        user2.incrementRecyclablesCount(7.0);
        user2.incrementNonRecyclablesCount(3.0);

        userDatabase[1000] = user1;
        userDatabase[1001] = user2;
    }
};

TEST_F(TrackWasteTest, TestWasteTracking)
{
    // Simulate input for the test
    istringstream input("jug\n5.0\nq\n");
    // Redirect cin
    streambuf *originalCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    // Redirect cout
    ostringstream output;
    streambuf *originalCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    trackWaste(userDatabase, 1001);

    // Restore original cin and cout
    cin.rdbuf(originalCin);
    cout.rdbuf(originalCout);

    EXPECT_DOUBLE_EQ(userDatabase[1001].getRecyclablesCount(), 12.0);
    EXPECT_DOUBLE_EQ(userDatabase[1001].getNonRecyclablesCount(), 3.0);

    // Check the output
    string expectedOutput = "Enter type of trash (or 'q' to return to main menu): "
                            "Enter amount of waste (lbs): "
                            "Waste tracked successfully for User ID1001.\n"
                            "Enter type of trash (or 'q' to return to main menu): ";
    EXPECT_EQ(output.str(), expectedOutput);
}

TEST_F(TrackWasteTest, TrackRecyclableWaste)
{
    istringstream input("jug\n5.0\nq\n");
    streambuf *originalCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    ostringstream output;
    streambuf *originalCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    trackWaste(userDatabase, 1001);

    cin.rdbuf(originalCin);
    cout.rdbuf(originalCout);
    ASSERT_EQ(userDatabase[1001].getRecyclablesCount(), 12.0);
    ASSERT_EQ(userDatabase[1001].getNonRecyclablesCount(), 3.0);
}

TEST_F(TrackWasteTest, TrackNonRecyclableWaste)
{
    istringstream input("food\n2.0\nq\n");
    streambuf *originalCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    ostringstream output;
    streambuf *originalCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    trackWaste(userDatabase, 1001);

    cin.rdbuf(originalCin);
    cout.rdbuf(originalCout);
    ASSERT_EQ(userDatabase[1001].getRecyclablesCount(), 7.0);
    ASSERT_EQ(userDatabase[1001].getNonRecyclablesCount(), 5.0);
}

// Test that tracking waste with an invalid trash type fails correctly.
TEST_F(TrackWasteTest, InvalidTrashType)
{
    // Get the type and amount of waste.
    std::string type = "unknown";
    double amount = 10.0;

    std::stringstream input("unknown\n10.0\nq\n");

    // Redirect cin
    streambuf *originalCin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    // Redirect cout
    std::stringstream output;
    streambuf *originalCout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Redirect cerr
    streambuf *originalCerr = std::cerr.rdbuf();
    std::cerr.rdbuf(output.rdbuf());

    // Call function
    trackWaste(userDatabase, 1001);

    // Restore original cin, cout, and cerr
    std::cin.rdbuf(originalCin);
    std::cout.rdbuf(originalCout);
    std::cerr.rdbuf(originalCerr);

    // Verify that the user's waste data was not updated.
    ASSERT_EQ(userDatabase[1001].getRecyclablesCount(), 7.0);
    ASSERT_EQ(userDatabase[1001].getNonRecyclablesCount(), 3.0);

    // Verify that the output contains an error message.
    std::string outputStr = output.str();
    ASSERT_NE(outputStr.find("Error: Invalid trash type entered."), std::string::npos);
}

TEST_F(TrackWasteTest, ExitCommand)
{
    istringstream input("q\n");
    streambuf *originalCin = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    ostringstream output;
    streambuf *originalCout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    trackWaste(userDatabase, 1001);

    cin.rdbuf(originalCin);
    cout.rdbuf(originalCout);
    ASSERT_EQ(userDatabase[1001].getRecyclablesCount(), 7.0);
    ASSERT_EQ(userDatabase[1001].getNonRecyclablesCount(), 3.0);
}
