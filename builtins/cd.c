#include <stdlib.h>
#include <stdio.h>

//STEP 1 - Store the current working directory in OLD_PWD i.e PWD = OLD_PWD
//STEP 2 - Change the current working directory to the new path.
//STEP 3 - Store the new working directory in PWD
//STEP 4 - Update the environment variables

int	cd(char *path)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = NULL;
	new_pwd = NULL;
	old_pwd = getenv("PWD");
	
	if (old_pwd == NULL) 
		perror("Failed to get current working directory");
	if (chdir(path) != 0) 
		perror("Failed to change directory");
	
	new_pwd = getcwd(NULL, 0);
	
	if (new_pwd == NULL) 
		perror("Failed to get current working directory");
	if (setenv("OLD_PWD", old_pwd, 1) != 0) 
		perror("Failed to set OLD_PWD");
	if (setenv("PWD", new_pwd, 1) != 0) 
		perror("Failed to set PWD");
	
	free(new_pwd);
	return (0);
}
