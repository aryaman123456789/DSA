#include "Matrix.h"

typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

Entry newEntry(int column, double value) {
    Entry entry = malloc(sizeof(EntryObj));
    entry->column = column;
    entry->value = value;
    return entry;
}

typedef struct MatrixObj {
    int size;
    int NNZ;
    List* rows;
} MatrixObj;

int getEntryCol(Entry entry) {
    return entry->column;
}

double getEntryValue(Entry entry) {
    return entry->value;
}

Matrix newMatrix(int n) {
    Matrix new = malloc(sizeof(MatrixObj));
    new->size = n;
    new->NNZ = 0;
    new->rows = calloc(n, sizeof(List));
    for (int i = 0; i < n; i++) {
        new->rows[i] = newList();
    }
    return new;
}

void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 0; i < (*pM)->size; i++) {
            List row = (*pM)->rows[i];
            moveFront(row);
            while (index(row) >= 0) {
                Entry entry = (Entry)get(row);
                free(entry);
                moveNext(row);
            }
            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}

void freeEntry(Entry* pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

int size(Matrix M) {
    return M->size;
}

int NNZ(Matrix M) {
    return M->NNZ;
}

int listEqual(List A, List B);
int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size || A->NNZ != B->NNZ) {
        return 0; 
    }
    for (int i = 0; i < A->size; i++) {
        List a = A->rows[i];
        List b = B->rows[i];
        if (!listEqual(a, b)) {
            return 0; 
        }
    }
    return 1; 
}

int listEqual(List A, List B) {
    if (A == NULL || B == NULL) {
        exit(EXIT_FAILURE);
    }
    if (length(A) != length(B)) {
        return 0; 
    }
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0) {
        Entry a = (Entry)get(A);
        Entry b = (Entry)get(B);

        if (getEntryCol(a) != getEntryCol(b) || getEntryValue(a) != getEntryValue(b)) {
            return 0; 
        }
        moveNext(A);
        moveNext(B);
    }
    return 1; 
}

void makeZero(Matrix M) {
    for (int i = 0; i < M->size; i++) {
        List zero = M->rows[i];
        moveFront(zero);
        while (index(zero) >= 0) {
            Entry entry = (Entry)get(zero);
            free(entry);
            moveNext(zero);
        }
        clear(zero);
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        exit(EXIT_FAILURE);
    }
    List change = M->rows[i - 1];
    moveFront(change);
    while (index(change) >= 0 && getEntryCol((Entry)get(change)) < j) {
        moveNext(change);
    }
    if (index(change) >= 0 && getEntryCol((Entry)get(change)) == j) {
        if (x != 0.0) {
            ((Entry)get(change))->value = x; 
        } else {
            Entry temp = (Entry)get(change);
            delete(change);
            free(temp);
            M->NNZ--;
        }
    } else {
        if (x != 0.0) {
            if (index(change) >= 0) {
                insertBefore(change, newEntry(j, x));
            } else {
                append(change, newEntry(j, x));
            }
            M->NNZ++;
        }
    }
}

Matrix copy(Matrix A) {
    if (A == NULL) {
        exit(EXIT_FAILURE);
    }
    Matrix directCopy = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        List a = A->rows[i];
        List b = directCopy->rows[i];
        moveFront(a);
        while (index(a) >= 0) {
            Entry entry = get(a);
            append(b, newEntry(entry->column, entry->value));
            moveNext(a);
        }
    }
    directCopy->NNZ = A->NNZ;
    return directCopy;
}

