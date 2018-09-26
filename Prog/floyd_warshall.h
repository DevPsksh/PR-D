//
// Created by Ayoub IDEL  on 20/09/2018.
//

#ifndef PROG_FLOYD_WARSHALL_H
#define PROG_FLOYD_WARSHALL_H

#include <stdio.h>

#define VERTICES 4
#define INF 99999

/**
 * Find shortest path between all pairs of vertices
 * @param graph matrix (2D array)
 * @return shortest path matrix
 */
int** floyd_warshall_algorithm(int graph[][VERTICES]);

/**
 * Print matrix (2D array)
 * @param graph matrix
 */
void print_matrix(int graph[][VERTICES]);

#endif //PROG_FLOYD_WARSHALL_H

