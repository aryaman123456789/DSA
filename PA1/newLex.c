#include "List.h"
#define MAX_LEN 255

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        exit(EXIT_FAILURE);
    }
    FILE* infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Unable to read from file, %s.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    FILE* outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr, "Unable to write to file, %s.\n", argv[2]);
        exit(EXIT_FAILURE);
    }  
    char str[MAX_LEN];
    int lineCount = 0;
    while (fgets(str, MAX_LEN, in) != NULL) {
        lineCount++;
    }
    fclose(infile);
    infile = fopen(argv[1], "r");
    char strArr[lineCount][MAX_LEN];
    lineCount = 0;
    while (fgets(str, MAX_LEN, infile) != NULL) {
        for (int i = 0; i < MAX_LEN; i++) {
            strArr[lineCount][i] = str[i];
        }
        lineCount++;
    }   
    List strList = newList();
    for (int i = 0; i < lineCount; i++) {
        moveBack(strList);
        while (index(strList) >= 0 &&  strcmp(strArr[i], strArr[get(strList)]) < 0) {
            movePrev(strList);
        }
        if (index(strList) >= 0) {
            insertAfter(strList, i);
        }
        else {
            prepend(strList, i);
        }
    }
    moveFront(strList);
    while (index(strList) >= 0) {
        fprintf(outfile, "%s", strArr[get(strList)]);
        moveNext(strList);
    }
    freeList(&strList);
    strList = NULL;
    fclose(infile);
    fclose(outfile);
    return 0;
}