Matrix transpose(Matrix M) {
    if (M == NULL) {
        exit(EXIT_FAILURE);
    }
    Matrix transposed = newMatrix(M->size);
    for (int i = 0; i < M->size; i++) {
        List row = M->rows[i];
        moveFront(row);
        while (index(row) >= 0) {
            Entry entry = (Entry)get(row);
            int column = getEntryCol(entry);
            double value = getEntryValue(entry);
            changeEntry(transposed, column, (i + 1), value);
            moveNext(row);
        }
    }
    return transposed;
}

Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        exit(EXIT_FAILURE);
    }
    Matrix mult = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        List a = A->rows[i];
        List b = mult->rows[i];
        moveFront(a);
        while (index(a) >= 0) {
            Entry entry = get(a);
            append(b, newEntry(entry->column, (x * entry->value)));
            moveNext(a);
        }
    }
    mult->NNZ = A->NNZ;
    return mult;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        return scalarMult(2.0, A);
    }
    Matrix SumM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List ListA = A->rows[i - 1];
        List ListB = B->rows[i - 1];
        List ListSum = SumM->rows[i - 1];
        moveFront(ListA);
        moveFront(ListB);
        while (index(ListA) >= 0 || index(ListB) >= 0) {
            int columnA = (index(ListA) >= 0) ? getEntryCol(get(ListA)) : -1;
            int columnB = (index(ListB) >= 0) ? getEntryCol(get(ListB)) : -1;
            if (columnA == columnB) {
                if (columnA != -1) {
                    double sum = getEntryValue(get(ListA)) + getEntryValue(get(ListB));
                    if (sum != 0.0) {
                        append(ListSum, newEntry(columnA, sum));
                        SumM->NNZ++;
                    }
                    moveNext(ListA);
                    moveNext(ListB);
                }
            } else if ((columnA < columnB && columnA != -1) || columnB == -1) {
                append(ListSum, newEntry(columnA, getEntryValue(get(ListA))));
                SumM->NNZ++;
                moveNext(ListA);
            } else if ((columnB < columnA && columnB != -1) || columnA == -1) {
                append(ListSum, newEntry(columnB, getEntryValue(get(ListB))));
                SumM->NNZ++;
                moveNext(ListB);
            }
        }
    }
    return SumM;
}

Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        exit(EXIT_FAILURE);
    }
    Matrix DiffM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List ListA = A->rows[i - 1];
        List ListB = B->rows[i - 1];
        List ListDiff = DiffM->rows[i - 1];
        moveFront(ListA);
        moveFront(ListB);
        while (index(ListA) >= 0 || index(ListB) >= 0) {
            int columnA = (index(ListA) >= 0) ? getEntryCol(get(ListA)) : -1;
            int columnB = (index(ListB) >= 0) ? getEntryCol(get(ListB)) : -1;
            if (columnA == columnB) {
                if (columnA != -1) {
                    double diff = getEntryValue(get(ListA)) - getEntryValue(get(ListB));
                    if (diff != 0.0) {
                        append(ListDiff, newEntry(columnA, diff));
                        DiffM->NNZ++;
                    }
                    moveNext(ListA);
                    moveNext(ListB);
                }
            } else if ((columnA < columnB && columnA != -1) || columnB == -1) {
                append(ListDiff, newEntry(columnA, getEntryValue(get(ListA))));
                DiffM->NNZ++;
                moveNext(ListA);
            } else if ((columnB < columnA && columnB != -1) || columnA == -1) {
                append(ListDiff, newEntry(columnB, -getEntryValue(get(ListB))));
                DiffM->NNZ++;
                moveNext(ListB);
            }
        }
    }
    return DiffM;
}


Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        exit(EXIT_FAILURE);
    }
    Matrix Acopy = newMatrix(A->size);
    Matrix Btranspose = transpose(B); 
    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i-1];
        if (length(rowA) == 0) {
            continue;
        }
        for (int j = 1; j <= Btranspose->size; j++) {
            List rowBtranspose = Btranspose->rows[j-1];
            if (length(rowBtranspose) == 0) {
                continue; 
            } 
            double dotProduct = vectorDot(rowA, rowBtranspose);
            if (dotProduct != 0.0) {
                changeEntry(Acopy, i, j, dotProduct);
            }
        }
    }
    freeMatrix(&Btranspose);
    return Acopy;
}

double vectorDot(List A, List B) {
    moveFront(A);
    moveFront(B);
    double entrySum = 0.0;
    while (index(A) >= 0 && index(B) >= 0) {
        Entry a = (Entry)get(A);
        Entry b = (Entry)get(B);
        if (getEntryCol(a) == getEntryCol(b)) {
            entrySum += getEntryValue(a) * getEntryValue(b);
            moveNext(A);
            moveNext(B);
        } else if (getEntryCol(a) < getEntryCol(b)) {
            moveNext(A);
        } else {
            moveNext(B);
        }
    }
    return entrySum;
}

void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < M->size; i++) {
        List L = M->rows[i];
        if (length(L) > 0) {
            fprintf(out, "%d: ", (i + 1));
            moveFront(L);
            while (index(L) >= 0) {
                Entry entry = (Entry)get(L);
                fprintf(out, "(%d, %.1f) ", getEntryCol(entry), getEntryValue(entry));
                moveNext(L);
            }
            fprintf(out, "\n");
        }
    }
}