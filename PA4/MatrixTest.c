#include "Matrix.h"

int main() {
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);
    changeEntry(A, 1, 1, 3.5);
    changeEntry(A, 1, 2, 1.5);
    changeEntry(A, 2, 3, 2.5);
    changeEntry(A, 3, 1, 4.5);
    changeEntry(B, 1, 1, 2.5);
    changeEntry(B, 1, 2, 1.5);
    changeEntry(B, 2, 3, 3.5);
    changeEntry(B, 3, 1, 1.5);

    printf("Size of Matrix A: %d, NNZ: %d\n", size(A), NNZ(A));

    printf("Size of Matrix A and B are%s equal.\n", equals(A, B) ? "" : " not");

    makeZero(A);
    printf("Matrix A after makeZero:\n");
    printMatrix(stdout, A);

    Matrix BCopy = copy(B);
    printf("Matrix B and direct copy of Matrix B:\n");
    printMatrix(stdout, B);
    printMatrix(stdout, BCopy);

    Matrix Btranspose = transpose(B);
    printf("Matrix B and the transpose of Matrix B:\n");
    printMatrix(stdout, B);
    printMatrix(stdout, Btranspose);

    Matrix Bscalarmult = scalarMult(2.0, B);
    printf("Matrix B and the scalar multiplication of Matrix B by 2.0:\n");
    printMatrix(stdout, B);
    printMatrix(stdout, Bscalarmult);

    Matrix matrixSum = sum(B, Btranspose);
    printf("Sum of Matrix B and its transpose:\n");
    printMatrix(stdout, matrixSum);

    Matrix matrixDiff = diff(B, Btranspose);
    printf("Diff between Matrix B and its transpose:\n");
    printMatrix(stdout, matrixDiff);

    Matrix matrixProduct = product(B, Btranspose);
    printf("Product of Matrix B and its transpose:\n");
    printMatrix(stdout, matrixProduct);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&BCopy);
    freeMatrix(&Btranspose);
    freeMatrix(&Bscalarmult);
    freeMatrix(&matrixSum);
    freeMatrix(&matrixDiff);
    freeMatrix(&matrixProduct);
    return 0;
}