/*
 ** MAIN FILE FOR SEGMENTATION
 ** - Free Functions
 ** - Main Segmentation Function
 ** - Main Preprocessing Function
 */

#include "../segmentation/segmentation.h"
#include "headers/decode.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void Help()
{
    printf("Usage: ./decode [File To Decode] [OPTIONS]\n            Decodes a QrCode from a file\n\n");
    printf("OPTIONS\n\n");
    printf("  -e                Decodes an Epicode instead of a QrCode\n\n");
    printf("  -h                Help\n");
}

void write_file(char *string)
{
    FILE* file = NULL;

    file = fopen("./output/results.txt", "w");

    if (file != NULL)
    {
        fprintf(file, "%s\n", string);
        fclose(file);
    }
}

int main(int argc, char *argv[])
{
    struct PCode* data;
    if(argc > 2)
    {
        if(strcmp(argv[2], "-d") == 0)
            data = SegmentationFromFile(argv[1], 1);
        else if(strcmp(argv[2], "-e") == 0)
            data = SegmentationFromFile(argv[1], 2);
        else if(strcmp(argv[2], "-h") == 0){
            Help();
            exit(EXIT_SUCCESS);
        }
    }
    else if(argc > 1){
        if(strcmp(argv[1], "-h") == 0){
            Help();
            exit(EXIT_SUCCESS);
        }
        data = SegmentationFromFile(argv[1], 0);
    }
    else
        return EXIT_FAILURE;

    int s_level;
    switch(data->ECL)
    {
        case 'M':
            s_level = 1;
            break;
        case 'Q':
            s_level = 2;
            break;
        case 'H':
            s_level = 3;
            break;
        default:
            s_level = 0;
            break;

    }
    char* string = malloc(4 * sizeof(char));
    string[0] = 'N';
    string[1] = '/';
    string[2] = 'A';
    string[3] = '\0';
    string = decode(data->BStream, data->Version, s_level);
    write_file(string);   
    sleep(1);
    printf("Output : %s\n", string);
    free(string);
    return EXIT_SUCCESS;
}
