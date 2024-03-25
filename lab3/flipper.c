#include <stdio.h>

int main() {
    FILE * input_file = fopen("art/pikachu.txt", "r");
    FILE * output_file = fopen("reversed/reversed_pikachu", "w");
    if (!input_file) {
        printf("Can't read file");
        return 1;
    }

    char first_line[1000];
    fgets(first_line, sizeof(first_line), input_file);
    printf("%s", first_line);
    while ( fgets(first_line, sizeof(first_line), input_file) != NULL ) {

    }
    // int current_character = fgetc(input_file);
    // while (current_character != EOF) {
    //     // printf("%c", current_character);
    //     current_character = fgetc(input_file);
    //     putc(current_character, output_file);
    // }

    fclose(input_file);
    input_file = NULL;
    return 0;
}
