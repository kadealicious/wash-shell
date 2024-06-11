#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#include"commands.h"
#include"colors.h"

void ExecuteCommand(char *tokens[MAX_ARGS]);
bool ExecuteInternalCommand(char *tokens[MAX_ARGS]);

int main()
{
	printf("%sWelcome to wash!\n%s", KBLU, KNRM);

	// Create a character array to hold our entire command.
	char command[MAX_COMMAND_LENGTH];
	
	while(true)
	{
		// Get user input.
		printf("%swash>%s ", KGRN, KNRM);
		fgets(command, MAX_COMMAND_LENGTH, stdin);

		if(command[0] == '\n')
		{
			continue;
		}

		// Tokenize the input string into the command and its args.
		char *args[MAX_ARGS];
		char *token;
		int arg_count = 0;
		token = strtok(command, " \n");
		while(token != NULL && arg_count < MAX_ARGS - 1)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " \n");
		}
		args[arg_count] = NULL;

		
		/* Check if the requested command is in-built; if it is, we call the 
		 * correct function and return from this function, preventing an 
		 * unnecessary call to fork(). */
		if(!ExecuteInternalCommand(args))
		{
			ExecuteCommand(args);
		}
	}

	return 0;
}

/// Given an input string, execute the correct command.
void ExecuteCommand(char *tokens[MAX_ARGS])
{
	// Fork a child process to execute the command without exiting wash!
	pid_t pid = fork();
	if(pid < 0)
	{
		fprintf(stderr, "%sERROR: Could not create child process!\n%s", KRED, KNRM);
	}
	// If we are in the child process, execute the command!
	else if(pid == 0)
	{
		execvp(tokens[0], tokens);
		fprintf(stderr, "%sERROR: Unknown command!\n%s", KRED, KNRM);
		exit(EXIT_FAILURE);
	}
	// IF we are in the parent process, wait for the child to complete!
	else
	{
		wait(NULL);
	}
}

bool ExecuteInternalCommand(char *tokens[MAX_ARGS])
{
	if(strcmp(tokens[0], "exit") == 0)
	{
		WashExit();
		return true;
	}
	else if(strcmp(tokens[0], "echo") == 0)
	{
		WashEcho(&tokens[1]);
		return true;
	}
	else if(strcmp(tokens[0], "pwd") == 0)
	{
		WashPwd();
		return true;
	}
	else if(strcmp(tokens[0], "cd") == 0)
	{
		WashCd(tokens[1]);
		return true;
	}
	else if(strcmp(tokens[0], "setpath") == 0)
	{
		WashSetPath(tokens[1]);
		return true;
	}
	else if(strcmp(tokens[0], "help") == 0)
	{
		WashHelp();
		return true;
	}

	return false;
}
