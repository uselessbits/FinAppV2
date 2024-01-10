
//Defined modules
#include "main.h"
#include "users.h"
#include "accounts.h"
#include "transactions.h"





void mainMenu()
{
    printf("\n===== Accounting System =====\n");
    printf("1. Sign In\n");
    printf("2. Change credentials\n");
    printf("3. Exit\n");
    printf("Enter your choice: \n");
}

void reportsMenu(){
    /**
 * @brief Displays the financial reporting menu options.
 */
    printf("===== Financial Reporting =====\n");
    printf("1. Account Statements\n");
    printf("2. Transaction Registers\n");
    printf("3. Expense Reports\n");
    printf("4. Return\n");
    printf("Enter your choice: \n");
}


void printTransactionsToFile(User user) {

    /**
 * @brief Prints transactions of a user to a file named "transaction_register.txt".
 * @param user The user whose transactions need to be printed.
 */
    char accountName[30];
    printf("Enter account name for report");
    scanf("%s", accountName);

    FILE *file = fopen("transaction_register.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    int i, j;
    for (i = 0; i < user.numberOfAccounts; i++) {
        if (strcmp(user.accountList[i].name, accountName) == 0) {
            fprintf(file, "Transactions for Account: %s\n", accountName);
            fprintf(file, "--------------------------------\n");

            for (j = 0; j < user.accountList[i].transactionCount; j++) {
                Transaction transaction = user.accountList[i].transactionList[j];
                fprintf(file, "Type: %s\n", transaction.type);
                fprintf(file, "Date: %s\n", transaction.date);
                fprintf(file, "Parent Account: %s\n", transaction.parentAccount);
                fprintf(file, "Description: %s\n", transaction.description);
                fprintf(file, "Amount: %.2f\n", transaction.amount);
                fprintf(file, "--------------------------------\n");
            }

            fclose(file);
            return;
        }
    }

    fprintf(stderr, "Account not found: %s\n", accountName);
    fclose(file);
}

void printAccountStatements(User user){
    /**
 * @brief Prints account statements to a file named "statements.txt".
 * @param user The user whose account statements need to be printed.
 */

    FILE *file = fopen("statements.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return;
    }

    fprintf(file,"User has:%d\n", user.numberOfAccounts);
    for(int i= 0 ; i< user.numberOfAccounts;i++)
        fprintf(file, "Account: %s, Account type:%s, Account balance:%.2lf\n", user.accountList[i].name,
               user.accountList[i].type, user.accountList[i].balance);
}

void financialReporting(User user) {
/**
 * @brief Handles the financial reporting options based on user input.
 * @param user The user for whom financial reporting is conducted.
 */
    int choice;
    char choiceStr[50];
    reportsMenu();
    scanf("%s", choiceStr);

// Convert the string to an integer using strtol
    char *endptr;
    choice = strtol(choiceStr, &endptr, 10);

// Check for conversion errors
    if (*endptr != '\0') {
        printf("Invalid input. Please enter a valid integer.\n");

    }


    switch (choice) {
        case 1:

            printAccountStatements(user);
            break;
        case 2:
            printTransactionsToFile(user);
            break;

//        case 3:
//            // Implement code for generating transaction registers
//            // This could include a list of transactions for all accounts or a specific account
//            printAccounts(numAccounts, user);
//            break;
//
//

        case 4:
            return;  // Return to the main menu

        default:
            printf("Invalid choice. Please try again.\n");
    }
}





void bank(User user)
{

/**
 * @brief Manages user interactions within the banking system, including account management and transactions.
 * @param user The user for whom banking operations are performed.
 */

    while (1) {

        loadAccounts(&user);
        userMenu();
        int choice;
        char choiceStr[50];

        scanf("%s", choiceStr);


        char *endptr;
        choice = strtol(choiceStr, &endptr, 10);


        if (*endptr != '\0') {
            printf("Invalid input. Please enter a valid integer.\n");

        }

        switch (choice) {
            case 1:
                manageAccounts(user);
                break;

            case 2:
                createTransaction(&user);
                saveAccountsToFile(user);
                break;

            case 3:
                if(user.numberOfAccounts > 0)
                    financialReporting(user);
                else
                    printf("User has no accounts");
                break;
            case 4:
                return;


            default:
                printf("Invalid choice. Please try again.\n");
        }


}
}




int main() {


/**
 * @brief The main function responsible for handling user sign-in, sign-up, and system exit.
 */
    User newUser;
    int response;

    while (1)
    {
        mainMenu();
        int choice;
        char choiceStr[50];

        scanf("%s", choiceStr);


        char *endptr;
        choice = strtol(choiceStr, &endptr, 10);


        if (*endptr != '\0') {
            printf("Invalid input. Please enter a valid integer.\n");

        }

        switch (choice) {



            case 1:
                printf("Enter username: \n");

                scanf("%s", newUser.username);

                printf("Enter password: \n");

                scanf("%s", newUser.password);

                newUser.numberOfAccounts = 0;

                response = signIn(newUser);
                if (response == 0)
                    bank(newUser);
                else
                    printf("Incorrect password. Try again!\n");
                break;



            case 2:
                printf("Enter a new username: \n");
                scanf("%s", newUser.username);

                printf("Enter a new password: \n");
                scanf("%s", newUser.password);


                response = signUp(newUser);
                if (response == 0) {
                    printf("Username and password changed successfully!\n");

                }
                else
                    printf("User already exists or User limit reached.\n");
                break;

            case 3:
                exit(0);

            default:
                break;
        }
    }
}
