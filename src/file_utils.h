//
// Created by Ayoub IDEL  on 25/02/2019.
//

#ifndef PRD_CLEAN_FILE_UTILS_H
#define PRD_CLEAN_FILE_UTILS_H


#include <printf.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "file_utils.h"
#include "matrix_utils.h"
#include "client_utils.h"


char *loadFileIntoArray(char *filename);
int getColumns(const char *const line, const char *const delim, char ***out_storage);
MATRIX* loadFileIntoMatrix(char* filename, int size);

int write2FileMatrix(char const *filename, MATRIX* matrix, char* msg);
int write2FileDataClient(char const *filename, DATA_CLIENT* data_client, int size, char* msg);
int write2FileErrorMessage(char const *filename, char const *msg);
int write2FileInfoMessage(char const *filename, char const *msg);
int write2FileInfoMessageInt(char const *filename, char const *msg, int val);

#endif //PRD_CLEAN_FILE_UTILS_H
