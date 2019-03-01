//
// Created by Ayoub IDEL  on 25/02/2019.
//

#ifndef PRD_CLEAN_QUEUE_H
#define PRD_CLEAN_QUEUE_H

#include <stdlib.h>
#include <stdio.h>

#include "matrix_utils.h"


/**
 * a link in the queue, holds the info and point to the next Node
 *
 * DATA OF THE SERVER
 *
 */
typedef struct {
    int info;
    int *elements;
    MATRIX *matrix;
} DATA;


typedef struct Node_t {
    DATA data;
    struct Node_t *prev;
} NODE;


/**
 * the HEAD of the Queue, hold the amount of node's that are in the queue
 */
typedef struct Queue {
    NODE *head;
    NODE *tail;
    int size;
    int limit;
} Queue;


Queue *ConstructQueue(int limit);
void DestructQueue(Queue *queue);
int Enqueue(Queue *pQueue, NODE *item);
NODE *Dequeue(Queue *pQueue);
int isEmpty(Queue* pQueue);



#endif //PRD_CLEAN_QUEUE_H
