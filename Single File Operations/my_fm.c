#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int createFile(const char *filePath) {
    int fd = open(filePath, O_CREAT | O_EXCL, 0666);
    if (fd == -1) {
        return errno;
    }

    if (close(fd) == -1) {
        return errno;
    }

    return 0;
}

int renameFile(const char *oldName, const char *newName) {
    if (rename(oldName, newName) != 0) {
        return errno;
    }

    return 0;
}

int deleteFileOrDirectory(const char *path) {
    struct stat fileStat;
    if (stat(path, &fileStat) == -1) {
        return errno;
    }

    if (S_ISDIR(fileStat.st_mode)) {
        return EISDIR;
    } else {
        if (unlink(path) == -1) {
            return errno;
        }
    }

    return 0;
}

int createDirectoryAndFile(const char *path) {
    struct stat fileStat;
    if (stat(path, &fileStat) != 0) {
        if (errno == ENOENT) {
            if (mkdir(path, 0777) == -1) {
                return errno;
            }
        } else {
            return errno;
        }
    } else {
        if (S_ISDIR(fileStat.st_mode)) {
            char newFilePath[256];
            snprintf(newFilePath, sizeof(newFilePath), "%s/new_file.txt", path);
            return createFile(newFilePath);
        }
    }

    return 0;
}

int appendTextOrBinaryData(const char *filePath, const char *data) {
    int fd = open(filePath, O_WRONLY | O_APPEND);
    if (fd == -1) {
        return errno;
    }

    size_t dataSize = strlen(data);
    ssize_t bytesWritten = write(fd, data, dataSize);

    if (bytesWritten == -1) {
        close(fd);
        return errno;
    }

    if (close(fd) == -1) {
        return errno;
    }

    return 0;
}

int appendBinarySequence(const char *filePath, int startOdd, int numBytes) {
    if (startOdd % 2 == 0) {
        return EINVAL;
    }

    int fd = open(filePath, O_WRONLY | O_APPEND);
    if (fd == -1) {
        return errno;
    }

    for (int i = 0; i < numBytes; i++) {
        char oddNumber = startOdd + 2 * i;
        ssize_t bytesWritten = write(fd, &oddNumber, sizeof(oddNumber));

        if (bytesWritten == -1) {
            close(fd);
            return errno;
        }
    }

    if (close(fd) == -1) {
        return errno;
    }

    return 0;
}

int output_on_cmd(char* path){
    int fd = open(path, O_RDONLY);
    if (fd == -1){
        return errno;
    }
    char buf[50];
    int read_status = read(fd, buf, 50);
    if (read_status == -1){
        return errno;
    }
    int write_status = write(1, buf, 50);
    if (write_status == -1){
        return errno;
    }
    close(fd);
    return errno;
}

int executeOperation(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    const char *operation = argv[1];

    if (strcmp(operation, "create_file") == 0) {
        if (argc != 3) {
            return 1;
        }
        return createFile(argv[2]);
    } else if (strcmp(operation, "rename_file") == 0) {
        if (argc != 4) {
            return 1;
        }
        return renameFile(argv[2], argv[3]);
    } else if (strcmp(operation, "delete_file_or_directory") == 0) {
        if (argc != 3) {
            return 1;
        }
        return deleteFileOrDirectory(argv[2]);
    } else if (strcmp(operation, "create_directory_and_file") == 0) {
        if (argc != 3) {
            return 1;
        }
        return createDirectoryAndFile(argv[2]);
    } else if (strcmp(operation, "append_text") == 0) {
        if (argc != 4) {
            return 1;
        }
        return appendTextOrBinaryData(argv[2], argv[3]);
    } else if (strcmp(operation, "append_binary_sequence") == 0) {
        if (argc != 5) {
            return 1;
        }
        int startOdd = atoi(argv[3]);
        int numBytes = atoi(argv[4]);
        return appendBinarySequence(argv[2], startOdd, numBytes);
    }else if(strcmp(operation, "output_on_cmd") == 0){
        if (argc != 3) {
            return 1;
        }
        return output_on_cmd(argv[2]);
    }
    else {
        return 1;
    }
}

int main(int argc, char *argv[]) {
    return executeOperation(argc, argv);
}

