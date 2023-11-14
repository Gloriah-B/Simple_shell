#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt(void);
void execute_command(char *command);

/**
 * main - Entry point of the shell.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(void)
{
	while (1)
	{
		char command[MAX_COMMAND_LENGTH];
		size_t length;

		display_prompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			write(STDOUT_FILENO, "\nExiting Gloriah_shell. Goodbye!\n", 31);
			break;
		}
		length = strlen(command);

		if (length > 0 && command[length - 1] == '\n')
		{
			command[length - 1] = '\0';
		}
		execute_command(command);
	}
	return (EXIT_SUCCESS);
}

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "Gloriah_shell$ ", 15);
	fflush(stdout);
}
/**
 * execute_command - Execute the specified command
 * @command: The command to be executed
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char *token;
		char *args[MAX_COMMAND_LENGTH];
		int i;
		char *path_copy;
		char *dir;
		char *path;

		token = strtok(command, " ");
		i = 0;

	while (token != NULL && i < MAX_COMMAND_LENGTH - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

		args[i] = NULL;
		path = getenv("PATH");

		if (path == NULL)
		{
			write
	(STDERR_FILENO, "PATH environment variable not set,\n", 36);

			exit(EXIT_FAILURE);
		}

		path_copy = strdup(path);
		dir = strtok(path_copy, " : ");

		while (dir != NULL)
		{
			char executable_path[MAX_COMMAND_LENGTH];

			snprintf(executable_path, sizeof(executable_path),
					"%s/%s", dir, args[0]);
			if (access(executable_path, X_OK) == 0)
			{
			execve(executable_path, args, NULL);
			}

			dir = strtok(NULL, " : ");
		}
		free(path_copy);

		write(STDERR_FILENO, "Command not found : ", 20);
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
}
else
{
	int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}


		if (WIFEXITED(status))
		{
			/* int exit_code = WEXITSTATUS(status);  // Not used in this version */
		}

}
