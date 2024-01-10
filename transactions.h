//
// Created by Paul on 09.01.2024.
//

#ifndef FINAPPV2_TRANSACTIONS_H
#define FINAPPV2_TRANSACTIONS_H

#include "main.h"

int recordTransaction(Account *account, Transaction transaction);
void createTransaction( User *user);
void writeTransactions(User user);



#endif //FINAPPV2_TRANSACTIONS_H
