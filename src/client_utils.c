//
// Created by Ayoub IDEL  on 25/02/2019.
//


#include "client_utils.h"



/**
 * Puts in my_array the array of all DATA_CLIENTs with specific
 * elements, distances and total cost
 * @param all_leaves
 * @param mtx_distances
 * @param my_array
 */
void getArrayOfDataClients(MATRIX *all_leaves, MATRIX *mtx_distances, DATA_CLIENT **my_array) {

    *my_array = malloc(all_leaves->rows * sizeof(**my_array));

    for (int i = 0; i < all_leaves->rows; i++) {
        (*my_array)[i].elements = copy1DArray(getRow(all_leaves, i + 1), all_leaves->cols);
        (*my_array)[i].distances = copy1DArray(getArrayOfDistances(mtx_distances, (*my_array)[i].elements),
                                               all_leaves->cols - 1);
        (*my_array)[i].total_cost = getTotalCost((*my_array)[i].distances, all_leaves->cols - 1);

    }
}

/**
 * Gives the minimum of DATA_CLIENT in a DATA_CLIENTS array (lowest cost)
 * @param all_data_clients
 * @param num_elements
 * @return
 */
DATA_CLIENT *getMinimumOfDataClients(DATA_CLIENT **all_data_clients, int num_elements, int SIZE) {

    DATA_CLIENT *result = malloc(sizeof(DATA_CLIENT));

    result->total_cost = (*all_data_clients)[0].total_cost;
    result->elements = copy1DArray((*all_data_clients)[0].elements, SIZE);
    result->distances = copy1DArray((*all_data_clients)[0].distances, SIZE - 1);

    for (int i = 1; i < num_elements; i++) {

        if ((*all_data_clients)[i].total_cost < result->total_cost) {
            result->total_cost = (*all_data_clients)[i].total_cost;
            result->elements = copy1DArray((*all_data_clients)[i].elements, SIZE);
            result->distances = copy1DArray((*all_data_clients)[i].distances, SIZE - 1);
        }

    }

    return result;
}

/**
 * Deletes DATA_CLIENT
 * @param data_client
 * @return
 */
int deleteDataClient(DATA_CLIENT *data_client) {
    if (!data_client)
        return -1;

    assert (data_client->distances);
    free(data_client->distances);

    assert (data_client->elements);
    free(data_client->elements);

    free(data_client);

    return 0;
}

/**
 *
 * @param my_array
 * @param size
 */
void createDataClientArray(DATA_CLIENT **my_array, int size) {

    *my_array = malloc(size * sizeof(**my_array));

}

/**
 *
 * @param my_array
 * @param data_client
 * @param SIZE
 * @param pos
 */
void addDataClient2Array(DATA_CLIENT **my_array, DATA_CLIENT* data_client,int SIZE, int pos) {

    (*my_array)[pos].elements = copy1DArray(data_client->elements, SIZE);
    (*my_array)[pos].distances = copy1DArray(data_client->distances, SIZE);
    (*my_array)[pos].total_cost = data_client->total_cost;


}

void printDataClient(DATA_CLIENT* data_client, int size) {
    printf("DATA_CLIENT cost = %d\n", data_client->total_cost);
    printf("Elements : ");
    show1DArray(data_client->elements, size);
    printf("Distances : ");
    show1DArray(data_client->distances, size-1);
}






///////TEST OF DATA CLIENTS

/*
    int SIZE = 4;
    int array[] = {1, 2, 3, 4};

    MATRIX *matrix_distances = newMatrix(4, 4);
    MATRIX *matrix_leaves = newMatrix(6, 4);

    int count = 0;
    for (int i = 0; i < matrix_distances->rows; ++i) {
        for (int j = 0; j < matrix_distances->cols; ++j) {
            setElement(matrix_distances, i + 1, j + 1, ++count);
        }
    }

    setElement(matrix_leaves, 1, 1, 1);
    setElement(matrix_leaves, 1, 2, 2);
    setElement(matrix_leaves, 1, 3, 3);
    setElement(matrix_leaves, 1, 4, 4);

    setElement(matrix_leaves, 2, 1, 2);
    setElement(matrix_leaves, 2, 2, 1);
    setElement(matrix_leaves, 2, 3, 3);
    setElement(matrix_leaves, 2, 4, 4);

    setElement(matrix_leaves, 3, 1, 1);
    setElement(matrix_leaves, 3, 2, 2);
    setElement(matrix_leaves, 3, 3, 4);
    setElement(matrix_leaves, 3, 4, 3);

    setElement(matrix_leaves, 4, 1, 1);
    setElement(matrix_leaves, 4, 2, 4);
    setElement(matrix_leaves, 4, 3, 3);
    setElement(matrix_leaves, 4, 4, 2);

    setElement(matrix_leaves, 5, 1, 4);
    setElement(matrix_leaves, 5, 2, 3);
    setElement(matrix_leaves, 5, 3, 1);
    setElement(matrix_leaves, 5, 4, 2);

    setElement(matrix_leaves, 6, 1, 4);
    setElement(matrix_leaves, 6, 2, 2);
    setElement(matrix_leaves, 6, 3, 3);
    setElement(matrix_leaves, 6, 4, 1);

    printMatrix(matrix_distances);

    printf("\n---------------\n");

    printMatrix(matrix_leaves);

    printf("\n---------------\n");

    //DATA_CLIENT* test = getArrayOfDataClients(matrix_leaves, matrix_distances);
    DATA_CLIENT* test = NULL;
    getArrayOfDataClients(matrix_leaves, matrix_distances, &test);

    for (int k = 0; k < matrix_leaves->rows; ++k) {
        printf("struct %d  ->  cost = %d\n", k, test[k].total_cost);
        show1DArray(test[k].elements, SIZE);
        show1DArray(test[k].distances, SIZE-1);
    }

    printf("\n==========================\n");

    DATA_CLIENT* min = getMinimumOfDataClients(&test, matrix_leaves->rows, SIZE);



    printf("struct with lowest cost = %d\n", min->total_cost);
    show1DArray(min->elements, SIZE);
    show1DArray(min->distances, SIZE-1);


    free(test);


    return 0;*/