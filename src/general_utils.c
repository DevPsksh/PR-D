//
// Created by Ayoub IDEL  on 25/02/2019.
//

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#include "general_utils.h"
#include "matrix_utils.h"





/**
 * Copies 1D array into another 1D array
 * @param array the array to copy
 * @param size lenght of the array
 * @return copied array with the same size
 */
int *copy1DArray(int const *array, int size) {
    int *copied = malloc(size * sizeof(int));
    memcpy(copied, array, size * sizeof(int));
    return copied;
}

/**
 * Calculates the factoriel of a value
 * @param n the value
 * @return the factorial of the value or prints an error on the screen
 */
int factorial(int const n) {
    int factorial = 1;
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");
    else
        for (int i = 1; i <= n; ++i)
            factorial *= i;

    return factorial;
}

/**
 * Swap two values of an array
 * @param array the current array
 * @param size lenght of the array
 * @param pos1 the position of the first element
 * @param pos2 the positon of the second element
 * @return the new array with the values in both positions swapped
 */
int *swap(int const *array, int size, int pos1, int pos2) {
    int *copy = copy1DArray(array, size);
    int temp = copy[pos1];
    copy[pos1] = copy[pos2];
    copy[pos2] = temp;
    return copy;
}

/**
 * Creates a 2D array
 * @param rows number of rows
 * @param cols number of columns
 * @return 2D array
 */
int **new2DArray(int rows, int cols) {
    int **array = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < cols; i++) {
        array[i] = (int *) malloc(cols * sizeof(int));
    }

    return array;
}

/**
 * Frees the memory
 * @param matrix
 * @param cols
 */
