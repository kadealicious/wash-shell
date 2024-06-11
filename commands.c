#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<linux/limits.h>
#include<unistd.h>

#include"commands.h"
#include"colors.h"

void WashExit()
{
	
	printf("%sGoodbye!\n%s", KBLU, KNRM);
	exit(0);
}

void WashEcho(char *tokens[MAX_ARGS])
{
	for(size_t i = 0; i < MAX_ARGS && tokens[i] != NULL; i++)
	{
		printf("%s ", tokens[i]);
	}
	printf("\n");
}

void WashPwd() {
	char working_dir[PATH_MAX];
	if(getcwd(working_dir, sizeof(working_dir)) != NULL)
	{
		printf("%s\n", working_dir);
		return;
	}
	
	fprintf(stderr, "%sERROR: Failed to get current working directory!\n%s", KRED, KNRM);
}

void WashCd(char* path)
{
	// If no path is provided, go home!  Otherwise, go to the specified path.
	if(path == NULL)
	{
		chdir(getenv("HOME"));
	}
	else if(chdir(path) != 0)
	{
		fprintf(stderr, "%sERROR: Could not change directory!\n%s", KRED, KNRM);
	}
}

void WashSetPath(char *path)
{
	if(setenv("PATH", path, 1) != 0)
	{
		fprintf(stderr, "%sERROR: Could not set path environment variable!\n%s", KRED, KNRM);
	}
}

void WashHelp()
{
	printf("%sHello, and welcome to %swash%s!\n%s", KBLU, KGRN, KBLU, KNRM);
	printf("Enter a command to use the shell: \n");
	printf(" - %sexit%s will close the shell.\n", KYEL, KNRM);
	printf(" - %secho [input]%s will print your [input] to the terminal.\n", KYEL, KNRM);
	printf(" - %spwd%s will print the current working directory.\n", KYEL, KNRM);
	printf(" - %scd [newdir]%s will change directories to [newdir].\n", KYEL, KNRM);
	printf(" - %ssetpath [newpath]%s will overwrite your path environment variable with your [newpath].\n", KYEL, KNRM);
	printf(" - %shelp%s will print this menu to the terminal.\n", KYEL, KNRM);
	printf("%sHave fun!%s\n", KBLU, KNRM);
}
