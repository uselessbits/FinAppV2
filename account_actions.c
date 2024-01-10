
#include "accounts.h"

void manageAccounts( User user)
{
 /**
 * @brief Manages user accounts by providing options to create, update, and delete accounts.
 * @param user The user for whom the accounts are managed.
 */

    while(1)
    {
        //prints the accounts menu
        accountsMenu();

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
                if (user.numberOfAccounts < 10) {
                    createAccount(&user);
                    printf("Account created successfully.\n");
                    saveAccountsToFile(user);
                } else {
                    printf("Maximum number of accounts reached.\n");
                }
                break;
            case 2:

                if (user.numberOfAccounts > 0 )
                {
                    if(printAccounts(user))
                    {
                        printf("Enter the name of the account you want to update: \n");
                        char subchoice[50];
                        scanf("%s", subchoice);
                        updateAccount(subchoice, &user);
                        saveAccountsToFile(user);
                    } else
                        printf("No accounts available\n");

                }
                break;

            case 3:
                if (user.numberOfAccounts > 0 ) {
                    if(printAccounts( user))
                    {
                        printf("Enter the name of the account you want to delete: \n");
                        char subchoice[50];
                        scanf("%s", subchoice);
                        deleteAccount(subchoice, &user);
                        saveAccountsToFile(user);
                    } else
                        printf("No accounts available\n");

                }
                break;
            case 4:
                return;
            default:
                break;
        }


    }


}



void accountsMenu()
{
/**
 * @brief Displays the accounts menu with options for account management.
 */
    printf("\n===== Account Menu =====\n");
    printf("1. Create new Account.\n");
    printf("2. Update Account.\n");
    printf("3. Delete Account.\n");
    printf("4. Return\n");
    printf("Enter your choice: \n");
}

void saveAccountsToFile(User user) {

    /**
 * @brief Saves user accounts to a file named "accounts.txt".
 * @param user The user whose accounts need to be saved.
 */
    FILE *file = fopen("accounts.txt", "w");

    if (file != NULL) {


            for (int j = 0; j < user.numberOfAccounts; j++)
                fprintf(file, "%s,%s,%.2lf\n",
                         user.accountList[j].name, user.accountList[j].type, user.accountList[j].balance);



        fclose(file);
    } else {
        printf("Error opening file for writing\n");
    }
}



void createAccount(User *user) {

/**
 * @brief Creates a new account for the user.
 * @param user The user for whom the account is created.
 */

    printf("Enter account name: \n");
    scanf("%s", user->accountList[user->numberOfAccounts].name);

    printf("Enter account type: \n");
    scanf("%s", user->accountList[user->numberOfAccounts].type);

    strcpy(user->accountList[user->numberOfAccounts].owner,user->username);
    user->accountList[user->numberOfAccounts].balance = 0.0;
    user->numberOfAccounts++;

}


void loadAccounts(User *user)
{
    /**
 * @brief Loads user accounts from the "accounts.txt" file.
 * @param user The user for whom accounts are loaded.
 */
    user->numberOfAccounts=0;
    FILE *file = fopen("accounts.txt", "r");
    if (file!=NULL){


        while(fscanf(file,"%[^,],%[^,],%lf\n",user->accountList[user->numberOfAccounts].name,
                     user->accountList[user->numberOfAccounts].type, &(user->accountList[user->numberOfAccounts].balance))!= EOF)


            user->numberOfAccounts+=1;

        fclose(file);
    } else
        printf("Error opening file!\n");
}

int printAccounts(User user){

/**
 * @brief Prints the user's accounts and returns the number of accounts.
 * @param user The user whose accounts need to be printed.
 * @return The number of accounts.
 */
    for (int i = 0; i<user.numberOfAccounts; i++)
        printf("[%d] %s || %s || %.2lf\n", i ,user.accountList[i].name, user.accountList[i].type,  user.accountList[i].balance);

    printf("User has: %d accounts\n", user.numberOfAccounts);
    return user.numberOfAccounts;
}

void deleteAccount(char *accountName, User *user )
{

    /**
 * @brief Deletes an account with the given name.
 * @param accountName The name of the account to be deleted.
 * @param user The user from whom the account is deleted.
 */
    for(int i = 0; i < user->numberOfAccounts; i++)
        if(strcmp(user->accountList[i].name, accountName) == 0 )
        {

            user->accountList[i] = user->accountList[user->numberOfAccounts-1];
            printf("Account deleted\n");
            user->numberOfAccounts--;
            return;
        }
    printf("Error deleting account\n");

}

void updateAccount(char *accountName, User *user ){

/**
 * @brief Updates an account with the given name.
 * @param accountName The name of the account to be updated.
 * @param user The user for whom the account is updated.
 */
    for(int i = 0; i < user->numberOfAccounts; i++)
        if(strcmp(user->accountList[i].name, accountName) == 0 )
        {

            printf("Enter new account name: \n");
            scanf("%s", user->accountList[i].name);

            printf("Enter new account type: \n");
            scanf("%s", user->accountList[i].type);
            char amountStr[50];
            printf("Enter new account balance: \n");
            scanf("%s", amountStr);
            user->accountList[i].balance = strtod(amountStr, NULL);
            if(user->accountList[i].balance)
            {
                printf("Transaction value must be greater than 0\n");
                return;
            }

            printf("Account updated successfully! \n");
            return;

        }
    printf("Account doesn't exist!\n");

}