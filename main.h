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


typedef struct {
    char type[20];  // deposit, withdrawal, transfer, payment, etc.
    char date[20];
    char parentAccount[20];
    char description[100];
    double amount;
} Transaction;


// Structure to represent a financial account
typedef struct {
    char type[50];
    char name[50];
    char owner[50];
    Transaction transactionList[30];
    int transactionCount;
    double balance;
} Account;

typedef struct {

    char username[50];
    char password[50];
    Account accountList[MAXACCOUTNS];
    int numberOfAccounts;

}User;



#endif //FINAPPV2_MAIN_H
