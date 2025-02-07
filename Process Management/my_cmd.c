#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void optionArray(char *array[], char *s)
{
    int i = 1;
    int j = 0;
    int k = 0;

    char temp[100] = "";

    while (s[j] != '\0')
    {
        if (s[j] == ' ')
        {
            temp[k] = '\0';
            array[i] = strdup(temp);
            i++;
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
    array[i] = temp;
}

int main(int argc, char *argv[])
{
    if (argc < 4 || argc > 6)
    {
        return 1;
    }

    int foreGround = 1;
    char path[25] = "";
    char options[100] = "";
    char command[100] = "";
    strcat(command, argv[0]);
    int fg_bg = 0;
    int status;
    int errorCode = 0;

    for (int i = 1; i < argc; i++)
    {
        strcat(command, " ");
        strcat(command, argv[i]);
        strcat(command, " ");
        if (strcmp(argv[i], "-e") == 0)
        {
            if (i + 1 != argc)
            {
                if (strcmp(path, "") != 0)
                {
                    return 1;
                }
                strcpy(path, argv[i + 1]);
            }
            else
            {
                return 1;
            }
            strcat(command, path);
            strcat(command, " ");
            i++;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            if (i + 1 != argc)
            {
                if (strcmp(options, "") != 0)
                {
                    return 1;
                }
                strcpy(options, argv[i + 1]);
            }
            else
            {
                return 1;
            }
            strcat(command, options);
            strcat(command, " ");
            i++;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            if (fg_bg)
            {
                return 1;
            }
            fg_bg = 1;
        }
        else if (argv[i][0] == '-')
        {
            if (argv[i][1] == 'b')
            {
                if (fg_bg)
                {
                    return 1;
                }
                fg_bg = 1;
                foreGround = 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }

    if (strcmp(path, "") == 0)
    {
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        return errno;
    }
    else if (pid == 0)
    {
        char *args[10] = {path};
        if (strcmp(options, "") != 0)
        {
            optionArray(args, options);
        }
        char *const env[] = {"PATH=/usr/bin:/bin", NULL};

        if (execve(path, args, env) == -1)
        {
            errorCode = errno; // Set errorCode if execve() fails
            _exit(1);
        }
    }
    else
    {
        if (foreGround)
        {
            if (waitpid(-1, &status, 0) == -1)
            {
                return errno;
            }
        }
    }

    if (pid != 0)
    {
        printf("Command Line: %s\n", command);
        printf("Process Id of the child: %d\n", pid);

        if (WIFEXITED(status))
        {
            printf("Exit code of the child process: %d\n", WEXITSTATUS(status));
        }
        printf("Exit code of the main program: %d\n", errorCode);
    }

    return 0;
}
