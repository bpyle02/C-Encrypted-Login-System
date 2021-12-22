#pragma once

#include <string>

class AccountManager
{
    std::string userNameAttempt;
    std::string passwordAttempt;
    std::string tryAgain;

public:
    AccountManager();

    void login();

    void signUp();

    void addUser(const std::string p_username, const std::string p_password);

    int getLastID();

    int checkFile(std::string attempt, const char* p_fileName);

    void saveFile(std::string p_line, const char* p_fileName, int& p_id);

    long long encrypt(long long p_letter);

    int decrypt(long long p_letter);
};