void delete2DArray(int **matrix, int cols) {
    for (int i = 0; i < cols; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

/**
 * Creates a 1D array
 * @param size
 * @return
 */
int *new1DArray(int size) {
    int *array = (int *) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        array[i] = 0;

    return array;
}

/**
 * Frees the memory
 * @param array
 */
void delete1DArray(int *array) {
    free(array);
}

/**
 * Prints 2D array on the screen
 * @param array
 * @param rows
 * @param cols
 */
void show2DArray(int **array, int const rows, int const cols) {
    //printf("ShowMatrix :\n");
    printf("[\n");
    for (int i = 0; i < rows; i++) {
        printf(" [");
        for (int j = 0; j < cols; j++) {
            printf("  %d  ", array[i][j]);
        }
        printf(" ]\n");
    }
    printf("]\n");
}

/**
 * Prints 1D array on the screen
 * @param array
 * @param size
 */
void show1DArray(int *array, int size) {
    printf("[");
    for (int j = 0; j < size; j++) {
        printf("  %d  ", array[j]);
    }
    printf(" ]\n");
}

/**
 * //TODO : this method must be deleted
 * //TODO : NEVER USE THIS
 * @param array
 * @param fixed
 * @param SIZE
 * @return
 */
int **generate_next_level(int const *array, int fixed, int SIZE) {
    int size_level_plus_1 = SIZE - fixed;
    int **result = new2DArray(size_level_plus_1, SIZE);

    //array copied
    int *temp = copy1DArray(array, SIZE);

    for (int i = 0; i < size_level_plus_1; i++) {
        result[i] = swap(temp, SIZE, fixed, fixed + i);
    }
    return result;
}

/**
 * //TODO : this method must be deleted
 * //TODO : NEVER USE THIS
 * @version 1.0
 * @param array
 * @param fixed
 * @return
 */
int **generate_n_level(int const *array, int fixed, int SIZE) {

    int *array_copy = copy1DArray(array, SIZE);
    int leaves_level = factorial(SIZE);
    int **tmp = new2DArray(1, SIZE);

    for (int i = 0; i < SIZE; i++) {
        tmp[0][i] = array[i];
    }
    //show_matrix(tmp, 1, SIZE);

    int **result = new2DArray(leaves_level, SIZE);

    tmp = generate_next_level(array_copy, fixed, SIZE);
    show2DArray(tmp, SIZE, SIZE);
    for (int i = 1; i < SIZE; i++) {
        int **tmp2 = new2DArray(SIZE * (SIZE - i), SIZE);
        printf("i = %d \n", i);
        int count = 0;
        int size_current_level = factorial(SIZE) / factorial(SIZE - i);
        for (int j = 0; j < size_current_level; ++j) {
            //show_matrix(generate_next_level(tmp[j], i), SIZE-i, SIZE);
            for (int k = 0; k < (SIZE - i); ++k) {
                tmp2[count] = generate_next_level(tmp[j], i, SIZE)[k];
                count++;
            }
            printf("tmp2 = %d \n ", j);
            show2DArray(tmp2, count, SIZE);
        }
        printf("tmp  \n ");
        memcpy(tmp, tmp2, sizeof(int) * count * SIZE);
        show2DArray(tmp, count, SIZE);
    }

    return tmp;
}

/**
 * Generates all leaves of a node
 * @version 1.2
 * @param array
 * @param fixed
 * @param SIZE
 * @return
 */
MATRIX *generateNextLevel(int const *array, int fixed, int SIZE) {
    int size_level_plus_1 = SIZE - fixed;
    MATRIX *rslt = newMatrix(size_level_plus_1, SIZE);

    for (int j = 0; j < rslt->rows; ++j) {
        for (int i = 0; i < rslt->cols; ++i) {
            setElement(rslt, j + 1, i + 1, array[i]);
        }
    }

    int tmpp = 0;
    for (int i = 0; i < size_level_plus_1; i++) {
        setElement(rslt, i + 1, fixed + 1, array[fixed + i]);
        setElement(rslt, i + 1, fixed + 1 + i, array[fixed]);
    }

    return rslt;
}

/**
 *
 * @param array
 * @param SIZE
 * @return
 */
 /*
MATRIX *generateLeaves(int const *array, int SIZE) {

    MATRIX *mtx_tmp = generateNextLevel(array, 0, SIZE);
    //printf("PrintMatrix\n");
    //printMatrix(mtx_tmp);
    for (int i = 1; i < SIZE; i++) {
        MATRIX *mtx_tmp2 = newMatrix(factorial(SIZE) / factorial(SIZE - i - 1), SIZE);
        //printf("i = %d \n", i);
        int count = 0;
        int size_current_level = factorial(SIZE) / factorial(SIZE - i);
        for (int j = 0; j < size_current_level; ++j) {
            //printf("j = %d \n", j);
            MATRIX *mtx_tmp3 = generateNextLevel(getRow(mtx_tmp, j + 1), i, SIZE);
            //printf("print tmp3 at j = %d\n", j);
            //printMatrix(mtx_tmp3);
            for (int k = 0; k < (SIZE - i); ++k) {
                //printf("k = %d \n", k);
                setRow(mtx_tmp2, getRow(mtx_tmp3, k + 1), count + 1);
                count++;
            }
            //printf("tmp2 j = %d , count = %d \n ", j, count);
            //printMatrix(mtx_tmp2);

            deleteMatrix(mtx_tmp3);
        }
        //printf("tmp  i = %d \n ", i);
        mtx_tmp = copyMatrix(mtx_tmp2);
        deleteMatrix(mtx_tmp2);
        //printMatrix(mtx_tmp);
    }
    printf("----------------------------------------------------------\n");
    printf("final matrix : rows = %d  cols = %d \n", mtx_tmp->rows, mtx_tmp->cols);
    printMatrix(mtx_tmp);
    printf("----------------------------------------------------------\n");
    return mtx_tmp;
}
  */

 /**
  * Final version of Generator of leaves
  * @param array
  * @param SIZE
  * @param fixed
  * @return
  */
 MATRIX *generateLeaves(int const *array, int SIZE, int fixed) {


     MATRIX *mtx_tmp = generateNextLevel(array, fixed, SIZE);
     //printf("PrintMatrix\n");
     //printMatrix(mtx_tmp);
     for (int i = 1; i < SIZE-fixed; i++) {
         MATRIX *mtx_tmp2 = newMatrix(factorial(SIZE - fixed) / factorial(SIZE - i - 1 - fixed), SIZE);
         //printf("i = %d \n", i);
         int count = 0;
         int size_current_level = factorial(SIZE - fixed) / factorial(SIZE - i - fixed);
         for (int j = 0; j < size_current_level; ++j) {
             //printf("j = %d \n", j);
             MATRIX *mtx_tmp3 = generateNextLevel(getRow(mtx_tmp, j + 1), i + fixed, SIZE);
             //printf("print tmp3 at j = %d\n", j);
             //printMatrix(mtx_tmp3);
             for (int k = 0; k < (SIZE - i - fixed); ++k) {
                 //printf("k = %d \n", k);
                 setRow(mtx_tmp2, getRow(mtx_tmp3, k + 1), count + 1);
                 count++;
             }
             //printf("tmp2 j = %d , count = %d \n ", j, count);
             //printMatrix(mtx_tmp2);

             deleteMatrix(mtx_tmp3);
         }
         //printf("tmp  i = %d \n ", i);
         mtx_tmp = copyMatrix(mtx_tmp2);
         deleteMatrix(mtx_tmp2);
         //printMatrix(mtx_tmp);
     }
     //printf("---------------------\n");
     //printf("final matrix : fixed = %d rows = %d  cols = %d \n", fixed, mtx_tmp->rows, mtx_tmp->cols);
     //printMatrix(mtx_tmp);
     //printf("----------------------\n");
     return mtx_tmp;
 }

 /**
  * Gives the array of distances of a specific array
  * @param matrix
  * @param array
  * @return
  */
int *getArrayOfDistances(MATRIX *matrix, int *array) {

    //TODO : Verify the size

    int size_array = matrix->cols;
    int *result = new1DArray(size_array);

    int value = 0;

    for (int i = 0; i < size_array - 1; ++i) {
        getElement(matrix, array[i], array[i + 1], &value);
        result[i] = value;
        //printf("result[%d] = %d\n", i, result[i]);
    }

    return result;
}

/**
 * Calculate the total cost of an array
 * @param a_costs array of costs
 * @return total value
 */
int getTotalCost(int *a_costs, int size) {
    if (a_costs == NULL)
        return 0;

    int total = 0;

    for (int i = 0; i < size; i++) {
        total += a_costs[i];
    }
    return total;
}

/**
 * Find the minimum value of an array
 * @param a_total_costs array of total costs
 * @return minimum cost
 */
int getMinimumCost(int *a_total_costs, int size) {
    if (a_total_costs == NULL)
        return 0;

    int minimum = a_total_costs[0];

    for (int i = 1; i < size; i++) {
        if (minimum > a_total_costs[i]) {
            minimum = a_total_costs[i];
        }
    }
    return minimum;
}

/**
 *
 * @param array
 * @param rows
 * @param cols
 * @return
 */
MATRIX *convert2DArrayToMatrix(int **array, int rows, int cols) {

    MATRIX *matrix = newMatrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            setElement(matrix, i + 1, j + 1, array[i][j]);
        }
    }

    return matrix;
}


//int main() {
//
//    int **array = create_matrix(SIZE, SIZE);
//    int count = 0;
//
//    for (int i = 0; i < SIZE; i++)
//        for (int j = 0; j < SIZE; j++)
//            array[i][j] = count++;
//
//    show_matrix(array, SIZE, SIZE);
//
//    int *array2 = create_array(4);
//    showArray(array2, SIZE);
//    int *arraySwap = swap(array2, 0, 3);
//    show_array(arraySwap, SIZE);
//
//    int array[] = {1, 2, 3, 4, 5, 6};
//
//    int fixed = 3;
//    int size_result = SIZE - fixed;
//
//    printf("Size MATRIX : %d  \nFixed : %d  \nSize results : %d \n\n", SIZE, fixed, size_result);
//
//    int **result = generate_next_level(array, fixed);
//    show_matrix(result, size_result, SIZE);
//
//    //printf("Factoriel : %lld \n", factorial(4));
//
//    printf("\n\n============================\n\n");
//
//    //generateNLevel(array, 0, SIZE-1);
//    //generate_last_level(array, fixed);
//
//
//    int **result2 =generateNLevel(array, 1);
//    show_matrix(result2, factorial(size_result), SIZE);
//
//
//    return 0;
//}