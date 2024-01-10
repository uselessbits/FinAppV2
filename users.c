#include "users.h"
void userMenu()
{
/**
 * @brief Displays the user menu options for managing accounts, recording transactions, generating reports, and logging out.
 */
    printf("1. Manage Accounts\n");
    printf("2. Record Transaction\n");
    printf("3. Generate Report\n");
    printf("4. Logout\n");
    printf("Enter your choice: \n");
}


int signUp(User user)
{
/**
 * @brief Signs up a new user by appending their username and password to the USERSFILE.
 * @param user The user to sign up.
 * @return 0 on successful sign-up, -1 on error opening or writing to the file.
 */

        FILE *file = fopen(USERSFILE, "w");
        if (file == NULL) {
            printf("Error opening file for appending\n");
            return -1;
        }
        fprintf(file, "%s,%s\n", user.username, user.password);

        fclose(file);

        return 0;

}



int signIn(User user)
{

    /**
 * @brief Signs in a user by comparing the provided username and password with those in the USERSFILE.
 * @param user The user to sign in.
 * @return 0 on successful sign-in, -1 on error opening or reading from the file, -1 if sign-in fails.
 */

    char username[30];
    char password[30];
    FILE *file = fopen(USERSFILE, "r");
    if (file != NULL) {
        // Read the username and password from the file
        fscanf(file, "%[^,],%[^\n]%*c", username,password);

        fclose(file);
    } else {
        printf("Error opening file for reading\n");
        return -1;
    }

    // Compare the provided username and password with those in the file
    if (strcmp(user.username, username) == 0 && strcmp(password, user.password) == 0) {
        return 0;  // Sign-in successful
    }

    return -1;  // Sign-in failed
}