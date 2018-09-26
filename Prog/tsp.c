//
// Created by Ayoub IDEL  on 26/09/2018.
//

#include "tsp.h"

static void swap(unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}


static void traveling_salesman_recursive(const unsigned int **mat_distances, unsigned int order,
                                         unsigned int *best_tour, unsigned int *best_tour_cost, unsigned int *partial_tour,
                                         unsigned int *partial_tour_cost, unsigned int level)
{
    if (level == order - 1) {
        /* Add last two edges to complete the tour */
        unsigned int tour_cost = *partial_tour_cost
                                 + mat_distances[partial_tour[order - 2]][partial_tour[order - 1]]
                                 + mat_distances[partial_tour[order - 1]][0];
        if (*best_tour_cost == 0 || tour_cost < *best_tour_cost) {
            memcpy(best_tour, partial_tour, order * sizeof(unsigned int));
            *best_tour_cost = tour_cost;
        }
    }
    else {

        for (int i = level; i < order; i++) {
            if (*best_tour_cost == 0
                || *partial_tour_cost + mat_distances[partial_tour[level - 1]][partial_tour[i]]
                   < *best_tour_cost)
            {
                /* Next permutation */
                swap(&partial_tour[level], &partial_tour[i]);
                unsigned int cost = mat_distances[partial_tour[level - 1]][partial_tour[level]];
                *partial_tour_cost += cost;
                traveling_salesman_recursive(mat_distances, order, best_tour, best_tour_cost,
                                             partial_tour, partial_tour_cost, level + 1);
                *partial_tour_cost -= cost;
                swap(&partial_tour[level], &partial_tour[i]);
            }
        }
    }
}

unsigned int traveling_salesman(const unsigned int **mat_distances, unsigned int num_vertices,
                                unsigned int **best_tour)
{

    unsigned int best_tour_cost = 0;
    unsigned int partial_tour_cost = 0;
    unsigned int *partial_tour = malloc(num_vertices * sizeof(unsigned int));
    *best_tour = malloc(num_vertices * sizeof(unsigned int));
    if (partial_tour == NULL || *best_tour == NULL) {
        free(partial_tour);
        free(*best_tour);
        *best_tour = NULL;
        return 0;
    }
    for (int i = 0; i < num_vertices; i++) {
        partial_tour[i] = i;
    }
    traveling_salesman_recursive(mat_distances, num_vertices, *best_tour, &best_tour_cost, partial_tour,
                                 &partial_tour_cost, 1);
    free(partial_tour);
    return best_tour_cost;
}