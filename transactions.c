#include "transactions.h"
/**
 * @brief Records a transaction for the specified account.
 * @param account The account for which the transaction is recorded.
 * @param transaction The transaction details to be recorded.
 * @return 0 if the transaction is recorded successfully, -1 if an invalid transaction type is provided.
 */

int isValidDate(const char *dateStr) {
    int day, month, year;

    // Attempt to parse the date using sscanf
    if (sscanf(dateStr, "%d-%d-%d", &day, &month, &year) != 3) {
        return 0;  // Failed to parse all three components
    }

    // Check if the components are within valid ranges
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0;  // Invalid range
    }

    // Check for specific month-day combinations
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return 0;  // Invalid day for 30-day months
    } else if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) {
                return 0;  // Invalid day for February in a leap year
            }
        } else {
            if (day > 28) {
                return 0;  // Invalid day for February in a non-leap year
            }
        }
    }

    // If all checks pass, the date is considered valid
    return 1;
}

int recordTransaction(Account *account, Transaction transaction) {
    // Check transaction type and update account balance accordingly
    if (strcmp(transaction.type, "deposit") == 0 || strcmp(transaction.type, "transfer") == 0) {
        account->balance += transaction.amount;
    } else if (strcmp(transaction.type, "withdrawal") == 0 || strcmp(transaction.type, "payment") == 0) {
        // Ensure sufficient balance before processing withdrawal or payment
        if (account->balance >= transaction.amount) {
            account->balance -= transaction.amount;
        }
    } else {
        // Invalid transaction type
        return -1;
    }

    // Print success message and record transaction details if transactionCount is within limits
    printf("Transaction recorded successfully.\n");
    if (account->transactionCount < 30) {
        account->transactionList[(account->transactionCount)] = transaction;
        account->transactionCount++;
    }

    return 0;
}

/**
 * @brief Creates a new transaction for a user's account.
 * @param user The user for whom the transaction is created.
 */
void createTransaction(User *user) {
    Transaction transaction;
    if (user->numberOfAccounts > 0) {
        printf("Enter account name for the transaction: \n");
        char accountName[50];
        scanf("%s", accountName);

        int found = 0;
        // Find the account to which the transaction belongs
        for (int i = 0; i < user->numberOfAccounts; i++) {
            if (strcmp(user->accountList[i].name, accountName) == 0) {
                // Collect transaction details
                printf("Enter transaction type (deposit/withdrawal/transfer/payment): \n");
                scanf("%s", transaction.type);

                // Use strtod for better error handling
                printf("Enter transaction amount: $\n");
                char amountStr[50];
                scanf("%s", amountStr);
                transaction.amount = strtod(amountStr, NULL);
                if(transaction.amount <=0)
                {
                    printf("Transaction value must be greater than 0\n");
                    return;
                }

                printf("Enter transaction description: \n");
                scanf("%s", transaction.description);

                printf("Enter a date: \n");
                scanf("%s", transaction.date);
                if(!isValidDate(transaction.date))
                {
                    printf("Invalid date, try again!\n");
                    return;
                }

                // Set the parent account for the transaction
                strcpy(transaction.parentAccount, accountName);

                // Record the transaction and write transactions to file
                if (recordTransaction(&user->accountList[i], transaction) == 0)
                    writeTransactions(*user);

                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Account not found.\n");
        }
    } else {
        printf("No accounts available.\n");
    }
}

/**
 * @brief Writes user transactions to a file named "transactions.txt".
 * @param user The user whose transactions need to be written to the file.
 */
void writeTransactions(User user) {
    FILE *file = fopen("transactions.txt", "w");

    if (file != NULL) {
        // Loop through user accounts and their transactions, writing details to the file
        for (int i = 0; i < user.numberOfAccounts; i++) {
            for (int j = 0; j < user.accountList[i].transactionCount; j++) {
                fprintf(file, "%s,%s,%.2lf,%s,%s\n", user.accountList[i].transactionList[j].parentAccount,
                        user.accountList[i].transactionList[j].type, user.accountList[i].transactionList[j].amount,
                        user.accountList[i].transactionList[j].description, user.accountList[i].transactionList[j].date);
            }
        }

        fclose(file);
    } else {
        printf("Error opening file for writing\n");
    }
}
