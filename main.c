#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXUSERS 20
#define MAXACCOUTNS 10

// Structure to represent a financial account
typedef struct {
    char type[50];
    char name[50];
    char owner[50];

    double balance;
} Account;

typedef struct {

    char username[50];
    char password[50];

}User;

// Structure to represent a financial transaction
typedef struct {
    char type[20];  // deposit, withdrawal, transfer, payment, etc.
    char date[20];
    char parentAccount[20];
    char description[100];
    double amount;
} Transaction;


Account createAccount(User user) {
    // Returns a new account(Account)
    Account newAccount;

    printf("Enter account name: \n");
    scanf("%s", newAccount.name);

    printf("Enter account type: \n");
    scanf("%s", newAccount.type);

    strcpy(newAccount.owner,user.username);
    newAccount.balance = 0.0;

    return newAccount;
}

void updateAccount(char *accountName, Account accounts[], int numAccounts ){


    for(int i = 0; i < numAccounts; i++)
        if(strcmp(accounts[i].name, accountName) == 0 )
        {

            printf("Enter new account name: \n");
            scanf("%s", accounts[i].name);

            printf("Enter new account type: \n");
            scanf("%s", accounts[i].type);

            printf("Enter new account balance: \n");
            scanf("%lf", &accounts[i].balance);

            printf("Account updated successfully! \n");
            return;

        }
    printf("Account doesn't exist!\n");

}

void deleteAccount(char *accountName, Account accounts[], int *numAccounts )
{
    for(int i = 0; i < *numAccounts; i++)
        if(strcmp(accounts[i].name, accountName) == 0 )
        {

            accounts[i] = accounts[*numAccounts-1];
            printf("Account deleted\n");
            *numAccounts =*numAccounts-1;
            return;
        }
    printf("Error deleting account\n");

}

// Function to record a transaction for an account
void recordTransaction(Account *account, Transaction transaction) {
    if (strcmp(transaction.type, "deposit") == 0 || strcmp(transaction.type, "transfer") == 0) {
        account->balance += transaction.amount;
    } else if (strcmp(transaction.type, "withdrawal") == 0 || strcmp(transaction.type, "payment") == 0) {
    }
    if (account->balance >= transaction.amount) {
        account->balance -= transaction.amount;
    } else {
        printf("Insufficient funds for withdrawal/payment.\n");
    }
}

