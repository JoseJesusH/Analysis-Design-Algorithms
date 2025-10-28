#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 1000
typedef int vertex;

typedef struct node *link;
struct node { vertex w; link next; };

typedef struct graph {
    int V;
    int A;
    link *adj;
} *Graph;

static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof *a);
    if (!a) { perror("malloc"); exit(EXIT_FAILURE); }
    a->w = w; a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (!G) { perror("malloc"); exit(EXIT_FAILURE); }
    G->V = V; G->A = 0;
    G->adj = malloc(V * sizeof(link));
    if (!G->adj) { perror("malloc"); exit(EXIT_FAILURE); }
    for (int v=0; v<V; ++v) G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

static int cnt;
static int pre[MAXV];
static int indent = 0;

static void print_indent(void) {
    for (int i=0;i<indent;++i) putchar('.');
}

static void dfsR_trace(Graph G, vertex v) {
    pre[v] = cnt++;
    print_indent();
    printf("%d\n", v);
    indent++;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        print_indent();
        printf("%d-%d", v, w);
        if (pre[w] == -1) {
            printf(" dfsR(G,%d)\n", w);
            dfsR_trace(G, w);
        } else {
            printf("\n");
        }
    }
    indent--;
    print_indent();
    printf("%d\n", v);
}

void GRAPHdfs_trace(Graph G) {
    cnt = 0;
    for (int v = 0; v < G->V; ++v) pre[v] = -1;
    for (int v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            print_indent();
            printf("%d dfsR(G,%d)\n", v, v);
            dfsR_trace(G, v);
        }
    }
}

Graph readAdjFile(const char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { perror("fopen"); exit(EXIT_FAILURE); }
    int V;
    if (fscanf(fp, "%d", &V) != 1) { fprintf(stderr,"bad file\n"); exit(EXIT_FAILURE); }
    Graph G = GRAPHinit(V);
    char line[10000];
    fgets(line, sizeof line, fp); // consume eol
    for (int i=0;i<V;++i) {
        if (!fgets(line, sizeof line, fp)) line[0]='\0';
        char *p = line;
        while (*p==' '||*p=='\t') p++;
        int v;
        int read = 0;
        if (sscanf(p, "%d%n", &v, &read) != 1) continue;
        p += read;
        int w;
        while (sscanf(p, "%d%n", &w, &read) == 1) {
            GRAPHinsertArc(G, v, w);
            p += read;
        }
    }
    fclose(fp);
    return G;
}

void freeGraph(Graph G) {
    if (!G) return;
    for (int v=0; v<G->V; ++v) {
        link a = G->adj[v];
        while (a) { link t = a->next; free(a); a = t; }
    }
    free(G->adj);
    free(G);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s adjacency_file.txt\n", argv[0]);
        return 1;
    }
    Graph G = readAdjFile(argv[1]);
    GRAPHdfs_trace(G);
    freeGraph(G);
    return 0;
}
