#include <stdio.h>
#include "general_utils.h"
#include "file_utils.h"
#include "client_utils.h"
#include "queue.h"


int main() {

    char* filename = "log.log";

    int SIZE = 4;
    int fixed = 0;
    int array[] = {1, 2, 3, 4};

    MATRIX *matrix_distances = loadFileIntoMatrix("testfile.csv", SIZE);
    printf("matrice des distances : \n");
    printMatrix(matrix_distances);
    write2FileMatrix(filename, matrix_distances, "Matrix of distances");

    //Generate next level
    MATRIX *matrix_next_level = generateNextLevel(array, fixed, SIZE);
    printf("matrice next level : \n");
    printMatrix(matrix_next_level);
    write2FileMatrix(filename, matrix_next_level, "Matrix of next level");


    //Create a queue
    Queue *queue = ConstructQueue(SIZE);

    //Add each node of the first next level to the queue
    NODE *node;
    for (int i = 0; i < matrix_next_level->rows; ++i) {
        node = (NODE *) malloc(sizeof(NODE));
        node->data.info = i;
        node->data.elements = getRow(matrix_next_level, i + 1);
        node->data.matrix = copyMatrix(matrix_distances);
        Enqueue(queue, node);
    }

    // We Delete the matrix of distances & matrix of next level
    deleteMatrix(matrix_distances);
    write2FileInfoMessage(filename, "Matrix of distances successfully deleted !");
    deleteMatrix(matrix_next_level);
    write2FileInfoMessage(filename, "Matrix of next level successfully deleted !");


    printf("--------- \n");
    printf("Queues : \n");
    printf("--------- \n");


    //Define DATA_CLIENT of mins Array
    DATA_CLIENT* mins = NULL;
    createDataClientArray(&mins, SIZE);
    write2FileInfoMessage(filename, "Array of DATA_CLIENTs successfully created !");

    int count = 0;

    //We dequeue nodes to send them to the clients
    while (!isEmpty(queue)) {

        node = Dequeue(queue);

        printf("===================\n");
        printf("===================\n");
        printf("\nDequeued: %d\n", node->data.info);
        printMatrix(node->data.matrix);
        show1DArray(node->data.elements, SIZE);

        //
        //Client Side
        //
        printf("==========================\n");
        MATRIX* mtx_leaves_actual_node = generateLeaves(node->data.elements, SIZE, fixed+1);
        printMatrix(mtx_leaves_actual_node);
        printf("==========================\n");
        write2FileInfoMessageInt(filename, "This is node number :", count);
        write2FileMatrix(filename, mtx_leaves_actual_node, "All leaves of actual node");

        DATA_CLIENT* test = NULL;
        getArrayOfDataClients(mtx_leaves_actual_node, node->data.matrix, &test);



        for (int k = 0; k < mtx_leaves_actual_node->rows; ++k) {
            printf("struct %d  ->  cost = %d\n", k, test[k].total_cost);
            show1DArray(test[k].elements, SIZE);
            show1DArray(test[k].distances, SIZE-1);
        }

        printf("===========Print Min DATA_CLIENT===============\n");
        DATA_CLIENT* min = getMinimumOfDataClients(&test, mtx_leaves_actual_node->rows, SIZE);

        printf("struct number : %d\n", count);
        printDataClient(min, SIZE);
        write2FileDataClient(filename, min, SIZE, "local min DATA_CLIENT");


        // Add data_client array & store on it all the mins
        addDataClient2Array(&mins, min,SIZE, count++);


        deleteDataClient(min);
        deleteMatrix(mtx_leaves_actual_node);
        deleteDataClient(test);
        free(node);
    }
    printf("count = %d \n", count);

    printf("==========================\n");
    printf("==========================\n");
    printf("==========================\n");

    //print all the elements of mins data_client array

    for (int i = 0; i < count; ++i) {
        printf("struct %d  ->  cost = %d\n", i, mins[i].total_cost);
        show1DArray(mins[i].elements, count);
        show1DArray(mins[i].distances, count-1);
    }

    //Get the shortest data client of mins data_client array
    DATA_CLIENT* shortest_data_client = getMinimumOfDataClients(&mins, count, SIZE);


    // print to screen the shortest data_client
    printf("\n\n\n\n");
    printf("======================================\n");
    printf("===========FINAL RESULT===============\n");
    printf("======================================\n");
    printDataClient(shortest_data_client, count);
    printf("\n\n\n\n");

    write2FileDataClient(filename, shortest_data_client, SIZE, "global min DATA_CLIENT");


    deleteDataClient(mins);
    deleteDataClient(shortest_data_client);


    return 0;



}