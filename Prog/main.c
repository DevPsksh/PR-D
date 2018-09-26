#include <stdio.h>
#include <stdlib.h>
#include "tsp.h"
#include "floyd_warshall.h"

int main() {

    int graph[VERTICES][VERTICES] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 13, 15, 16}
    };

    int distance[VERTICES][VERTICES];
    memcpy(distance, floyd_warshall_algorithm(graph), VERTICES * VERTICES * sizeof(int));

    print_matrix(distance);

    const size_t order = VERTICES;

    const unsigned int *mat_distances[] = {distance[0], distance[1], distance[2], distance[3]};

    unsigned int *best_tour;
    unsigned int cost = traveling_salesman(mat_distances, order, &best_tour);

    printf("Best tour cost: %u\n", cost);

    printf("Vertices:\t");
    for (int i = 0; i < order; i++) {
        printf("%u", best_tour[i]);
        printf("-->");
    }
    printf("0\n");

    printf("Edge weights:\t");
    for (int i = 0; i < order - 1; i++) {
        printf("%u\t", mat_distances[best_tour[i]][best_tour[i + 1]]);
    }
    printf("%u\n\n", mat_distances[best_tour[order - 1]][0]);

    free(best_tour);

    return 0;
}