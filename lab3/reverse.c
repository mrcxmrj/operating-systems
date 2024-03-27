#include <stdio.h>
#include "reverse.h"

int reverse(char* input_path, char* output_path) {
    FILE* input_file = fopen(input_path, "r");
    FILE* output_file = fopen(output_path, "w");
    if (!input_file) {
        printf("Can't read file %s\n", input_path);
        return 1;
    }

    char buffer[MAX_LINE_SIZE];

    while (fgets(buffer, MAX_LINE_SIZE, input_file) != NULL) {
        int last_index = 0;
        while (buffer[last_index] != '\0')
            last_index++;
        for (int i = last_index; i > 0; --i) {
            fwrite(&buffer[i], sizeof(char), 1, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
    return 0;
}
