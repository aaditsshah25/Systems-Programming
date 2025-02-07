#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

#define WRONG_ARGNUMS     255
#define INVALID_SWITCHES  254 
#define EMPTY_COMMAND     253

void optionArray(char *arr[], char *s)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char temp[100] = "";

    while (s[j] != '\0')
    {
        if (s[j] == ' ')
        {
            temp[k] = '\0';
            arr[i++] = strdup(temp);
            strcpy(temp, "");
            k = 0;
        }
        else
        {
            temp[k++] = s[j];
        }
        j++;
    }
    temp[k] = '\0';
    arr[i] = strdup(temp);
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        return WRONG_ARGNUMS;
    }

    char generator[25] = "";
    char consumer[25] = "";

    for (int i = 1; i < argc; i = i + 2)
    {
        if (strcmp(argv[i], "-g") == 0)
        {
            strcpy(generator, argv[i + 1]);
        }
        else if (strcmp(argv[i], "-c") == 0)
        {
            strcpy(consumer, argv[i + 1]);
        }
        else
        {
            return INVALID_SWITCHES;
        }
    }

    if (strlen(generator) == 0 || strlen(consumer) == 0)
    {
        return EMPTY_COMMAND;
    }

    char *generatorArguments[20];
    char *consumerArguments[20];

    optionArray(generatorArguments, generator);
    optionArray(consumerArguments, consumer);

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        return errno;
    }

    pid_t pid_generator = fork();
    if (pid_generator == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return errno;
    }
    else if (pid_generator == 0)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            return errno;
        }
        close(pipefd[1]);
        execvp(generatorArguments[0], generatorArguments);
        return errno;
    }

    pid_t pid_consumer = fork();
    if (pid_consumer == -1)
    {
        close(pipefd[0]);
        close(pipefd[1]);
        return errno;
    }
    else if (pid_consumer == 0)
    {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
        {
            return errno;
        }
        close(pipefd[0]);
        execvp(consumerArguments[0], consumerArguments);
        return errno;
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status;
    if (waitpid(pid_generator, &status, 0) == -1)
    {
        return errno;
    }
    if (waitpid(pid_consumer, &status, 0) == -1)
    {
        return errno;
    }

    return 0;
}
