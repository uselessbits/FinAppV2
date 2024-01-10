//
// Created by Paul on 09.01.2024.
//

#ifndef FINAPPV2_ACCOUNTS_H
#define FINAPPV2_ACCOUNTS_H

#include "main.h"

void manageAccounts(User user);
void accountsMenu();
void loadAccounts(User *user);
void saveAccountsToFile(User user);
void createAccount(User *user);
void updateAccount(char *accountName, User *user );
void deleteAccount(char *accountName, User *user );
int printAccounts( User owner);
#endif //FINAPPV2_ACCOUNTS_H
