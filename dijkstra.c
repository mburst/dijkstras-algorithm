#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 1000

struct Edge {
    int to;
    int cost;
};

struct Node {
    int id;
    int dist;
};

int cmp(const void *a, const void *b) {
    const struct Node *node_a = (const struct Node *)a;
    const struct Node *node_b = (const struct Node *)b;
    return node_b->dist - node_a->dist;
}

void dijkstra(struct Edge **nodes, int num_nodes, int start, int *dist) {
    int i, j;
    struct Node pq[MAX_NODES];
    int pq_size = 0;

    for (i = 0; i < num_nodes; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    pq[pq_size++] = (struct Node){ start, 0 };
    qsort(pq, pq_size, sizeof(struct Node), cmp);

    while (pq_size > 0) {
        struct Node node = pq[--pq_size];

        for (j = 0; j < num_nodes; j++) {
            if (nodes[node.id][j].to < 0) break;

            int new_dist = dist[node.id] + nodes[node.id][j].cost;
            if (new_dist < dist[nodes[node.id][j].to]) {
                dist[nodes[node.id][j].to] = new_dist;
                pq[pq_size++] = (struct Node){ nodes[node.id][j].to, new_dist };
                qsort(pq, pq_size, sizeof(struct Node), cmp);
            }
        }
    }
}

int main() {
    int num_nodes = 4;
    struct Edge **nodes = (struct Edge **)malloc(num_nodes * sizeof(struct Edge *));
    int i, j;

    for (i = 0; i < num_nodes; i++) {
        nodes[i] = (struct Edge *)malloc(num_nodes * sizeof(struct Edge));
        for (j = 0; j < num_nodes; j++) {
            nodes[i][j].to = -1;
            nodes[i][j].cost = -1;
        }
    }

    nodes[0][0].to = 1; nodes[0][0].cost = 4;
    nodes[0][1].to = 2; nodes[0][1].cost = 2;
    nodes[1][0].to = 3; nodes[1][0].cost = 1;
    nodes[2][0].to = 1; nodes[2][0].cost = 1;
    nodes[2][1].to = 3; nodes[2][1].cost = 5;

    int *dist = (int *)malloc(num_nodes * sizeof(int));
    dijkstra(nodes, num_nodes, 0, dist);

    for (i = 0; i < num_nodes; i++) {
        printf("%d ", dist[i]);
    }
    printf("\n");

    for (i = 0; i < num_nodes; i++) {
        free(nodes[i]);
    }
    free(nodes);
    free(dist);

    return 0;
}