void createTransaction(int *numAccounts, Account accounts[], User user){
    Transaction transaction;
    if (*numAccounts > 0) {
        printf("Enter account name for the transaction: ");
        char accountName[50];
        scanf("%s", accountName);

        int found = 0;
        for (int i = 0; i < *numAccounts; i++) {
            if (strcmp(accounts[i].name, accountName) == 0 && strcmp(accounts[i].owner, user.username) == 0) {

                printf("Enter transaction type (deposit/withdrawal/transfer/payment): ");
                scanf("%s", transaction.type);
                printf("Enter transaction amount: $");
                scanf("%lf", &transaction.amount);
                printf("Enter transaction description ");
                scanf("%s", transaction.description);
                strcpy(transaction.parentAccount, accountName);
                printf("Enter a date ");
                scanf("%s", transaction.date);

                recordTransaction(&accounts[i], transaction);
                printf("Transaction recorded successfully.\n");
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


// Function to generate a financial report for an account
void generateReport(Account account) {
    printf("\nAccount owner: %s\n", account.owner);
    printf("Current Balance: $%.2f\n\n", account.balance);
}

void accountsMenu()
{
    printf("1. Create new Account.\n");
    printf("2. Update Account.\n");
    printf("3. Delete Account.\n");
    printf("4. Return\n");
    printf("Enter your choice: \n");
}

void userMenu()
{

    printf("1. Manage Accounts\n");
    printf("2. Record Transaction\n");
    printf("3. Generate Report\n");
    printf("4. Logout\n");
    printf("Enter your choice: \n");
}

void mainMenu()
{
    printf("\n===== Accounting System =====\n");
    printf("1. Sign Up\n");
    printf("2. Sign In\n");
    printf("3. Exit\n");
    printf("Enter your choice: \n");
}

void reportsMenu(){
    printf("===== Financial Reporting =====\n");
    printf("1. Account Statements\n");
    printf("2. Balances\n");
    printf("3. Transaction Registers\n");
    printf("4. Expense Reports\n");
    printf("5. Return\n");
    printf("Enter your choice: \n");
}

int printAccounts(int numAccounts, Account accounts[], User owner){
    int count=0;
    for (int i = 0; i<numAccounts; i++)
        if(strcmp(accounts[i].owner,owner.username)==0)
        {
            count++;
            printf("[%d] %s || %s || %s || %.2lf\n", i ,accounts[i].name, accounts[i].type, accounts[i].owner, accounts[i].balance);
        }
    printf("User has: %d accounts\n", count);
    return count;
}

int signUp(User user, int count, User users[])
{
    for (int i = 0 ; i < count; i++)
        if(strcmp(user.username, users[i].username) == 0 )
            return -1;

    if (count<MAXUSERS){
        users[count++] = user;
        return 0;
    }

    else
        printf("User limit reached\n");
    return -1;
}

int signIn(User user, User users[], int count)
{
    for (int i = 0 ; i < count; i++)
        if(strcmp(user.username, users[i].username) == 0)
            if (strcmp(users[i].password, user.password) == 0)
                return 0;
    return -1;
}

void financialReporting(int numAccounts, Account accounts[], User user) {
    int choice;
    reportsMenu();
    scanf("%d", &choice);

    switch (choice) {
        case 1:

            printf("Enter account name for the statement: ");
            char accountName[50];
            scanf("%s", accountName);

            int found = 0;
            for (int i = 0; i < numAccounts; i++) {
                if (strcmp(accounts[i].owner, user.username) == 0 && strcmp(accounts[i].name, accountName) == 0) {
                    generateReport(accounts[i]);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Account not found.\n");
            }
            break;

        case 2:
            // Implement code for generating balances report
            // This could include the current balance for each account
            printAccounts(numAccounts, accounts, user);
            break;

        case 3:
            // Implement code for generating transaction registers
            // This could include a list of transactions for all accounts or a specific account
            printAccounts(numAccounts, accounts, user);
            break;

        case 4:
            // Implement code for generating expense reports
            // This could include expenses based on transaction types (withdrawals, payments)
            printAccounts(numAccounts, accounts, user);
            break;

        case 5:
            return;  // Return to the main menu

        default:
            printf("Invalid choice. Please try again.\n");
    }
}



void manageAccounts(int *numAccounts, Account accounts[], User user)
{
    while(1)
    {
        accountsMenu();
        int choice;

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (*numAccounts < 10) {
                    accounts[*numAccounts] = createAccount(user);
                    *numAccounts = *numAccounts+1;
                    printf("Account created successfully.\n");
                } else {
                    printf("Maximum number of accounts reached.\n");
                }
                break;
            case 2:

                if (*numAccounts > 0 )
                {
                    if(printAccounts(*numAccounts, accounts, user))
                    {
                    printf("Enter the name of the account you want to update: \n");
                    char subchoice[50];
                    scanf("%s", subchoice);
                    updateAccount(subchoice, accounts, *numAccounts);
                    } else
                        printf("No accounts available\n");

                }
                break;

            case 3:
                if (*numAccounts > 0 ) {
                    if(printAccounts(*numAccounts, accounts, user))
                    {
                        printf("Enter the name of the account you want to delete: \n");
                        char subchoice[50];
                        scanf("%s", subchoice);
                        deleteAccount(subchoice, accounts, numAccounts);
                    } else
                        printf("No accounts available\n");

                }
                break;
            case 4:
                return;

        }


    }


}


void bank(User user)
{

    Account accounts[MAXACCOUTNS];  // Array to store up to 10 accounts

    int numAccounts = 0;

    while (1) {


        userMenu();
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                manageAccounts(&numAccounts, accounts, user);
                
            case 2:
                createTransaction(&numAccounts, accounts, user);
                break;

            case 3:
                financialReporting(numAccounts, accounts, user);
            case 4:
                return;


            default:
                printf("Invalid choice. Please try again.\n");
        }
}
}




int main() {

    int userCount = 0;
    User users[20];

    while (1)
    {
        mainMenu();
        int choice;
        scanf("%d", &choice);
        switch (choice) {

            User newUser;
            int response;

            case 1:


                printf("Enter a unique username: \n");
                scanf("%s", newUser.username);

                printf("Enter a password: \n");
                scanf("%s", newUser.password);


                response = signUp(newUser, userCount, users);
                if (response == 0) {
                    printf("User: %s added successfully!\n", newUser.username);
                    userCount += 1;
                }
                else
                    printf("User already exists.\n");
                break;
            case 2:
                printf("Enter a username: \n");

                scanf("%s", newUser.username);

                printf("Enter a password: \n");

                scanf("%s", newUser.password);


                response = signIn(newUser, users, userCount);
                if (response == 0)
                    bank(newUser);
                else
                    printf("Incorrect password. Try again!\n");
                break;


            case 3:
                exit(0);
        }
    }
}
