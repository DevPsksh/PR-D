//
// Created by Ayoub IDEL  on 25/02/2019.
//

#include "matrix_utils.h"
#include "general_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>


/**
 * Creates a Matrix with rows Rows & cols Columns initialized
 * with 0
 * @param rows number of rows
 * @param cols number of columns
 * @return pointer to the new MATRIX created or NULL if rows <= 0
 * or cols <= 0
 */
MATRIX *newMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        return NULL;

    MATRIX *m = (MATRIX *) malloc(sizeof(MATRIX));

    m->rows = rows;
    m->cols = cols;

    m->data = (int *) malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows * cols; i++)
        m->data[i] = 0;

    return m;
}


/**
 * Frees mtx form the the momery
 * @param mtx
 * @return either -1 if mtx is NULL or 0 if successfully deleted
 */
int deleteMatrix(MATRIX *mtx) {
    if (!mtx)
        return -1;

    assert (mtx->data);
    free(mtx->data);

    free(mtx);

    return 0;
}

#define ELEMENT_AT(mtx, row, col) mtx->data[(col-1) * mtx->rows + (row-1)]


/**
 * Copies MATRIX mtx in another MATRIX cp
 * @param mtx matrix to copy
 * @return either pointer to the copied matrix or NULL if mtx is NULL
 */
MATRIX *copyMatrix(MATRIX *mtx) {
    if (!mtx)
        return NULL;

    MATRIX *cp = newMatrix(mtx->rows, mtx->cols);

    memcpy(cp->data, mtx->data, mtx->rows * mtx->cols * sizeof(int));

    return cp;
}


/**
 * Sets the value at position (row, col) to val
 * @param mtx matrix
 * @param row position of row
 * @param col position of column
 * @param val the new value
 * @return 0 if successfully set, -1 if mtx is NULL, and -2 if row or col
 * are outside of the dimensions of mtx
 */
int setElement(MATRIX *mtx, int row, int col, int val) {
    if (!mtx)
        return -1;

    assert (mtx->data);

    if (row <= 0 || row > mtx->rows || col <= 0 || col > mtx->cols)
        return -2;

    ELEMENT_AT(mtx, row, col) = val;
    return 0;
}


/**
 * Gets an element of the matrix
 * @param mtx the matrix
 * @param row number of row
 * @param col number of column
 * @param val value of the element at (row, col)
 * @return 0 if successful, -1 if either
 * mtx or val is NULL, and -2 if row or col are outside of
 * the dimensions of mtx
 */
int getElement(MATRIX *mtx, int row, int col, int *val) {
    if (!mtx || !val)
        return -1;
    assert (mtx->data);

    if (row <= 0 || row > mtx->rows || col <= 0 || col > mtx->cols)
        return -2;

    *val = ELEMENT_AT(mtx, row, col);
    return 0;
}


/**
 * Sets
 * @param mtx
 * @param n
 * @return 0 if successful and -1 if mtx is NULL
 */
int nRows(MATRIX *mtx, int *n) {
    if (!mtx || !n) return -1;
    *n = mtx->rows;
    return 0;
}


/**
 *
 * @param mtx
 * @param n
 * @return 0 if successful and -1 if mtx is NULL
 */
int nCols(MATRIX *mtx, int *n) {
    if (!mtx || !n) return -1;
    *n = mtx->rows;
    return 0;
}


/**
 * Prints the matrix on the screen
 * @param mtx
 * @return 0 if successful
 * and -1 if mtx is NULL
 */
int printMatrix(MATRIX *mtx) {
    if (!mtx)
        return -1;

    int row, col;
    for (row = 1; row <= mtx->rows; row++) {
        for (col = 1; col <= mtx->cols; col++) {
            // Print the floating-point element with
            //  - either a - if negative or a space if positive
            //  - at least 3 spaces before the .
            //  - precision to the hundredths place
            printf("  %d   ", ELEMENT_AT(mtx, row, col));
        }
        // separate rows by newlines
        printf("\n");
    }
    return 0;
}

/**
 *
 * @param mtx
 * @param num
 * @return
 */
int *getRow(MATRIX *mtx, int num) {

    int *array = new1DArray(mtx->cols);

    if (num > mtx->rows || num <= 0) {
        printf("ERROR : impossible to get that row, please verify the number of row\n");//TODO : Log file
        return NULL;
    } else {
        for (int i = 0; i < mtx->cols; ++i) {
            getElement(mtx, num, i+1, &array[i]);
        }
        return array;
    }

}

/**
 *
 * @param mtx
 * @param array
 * @param num
 */
void setRow(MATRIX *mtx, int *array, int num) {
    for (int i = 0; i < mtx->cols; ++i) {
        setElement(mtx, num, i+1, array[i]);
    }
}
