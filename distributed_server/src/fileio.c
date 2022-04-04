#include <stdio.h>

int get_file_size(char *buffer, FILE *file){
    fseek(file, 0L, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return file_size;
}

void fileio_read_file(char *filename, char *buffer){
    FILE *file = fopen(filename, "r");

    if (!file){
        printf("Problemas ao abrir o arquivo de configuração\n");
        buffer = NULL;
    }

    int file_size = get_file_size(buffer, file);
    fread(buffer, sizeof (char), file_size, file);
    fclose(file);
}