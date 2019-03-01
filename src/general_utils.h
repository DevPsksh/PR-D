//
// Created by Ayoub IDEL  on 25/02/2019.
//

#ifndef PRD_CLEAN_GENERAL_UTILS_H
#define PRD_CLEAN_GENERAL_UTILS_H


#include "matrix_utils.h"

//ARRAYS
int *copy1DArray(int const *array, int len);
int factorial(int const n);
int **new2DArray(int rows, int columns);
void delete2DArray(int **matrix, int cols);
void show2DArray(int **array, int const rows, int const cols);
int *new1DArray(int size);
void delete1DArray(int *array);
void show1DArray(int *array, int size);
int *swap(int const *array, int size, int pos1, int pos2);
int **generate_next_level(int const *array, int fixed, int SIZE);

//MATRIX
MATRIX *generateNextLevel(int const *array, int fixed, int SIZE);
MATRIX *generateLeaves(int const *array, int SIZE, int fixed);
int* getArrayOfDistances(MATRIX *matrix, int* array);


int getTotalCost(int *a_costs, int size);
int getMinimumCost(int *a_total_costs, int size);
MATRIX* convert2DArrayToMatrix(int **array, int rows, int cols);

#endif //PRD_CLEAN_GENERAL_UTILS_H
