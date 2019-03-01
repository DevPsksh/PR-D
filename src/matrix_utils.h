//
// Created by Ayoub IDEL  on 25/02/2019.
//

#ifndef PRD_CLEAN_MATRIX_UTILS_H
#define PRD_CLEAN_MATRIX_UTILS_H

typedef struct {
    int rows;
    int cols;
    int *data;
} MATRIX;


MATRIX *newMatrix(int rows, int cols);
int deleteMatrix(MATRIX *mtx);
MATRIX *copyMatrix(MATRIX *mtx);
int setElement(MATRIX *mtx, int row, int col, int val);
int getElement(MATRIX *mtx, int row, int col, int *val);
int nRows(MATRIX *mtx, int *n);
int nCols(MATRIX *mtx, int *n);
int printMatrix(MATRIX *mtx);
int* getRow(MATRIX *mtx, int num);
void setRow(MATRIX *mtx, int* array, int num);


#endif //PRD_CLEAN_MATRIX_UTILS_H
