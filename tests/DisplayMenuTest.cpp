#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "../WasteWatch-Pro/displayMenu.cpp"

using namespace std;

// Redirect cout to a stringstream to capture the output
class CaptureStdout {
public:
    CaptureStdout() : oldCoutBuf(cout.rdbuf()), strCout() {
        cout.rdbuf(strCout.rdbuf());
    }

    ~CaptureStdout() {
        cout.rdbuf(oldCoutBuf);
    }

    string getCapturedOutput() {
        return strCout.str();
    }

private:
    stringstream strCout;
    streambuf* oldCoutBuf;
};

// Test fixture to capture cout output
class DisplayMenuTest : public ::testing::Test {
protected:
    CaptureStdout capture;
};

TEST_F(DisplayMenuTest, DisplayMenuOutput) {
    displayMenu(); // Call the function

    // Capture the output from displayMenu
    string output = capture.getCapturedOutput();

    // Define the expected menu output
    string expectedOutput = "\n\t-----     WastWath Pro 1.0     -----\n\n";
    expectedOutput += "1. Option 1\n";
    expectedOutput += "2. Option 2\n";
    expectedOutput += "3. Option 3\n";
    expectedOutput += "4. Help\n";
    expectedOutput += "5. Exit\n";

    // Compare the actual output with the expected output
    ASSERT_EQ(output, expectedOutput);
}