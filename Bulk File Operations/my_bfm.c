#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <sys/syscall.h>

#define MAX_PATH_LEN 4096

struct linux_dirent {
    unsigned long d_ino;
    off_t d_off;
    unsigned short d_reclen;
    char d_name[];
};

const char *LOG_FILE = "logfile.txt";

int write_log(char *op)
{
    int fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_CREAT, 0666);
    if (fd == -1)
    {
        return errno;
    }

    if (write(fd, op, strlen(op)) == -1)
    {
        close(fd);
        return errno;
    }

    if (close(fd) == -1)
    {
        return errno;
    }

    return 0;
}

int createFile(const char *filePath)
{
    int fd = open(filePath, O_CREAT | O_EXCL, 0666);
    if (fd == -1)
    {
        return errno;
    }

    if (close(fd) == -1)
    {
        return errno;
    }

    return 0;
}

int createDirectory(const char *dirPath)
{
    int status = mkdir(dirPath, 0755);
    if (status == -1)
    {
        return errno;
    }
    return 0;
}

int renameFile(const char *oldName, const char *newName)
{
    if (rename(oldName, newName) != 0)
    {
        return errno;
    }

    return 0;
}

int deleteFileOrDirectory(const char *path)
{
    struct stat fileStat;
    if (stat(path, &fileStat) == -1)
    {
        return errno;
    }

    if (S_ISDIR(fileStat.st_mode))
    {
        DIR *dir = opendir(path);
        if (dir == NULL)
        {
            return errno;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {

                size_t pathLen = strlen(path) + strlen(entry->d_name) + 2;
                char *entryPath = (char *)malloc(pathLen);
                if (entryPath == NULL)
                {
                    closedir(dir);
                    return ENOMEM;
                }

                snprintf(entryPath, pathLen, "%s/%s", path, entry->d_name);

                if (deleteFileOrDirectory(entryPath) != 0)
                {
                    free(entryPath);
                    closedir(dir);
                    return errno;
                }

                free(entryPath);
            }
        }

        closedir(dir);

        if (rmdir(path) == -1)
        {
            return errno;
        }
    }
    else
    {
        if (unlink(path) == -1)
        {
            return errno;
        }
    }

    return 0;
}

int appendTextOrBinaryData(const char *path, const char *data)
{
    struct stat fileStat;
    if (stat(path, &fileStat) == -1)
    {
        return errno;
    }

    if (S_ISDIR(fileStat.st_mode))
    {
        DIR *dir = opendir(path);
        if (dir == NULL)
        {
            return errno;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == 8)
            {
                char filePath[MAX_PATH_LEN];
                snprintf(filePath, MAX_PATH_LEN, "%s/%s", path, entry->d_name);

                int result = appendTextOrBinaryData(filePath, data);
                if (result != 0)
                {
                    closedir(dir);
                    return result;
                }
            }
        }

        closedir(dir);
    }
    else if (S_ISREG(fileStat.st_mode))
    {
        int fd = open(path, O_WRONLY | O_APPEND);
        if (fd == -1)
        {
            return errno;
        }

        size_t dataSize = strlen(data);
        ssize_t bytesWritten = write(fd, data, dataSize);

        if (bytesWritten == -1)
        {
            close(fd);
            return errno;
        }

        if (close(fd) == -1)
        {
            return errno;
        }
    }

    return 0;
}

int appendBinarySequence(const char *filePath, int starteven, int numBytes)
{
    if (starteven < 51 || starteven > 199)
    {
        return errno;
    }
    if (starteven % 2 == 1)
    {
        starteven = starteven + 1;
    }
    int fd = open(filePath, O_WRONLY | O_APPEND);
    if (fd == -1)
    {
        return errno;
    }

    for (int i = 0; i < numBytes; i++)
    {
        char evenNumber = starteven + 2 * i;
        ssize_t bytesWritten = write(fd, &evenNumber, sizeof(evenNumber));
        if (bytesWritten == -1)
        {
            close(fd);
            return errno;
        }
    }

    if (close(fd) == -1)
    {
        return errno;
    }

    return 0;
}

int executeOperation(int argc, char *argv[])
{
    if (argc < 3)
    {
        return 1;
    }

    const char *operation = argv[1];
    const char *path = argv[2];
    int result;

    if (strcmp(operation, "-c") == 0)
    {
        struct stat st;
        if (stat(path, &st) == 0)
        {

            if (S_ISDIR(st.st_mode))
            {
                result = createDirectory(path);
            }
            else
            {
                fprintf(stderr, "Error: The specified path is not a directory.\n");
                return 1;
            }
        }
        else
        {

            result = createFile(path);
        }
        char logMsg[500];
        sprintf(logMsg, "Created %s: %s\n", S_ISDIR(st.st_mode) ? "directory" : "file", path);
        write_log(logMsg);
        return result;
    }
    else if (strcmp(operation, "-r") == 0)
    {
        if (argc != 4)
        {
            return 1;
        }
        result = renameFile(argv[2], argv[3]);
        char logMsg[500];
        sprintf(logMsg, "Renamed %s to %s\n", argv[2], argv[3]);
        write_log(logMsg);
        return result;
    }
    else if (strcmp(operation, "-d") == 0)
    {
        if (argc != 3)
        {
            return 1;
        }
        result = deleteFileOrDirectory(argv[2]);
        char logMsg[500];
        sprintf(logMsg, "Deleted %s\n", argv[2]);
        write_log(logMsg);
        return result;
    }
    else if (strcmp(operation, "-s") == 0)
    {
        if (argc != 4)
        {
            return 1;
        }
        result = appendTextOrBinaryData(argv[2], argv[3]);
        char logMsg[500];
        sprintf(logMsg, "Appended text to %s\n", argv[2]);
        write_log(logMsg);
        return result;
    }
    else if (strcmp(operation, "-e") == 0)
    {
        if (argc != 5)
        {
            return 1;
        }
        int starteven = atoi(argv[3]);
        int numBytes = atoi(argv[4]);
        result = appendBinarySequence(argv[2], starteven, numBytes);
        char logMsg[500];
        sprintf(logMsg, "Appended even numbers to %s\n", argv[2]);
        write_log(logMsg);
        return result;
    }
    else
    {
        return 1;
    }
}

int main(int argc, char *argv[])
{
    return executeOperation(argc, argv);
}