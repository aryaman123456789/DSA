#include "List.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments: %d", argc);
        exit(EXIT_FAILURE);
    }
    FILE* infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Input File cannot be opened.");
        exit(EXIT_FAILURE);
    }
    FILE* outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr, "Output File cannot be opened.");
        exit(EXIT_FAILURE);
    }
    int lineCount = 0;
    char c;
    char string[256];
    while (!feof(infile)) {
        c = fgetc(infile);
        if(c == '\n') {
            lineCount++;
        }
    }
    fclose(infile);
    infile = fopen(argv[1], "r");
    char new[lineCount][256];
    lineCount = 0;
    while (fgets(string, 256, infile) != NULL) {
        for (int i = 0; i < 256; i++) {
            new[lineCount][i] = string[i];
        }
        lineCount++;
    }
    List stringarr = newList();
    for (int i = 0; i < lineCount; i++) {
        moveBack(stringarr);
        while (index(stringarr) > -1 &&  strcmp(new[i], new[get(stringarr)]) < 0) {
            movePrev(stringarr);
        }
        if (index(stringarr) > -1) {
            insertAfter(stringarr, i);
        }
        else {
            prepend(stringarr, i);
        }
    }
    moveFront(stringarr);
    while (index(stringarr) > -1) {
        fprintf(outfile, "%s", new[get(stringarr)]);
        moveNext(stringarr);
    }
    freeList(&stringarr);
    stringarr = NULL;
    fclose(infile);
    fclose(outfile);
    return 0;
}
