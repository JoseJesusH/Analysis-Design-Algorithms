#include <stdio.h>
#include <stdlib.h>

#define vertex int

typedef struct node *link;
struct node {
    vertex w;
    link next;
};

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof *a);
    if (!a) { perror("malloc"); exit(EXIT_FAILURE); }
    a->w = w;
    a->next = next;
    return a;
}

typedef struct graph {
    int V;
    int A;
    link *adj;   /* vector de listas */
} *Graph;

/* GRAPHinit: crea grafo con V vértices y 0 arcos */
Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (!G) { perror("malloc"); exit(EXIT_FAILURE); }
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    if (!G->adj) { perror("malloc"); exit(EXIT_FAILURE); }
    for (vertex v = 0; v < V; ++v) G->adj[v] = NULL;
    return G;
}

/* GRAPHinsertArc: inserta arco v->w si no existe */
void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

/* EJERCICIO 2: outdeg e indeg */

/* Cuenta arcos salientes de v: Θ(outdeg(v)) */
int GRAPHoutdeg(Graph G, vertex v) {
    int cnt = 0;
    for (link a = G->adj[v]; a != NULL; a = a->next) cnt++;
    return cnt;
}

/* Cuenta arcos entrantes a v: Θ(V + A) */
int GRAPHindeg(Graph G, vertex v) {
    int cnt = 0;
    for (vertex u = 0; u < G->V; ++u) {
        for (link a = G->adj[u]; a != NULL; a = a->next) {
            if (a->w == v) cnt++;
        }
    }
    return cnt;
}

/* EJERCICIO 3: decidir si v y w son adyacentes (v->w) */
/* Tiempo: Θ(outdeg(v)) */
int GRAPHadjacent(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return 1;
    return 0;
}

/* EJERCICIO 4: imprimir vecinos de cada vértice */
/* Tiempo total: Θ(V + A) */
void GRAPHshow(Graph G) {
    for (vertex v = 0; v < G->V; ++v) {
        printf("%d:", v);
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            printf(" %d", a->w);
        }
        printf("\n");
    }
}

/* EJERCICIO 5: destruir grafo y liberar memoria */
/* Tiempo: Θ(V + A) */
void GRAPHdestroy(Graph G) {
    if (!G) return;
    for (vertex v = 0; v < G->V; ++v) {
        link a = G->adj[v];
        while (a) {
            link next = a->next;
            free(a);
            a = next;
        }
    }
    free(G->adj);
    free(G);
}

/* ---------- Programa de prueba ---------- */
int main(void) {
    /* Construimos grafo de ejemplo
       arcos: 0-1, 0-5, 1-0, 1-5, 2-4, 3-1, 5-3 */
    Graph G = GRAPHinit(6);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 5);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 5);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 5, 3);

    printf("GRAPHshow() ->\n");
    GRAPHshow(G);
    printf("\n");

    vertex v = 0;
    printf("Is vertex %d isolated? (has outgoing) -> %s\n", v, (G->adj[v] == NULL) ? "YES" : "NO");

    printf("outdeg(1) = %d\n", GRAPHoutdeg(G, 1));
    printf("indeg(1) = %d\n", GRAPHindeg(G, 1));

    printf("Are 0 and 5 adjacent? (0->5) -> %s\n", GRAPHadjacent(G, 0, 5) ? "YES" : "NO");
    printf("Are 4 and 2 adjacent? (4->2) -> %s\n", GRAPHadjacent(G, 4, 2) ? "YES" : "NO");

    /* limpiar */
    GRAPHdestroy(G);

    return 0;
}
