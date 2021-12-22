#include "AccountManager.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>

AccountManager::AccountManager() {}

void AccountManager::login()
{
    std::cout << std::endl << "***** LOGIN *****" << std::endl;
    std::cout << "Username: ";
    std::cin >> userNameAttempt;

    int userID = checkFile(userNameAttempt, "users.txt");

    if (userID != 0)
    {
        std::cout << "Password: ";
        std::cin >> passwordAttempt;

        int passwordID = checkFile(passwordAttempt, "passwords.txt");
        if (userID == passwordID)
        {
            std::cout << "Login successful" << std::endl << std::endl;
        }
        else
        {
            std::cout << "Incorrect password" << std::endl << std::endl;
            std::cout << "Would you like to try again? y/n: ";
            std::cin >> tryAgain;

            if (tryAgain == "y" || tryAgain == "Y")
            {
                login();
            }
            else
            {
                std::cout << "Exiting program..." << std::endl;
            }
        }
    }
    else
    {
        std::cout << "Incorrect username" << std::endl << std::endl;
        std::cout << "Would you like to try again? y/n: ";
        std::cin >> tryAgain;

        if (tryAgain == "y" || tryAgain == "Y")
        {
            login();
        }
        else
        {
            std::cout << "Exiting program..." << std::endl;
        }
    }
}

void AccountManager::signUp()
{
    std::string username;
    std::string password;

    std::cout << "***** SIGN UP *****" << std::endl;
    std::cout << "Username: ";
    std::cin >> username;

    std::cout << "Password: ";
    std::cin >> password;

    addUser(username, password);

    login();
}

void AccountManager::addUser(const std::string p_username, const std::string p_password)
{
    if (checkFile(p_username, "users.txt") != 0)
    {
        std::cout << "Username is already taken. Please try again." << std::endl << std::endl;
        signUp();
    }

    int id = 1 + getLastID();
    saveFile(p_username, "users.txt", id);
    saveFile(p_password, "passwords.txt", id);

}

int AccountManager::getLastID()
{
    std::fstream file;
    file.open("users.txt", std::ios::in);
    file.seekg(0, std::ios::end);

    if (file.tellg() == -1)
        return 0;

    std::string s;

    for (int i = -1; s.find("#") == std::string::npos; i--)
    {
        file.seekg(i, std::ios::end);
        file >> s;
    }

    file.close();

    s.erase(0, 4);

    int id;
    std::istringstream(s) >> id;

    return id;
}

int AccountManager::checkFile(std::string attempt, const char* p_fileName)
{
    std::string line;
    std::fstream file;

    std::string currentChar;
    long long encChar;

    file.open(p_fileName, std::ios::in);

    while (1)
    {
        file >> currentChar;

        if (currentChar.find("#ID:") != std::string::npos)
        {
            if (attempt == line)
            {
                file.close();
                currentChar.erase(0, 4);
                int id;
                std::istringstream(currentChar) >> id;
                return id;
            }
            else
            {
                line.erase(line.begin(), line.end());
            }

        }
        else
        {
            std::istringstream(currentChar) >> encChar;
            line += (char)decrypt(encChar);
            currentChar = "";
        }

        if (file.peek() == EOF)
        {
            file.close();
            return 0;
        }

    }
}

void AccountManager::saveFile(std::string p_line, const char* p_fileName, int& p_id)
{
    std::fstream file;
    file.open(p_fileName, std::ios::app);
    file.seekg(0, std::ios::end);

    if (file.tellg() != 0)
        file << "\n";

    file.seekg(0, std::ios::beg);

    for (int i = 0; i < p_line.length(); i++)
    {
        file << encrypt(p_line[i]);
        file << "\n";
    }

    file << "#ID:" << p_id;
    file.close();
}

long long AccountManager::encrypt(long long p_letter)
{
    return powf(p_letter, 5) * 4;
}

int AccountManager::decrypt(long long p_letter)
{
    return powf(p_letter / 4, 1 / 5.f);
}