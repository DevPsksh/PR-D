//
// Created by Ayoub IDEL  on 26/09/2018.
//

#ifndef PROG_TSP_H
#define PROG_TSP_H

#include <stdlib.h>
#include <string.h>

/**
 * Swap two unsigned integers
 * @author Ayoub IDEL
 * @param a value1
 * @param b value2
 */
static void swap(unsigned int *a, unsigned int *b);

/**
 * Search the permutation of vertices by fixing the start of each tour at vertex 0
 * @param mat_distances
 * @param num_vertices
 * @param best_tour
 * @param best_tour_cost
 * @param partial_tour
 * @param partial_tour_cost
 * @param level
 */
static void traveling_salesman_recursive(const unsigned int **mat_distances, unsigned int num_vertices,
                                         unsigned int *best_tour, unsigned int *best_tour_cost, unsigned int *partial_tour,
                                         unsigned int *partial_tour_cost, unsigned int level);

/**
 * Calculate best tour cost and give the best path
 * @param mat_distances matrix of distances
 * @param num_vertices number of vertices
 * @param best_tour pointer to an array of unsigned integers userd as an output parameter
 * @return the vertices of the best tour in order
 */
unsigned int traveling_salesman(const unsigned int **mat_distances, unsigned int num_vertices,
                                unsigned int **best_tour);


#endif //PROG_TSP_H
