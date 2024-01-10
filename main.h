//
// Created by Paul on 09.01.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FINAPPV2_MAIN_H
#define FINAPPV2_MAIN_H


#define MAXUSERS 20
#define MAXACCOUTNS 10
#define USERSFILE "users.txt"
#define MAXCHARLENGTH 40

typedef struct {
    char type[MAXCHARLENGTH];  // deposit, withdrawal, transfer, payment, etc.
    char date[MAXCHARLENGTH];
    char parentAccount[MAXCHARLENGTH];
    char destinationAccount[MAXCHARLENGTH];
    char description[100];
    double amount;
} Transaction;


// Structure to represent a financial account
typedef struct {
    char type[MAXCHARLENGTH];
    char name[MAXCHARLENGTH];
    char owner[MAXCHARLENGTH];
    Transaction transactionList[30];
    int transactionCount;
    double balance;
} Account;

typedef struct {

    char username[MAXCHARLENGTH];
    char password[MAXCHARLENGTH];
    Account accountList[MAXACCOUTNS];
    int numberOfAccounts;

}User;



#endif //FINAPPV2_MAIN_H
