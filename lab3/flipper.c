#include <stdio.h>
#define MAX_LINE_SIZE 1000

int main() {
    FILE * input_file = fopen("art/pikachu.txt", "r");
    FILE * output_file = fopen("reversed/reversed_pikachu", "w");
    if (!input_file) {
        printf("Can't read file");
        return 1;
    }

    char buffer[MAX_LINE_SIZE];
    /* while (fseek(input_file, --i, SEEK_END) == 0) { */
    /*     fread(&buffer, sizeof(char), 1, input_file); */
    /*     fwrite(&buffer, sizeof(char), 1, output_file); */
    /* } */

    while (fgets(buffer, MAX_LINE_SIZE, input_file) != NULL) {
        /* printf("Current buffer: %s\n", buffer); */
        int last_index = 0;
        while (buffer[last_index] != '\0')
            last_index++;
        /* int buffer_length = sizeof(buffer) / sizeof(buffer[0]); */
        for (int i = last_index; i > 0; --i) {
            printf("%c", buffer[i]);
            fwrite(&buffer[i], sizeof(char), 1, output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
    return 0;
}
