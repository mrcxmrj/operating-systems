#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "reverse.h"

int main() {
    DIR *dir;
    struct dirent *entry;

    char input_dir_name[] = "art/";
    char output_dir_name[] = "reversed/";

    dir = opendir(input_dir_name);
    if (!dir) {
        printf("Can't read directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_type != DT_REG) continue;

        char* input_file_name = entry->d_name;
        if (strstr(input_file_name, ".txt") != NULL ) {
            char input_file_path[100];
            strcpy(input_file_path, input_dir_name);
            strcat(input_file_path, input_file_name);

            char output_file_path[100];
            strcpy(output_file_path, output_dir_name);
            strcat(output_file_path, input_file_name);

            if (!reverse(input_file_path, output_file_path))
                printf("Success!\n");
            else
                printf("Something went wrong :l\n");
        }
    }

    closedir(dir);
    return 0;
}
