#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "reverse.h"

int main() {
    DIR *dir;
    struct dirent *entry;

    char input_dir_name[50] = "art/";
    char output_dir_name[50] = "reversed/";
    dir = opendir("art");
    if (!dir) {
        printf("Can't read directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        char* input_file_name = entry->d_name;
        char input_file_path[] = "art/";
        strcat(input_file_path, input_file_name);
        if (strstr(input_file_name, ".txt") != NULL ) {
            if (!reverse(input_file_path, input_file_name))
                printf("Success!\n");
            else
                printf("Something went wrong :l\n");
        }
    }

    closedir(dir);
    return 0;
}
