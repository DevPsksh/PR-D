//
// Created by Ayoub IDEL  on 25/02/2019.
//

#ifndef PRD_CLEAN_CLIENT_UTILS_H
#define PRD_CLEAN_CLIENT_UTILS_H

#include "matrix_utils.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_utils.h"
#include "general_utils.h"



/**
 * Client Side
 */
typedef struct {
    int total_cost;
    int *elements;
    int *distances;
} DATA_CLIENT;


DATA_CLIENT *getMinimumOfDataClients(DATA_CLIENT **all_data_clients, int num_elements, int SIZE);
void getArrayOfDataClients(MATRIX *all_leaves, MATRIX *mtx_distances, DATA_CLIENT **my_array);
int deleteDataClient(DATA_CLIENT *data_client);

void createDataClientArray(DATA_CLIENT **my_array, int size);
void addDataClient2Array(DATA_CLIENT **my_array, DATA_CLIENT* data_client, int SIZE, int pos);
void printDataClient(DATA_CLIENT* data_client, int size);



#endif //PRD_CLEAN_CLIENT_UTILS_H
