//
// Created by Ayoub IDEL  on 20/09/2018.
//

#include "floyd_warshall.h"

void print_matrix(int graph[][VERTICES]) {
    printf("\n\nThe last matrix is : \n\n");
    for(int i=0 ; i<VERTICES ; i++) {
        for(int j=0 ; j<VERTICES ; j++) {
            if (graph[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** floyd_warshall_algorithm(int graph[][VERTICES]) {
    int distance[VERTICES][VERTICES];

    for(int i=0 ; i<VERTICES ; i++) {
        for(int j=0 ; j<VERTICES ; j++) {
            distance[i][j] = graph[i][j];
        }
    }

    int k;
    for(k=0 ; k<VERTICES ; k++) {
        int i;
        for(i=0 ; i<VERTICES ; i++) {
            int j;
            for(j=0 ; j<VERTICES ; j++) {
                if(distance[i][j] > (distance[i][k] + distance[k][j]))
                    distance[i][j] = distance[i][k] + distance[k][j];
            }
        }
    }

    return distance;
}