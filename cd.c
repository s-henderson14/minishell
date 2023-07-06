#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *old_pwd = NULL;
    char *new_pwd = NULL;

    // Store the current working directory in OLD_PWD
    old_pwd = getenv("PWD");
    if (old_pwd == NULL) {
        perror("Failed to get current working directory");
        exit(EXIT_FAILURE);
    }

    // Change the current working directory to the new path
    if (chdir(argv[1]) != 0) {
        perror("Failed to change directory");
        exit(EXIT_FAILURE);
    }

    // Store the new working directory in PWD
    new_pwd = getcwd(NULL, 0);
    if (new_pwd == NULL) {
        perror("Failed to get current working directory");
        exit(EXIT_FAILURE);
    }

    // Update the environment variables
    if (setenv("OLD_PWD", old_pwd, 1) != 0) {
        perror("Failed to set OLD_PWD");
        exit(EXIT_FAILURE);
    }

    if (setenv("PWD", new_pwd, 1) != 0) {
        perror("Failed to set PWD");
        exit(EXIT_FAILURE);
    }

    // Print the updated values of OLD_PWD and PWD
    printf("OLD_PWD: %s\n", getenv("OLD_PWD"));
    printf("PWD: %s\n", getenv("PWD"));

    // Free memory
    free(new_pwd);

    return 0;
}

