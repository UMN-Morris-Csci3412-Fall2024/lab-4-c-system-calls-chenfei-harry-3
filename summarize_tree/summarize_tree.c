#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static int num_dirs, num_regular;

// Function to check if the path is a directory
bool is_dir(const char* path) {
    struct stat buf;
    // Use stat to retrieve file info
    if (stat(path, &buf) != 0) {
        // Handle the error
        perror("stat");
        return false;
    }
    return S_ISDIR(buf.st_mode);
}

// Forward declaration of process_path because of recursion
void process_path(const char*);

// Function to process directories
void process_directory(const char* path) {
    num_dirs++;  

  
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    char original_dir[PATH_MAX];
    if (getcwd(original_dir, sizeof(original_dir)) == NULL) {
        perror("getcwd");
        closedir(dir);
        return;
    }

    if (chdir(path) != 0) {
        perror("chdir");
        closedir(dir);
        return;
    }

    struct dirent *entry;
    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        process_path(entry->d_name);
    }

    // Change back to the original directory
    if (chdir(original_dir) != 0) {
        perror("chdir");
    }

    closedir(dir); 
}

// Function to process files
void process_file(const char* path) {
    num_regular++;  // Increment file count
}

// Function to determine whether a path is a file or directory
void process_path(const char* path) {
    if (is_dir(path)) {
        process_directory(path);
    } else {
        process_file(path);
    }
}

// Main function
int main (int argc, char *argv[]) {
    // Ensure an argument was provided
    if (argc != 2) {
        printf ("Usage: %s <path>\n", argv[0]);
        printf ("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;
    process_path(argv[1]);
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
