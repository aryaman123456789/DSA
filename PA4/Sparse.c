#include "Matrix.h"
#include "List.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    FILE* infile = fopen(argv[1], "r");
    if (infile == NULL) {
        exit(EXIT_FAILURE);
    }
    FILE* outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        exit(EXIT_FAILURE);
    }
    int matrixSize = 0;
    int u, v, row, column;
    double value;
    fscanf(infile, " %d", &matrixSize);
    Matrix A = newMatrix(matrixSize);
    Matrix B = newMatrix(matrixSize);
    fscanf(infile, " %d", &u);
    fscanf(infile, " %d", &v);
    for (int i = 0; i < u; i++) {
        fscanf(infile, " %d", &row); 
        fscanf(infile, " %d", &column);
        fscanf(infile, " %lf", &value);
        changeEntry(A, row, column, value);
    }
    for (int i = 0; i < v; i++) {
        fscanf(infile, " %d", &row); 
        fscanf(infile, " %d", &column);
        fscanf(infile, " %lf", &value);
        changeEntry(B, row, column, value);
    }

    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");

    fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");

    fprintf(outfile, "(1.5)*A =\n");
    Matrix mult = scalarMult(1.5, A);
    printMatrix(outfile, mult);
    fprintf(outfile, "\n");

    fprintf(outfile, "A+B =\n");
    Matrix sumAB = sum(A, B);
    printMatrix(outfile, sumAB);
    fprintf(outfile, "\n");

    fprintf(outfile, "A+A =\n");
    Matrix sumAA = sum(A, A);
    printMatrix(outfile, sumAA);
    fprintf(outfile, "\n");

    fprintf(outfile, "B-A =\n");
    Matrix diffBA = diff(B, A);
    printMatrix(outfile, diffBA);
    fprintf(outfile, "\n");

    fprintf(outfile, "A-A =\n");
    Matrix diffAA = diff(A, A);
    printMatrix(outfile, diffAA);
    fprintf(outfile, "\n");

    fprintf(outfile, "Transpose(A) =\n");
    Matrix transposeA = transpose(A);
    printMatrix(outfile, transposeA);
    fprintf(outfile, "\n");

    fprintf(outfile, "A*B =\n");
    Matrix multAB = product(A, B);
    printMatrix(outfile, multAB);
    fprintf(outfile, "\n");

    fprintf(outfile, "B*B =\n");
    Matrix multBB = product(B, B);
    printMatrix(outfile, multBB);
    fprintf(outfile, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&mult);
    freeMatrix(&sumAB);
    freeMatrix(&sumAA);
    freeMatrix(&diffBA);
    freeMatrix(&diffAA);
    freeMatrix(&transposeA);
    freeMatrix(&multAB);
    freeMatrix(&multBB);
    fclose(infile);
    fclose(outfile);
    return 0;
}