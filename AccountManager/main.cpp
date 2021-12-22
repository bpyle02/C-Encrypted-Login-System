/*
    Brandon Pyle
    Account Manager

    This program allows the user to create and sign into accounts. When an account is created,
    the login details are encrypted and saved to a txt file. When a user logs in using those
    credentials, the program will search through the txt file to find and decrypt the appropriate
    login information.

    wait() function provided by Professor Terri Sipantzi
*/

#include <iostream>
#include "AccountManager.h"

using namespace std;

//Function Prototypes
void wait();

int main()
{
    //Variable Declarations
    AccountManager app;
    string loginOrSignUp;
    bool validInput = false;

    //Program Logic
    cout << "Welcome to Brandon Pyle's Account Manager" << endl << endl;
    cout << "Do you already have an account? y/n: ";

    while (!validInput)
    {
        getline(cin, loginOrSignUp);
        cout << endl;

        if (loginOrSignUp == "Y" || loginOrSignUp == "y")
        {
            validInput = true;
            app.login();
        }
        else if (loginOrSignUp == "N" || loginOrSignUp == "n")
        {
            validInput = true;
            app.signUp();
        }
        else
            cout << "Invalid input, please enter y or n: ";
    }

    system("pause");
}

void wait()
{
    //The following if-statement checks to see how many characters are in cin's buffer
    //If the buffer has characters in it, the clear and ignore methods get rid of them.
    if (cin.rdbuf()->in_avail() > 0) //If the buffer is empty skip clear and ignore
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clear the input buffer 
    }
    char ch;
    cout << "Press the Enter key to continue ... ";
    cin.get(ch);
}