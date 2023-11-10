#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 100

int parent[MAX_VERTICES];

void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

void set_union(int a, int b) {
    int root1 = set_find(a);
    int root2 = set_find(b);

    if (root1 != root2) {
        parent[root1] = root2;

        printf("Union: %d <- %d\n", root2, root1);
        for (int i = 0; i < 7; i++) {
            printf("%d ", parent[i]);
        }
        printf("\n\n");
    }
}

struct Edge {
    int start, end, weight;
};

typedef struct graphtype {
    int n;
    int nvertex;
    struct Edge edges[2 * MAX_VERTICES];
} graphtype;

void graph_init(graphtype* g) {
    g->n = g->nvertex = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

void insert_edge(graphtype* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}

int compare(const void* a, const void* b) {
    const struct Edge* x = (const struct Edge*)a;
    const struct Edge* y = (const struct Edge*)b;
    return (x->weight - y->weight);
}

void kruscal(graphtype* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    set_init(g->nvertex);
    qsort(g->edges, g->n, sizeof(struct Edge), compare);
    printf("크루스탈 최소 신장 트리\n");

    int i = 0;
    while (edge_accepted < (g->nvertex - 1)) {
        e = g->edges[i];
        uset = set_find(e.start);
        vset = set_find(e.end);

        if (uset != vset) {
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

int main(void) {
    graphtype* g;
    g = (graphtype*)malloc(sizeof(graphtype));
    if (g == NULL) {
        printf("Graph allocation error\n");
        return -1;
    }
    graph_init(g);
    int n = 7;
    int matrix[7][7] = {
        {0, 29, INF, INF, INF, 10, INF},
        {29, 0, 16, INF, INF, INF, 15},
        {INF, 16, 0, 12, INF, INF, INF},
        {INF, INF, 12, 0, 22, INF, 18},
        {INF, INF, INF, 22, 0, 27, 25},
        {10, INF, INF, INF, 27, 0, INF},
        {INF, 15, INF, 18, 25, INF, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != INF) {
                insert_edge(g, i, j, matrix[i][j]);
            }
        }
    }

    g->nvertex = n;
    kruscal(g);
    free(g);
    return 0;
}
