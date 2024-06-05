#include "List.h"
#define MAX_LEN 255
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");
    if (infile == NULL || outfile == NULL) {
        fprintf(stderr, "Error: could not open file\n");
        exit(EXIT_FAILURE);
    }
    int n = 0;
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, infile) != NULL) {
        n++;
    }
    rewind(infile);
    char **stringArray = calloc(n, sizeof(char *));
    for (int i = 0; i < n; i++) {
        stringArray[i] = calloc(MAX_LEN, sizeof(char));
        fgets(stringArray[i], MAX_LEN, infile);
    }
    List list = newList();
    append(list, 0);
    for (int i = 1; i < n; i++) {
        moveBack(list);
        int j = get(list);
        while (j >= 0 && strcmp(stringArray[i], stringArray[j]) < 0) {
            movePrev(list);
            j = get(list);
        }
        if (index(list) >= 0) {
            insertAfter(list, i);
        } else {
            prepend(list, i);
        }
    }
    moveFront(list);
    while (index(list) >= 0) {
        fprintf(outfile, "%s", stringArray[get(list)]);
        moveNext(list);
    }
    moveFront(list);
    List sortedList = newList();
    while (index(list) >= 0) {
        append(sortedList, get(list));
        moveNext(list);
    }
    moveFront(sortedList);
    while (index(sortedList) >= 0) {
        fprintf(outfile, "%s", stringArray[get(sortedList)]);
        moveNext(sortedList);
    }
    freeList(&sortedList);
    for (int i = 0; i < n; i++) {
        free(stringArray[i]);
    }
    free(stringArray);
    freeList(&list);
    fclose(infile);
    fclose(outfile);
    return 0;
}
