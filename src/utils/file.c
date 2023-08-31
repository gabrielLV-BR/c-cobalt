#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "error.h"

long read_from_file(const char* path, char** buffer) {
    long file_size = -1;
    FILE* file = fopen(path, "r");

    if(!file) {
        ERROR("When opening file");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // we malloc one byte more for \0
    *buffer = (char*) malloc(file_size + 1); 

    if(*buffer == NULL) {
        ERROR("When allocating memory");
        file_size = -1;
        goto EXIT;
    }

    int read_size = fread(*buffer, sizeof (char), file_size, file);

    if(read_size != file_size) {
        ERROR("When reading file");

        free(*buffer);
        file_size = -1;
        
        goto EXIT;
    }

    #ifndef NDEBUG
        printf("READ BUFFER FROM %s\n<\n%s\n>\n", path, *buffer);
    #endif

    (*buffer)[read_size] = '\0';

EXIT:
    fclose(file);

    return file_size;
}