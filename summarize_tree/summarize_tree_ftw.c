#include <stdio.h>
#include <sys/stat.h>
#include <ftw.h>   
#include <stdbool.h>
#include <stdlib.h>

static int num_dirs = 0;
static int num_regular = 0;
static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_D) {
        num_dirs++;
    } else if (typeflag == FTW_F) {
        num_regular++;
    }
    return 0;  
}

#define MAX_FTW_DEPTH 16 

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    if (ftw(argv[1], callback, MAX_FTW_DEPTH) != 0) {
        perror("ftw");
        return 1;
    }

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
