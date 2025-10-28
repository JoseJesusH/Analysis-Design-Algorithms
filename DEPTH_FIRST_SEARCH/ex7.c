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

void freeGraph(Graph G) {
    if (!G) return;
    for (int v=0; v<G->V; ++v) {
        link a = G->adj[v];
        while (a) { link t = a->next; free(a); a = t; }
    }
    free(G->adj);
    free(G);
}

Graph readAdjFile(const char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { perror("fopen"); exit(EXIT_FAILURE); }
    int V;
    if (fscanf(fp, "%d", &V) != 1) { fprintf(stderr,"bad file\n"); exit(EXIT_FAILURE); }
    Graph G = GRAPHinit(V);
    char line[10000];
    fgets(line, sizeof line, fp);
    for (int i=0;i<V;++i) {
        if (!fgets(line, sizeof line, fp)) line[0]='\0';
        char *p = line;
        while (*p==' '||*p=='\t') p++;
        int v; int read = 0;
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

typedef struct {
    vertex v;
    link cur; 
} Frame;

typedef struct {
    Frame *data;
    int top;
    int capacity;
} Stack;

Stack *stack_new(int cap) {
    Stack *s = malloc(sizeof *s);
    s->data = malloc(cap * sizeof(Frame));
    s->top = 0;
    s->capacity = cap;
    return s;
}
void stack_free(Stack *s) { free(s->data); free(s); }
void stack_push(Stack *s, Frame f) {
    if (s->top == s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, s->capacity * sizeof(Frame));
        if (!s->data) { perror("realloc"); exit(EXIT_FAILURE); }
    }
    s->data[s->top++] = f;
}
Frame stack_pop(Stack *s) { return s->data[--s->top]; }
Frame *stack_peek(Stack *s) { if (s->top==0) return NULL; return &s->data[s->top-1]; }
int stack_empty(Stack *s) { return s->top==0; }

void dfsR_iter(Graph G, vertex s, int pre[], int *cnt) {
    Stack *st = stack_new(16);
    pre[s] = (*cnt)++;
    Frame f = { s, G->adj[s] };
    stack_push(st, f);
    while (!stack_empty(st)) {
        Frame *top = stack_peek(st);
        vertex v = top->v;
        link cur = top->cur;
        while (cur && pre[cur->w] != -1) cur = cur->next;
        if (cur) {
            top->cur = cur->next;
            vertex w = cur->w;
            pre[w] = (*cnt)++;
            Frame nw = { w, G->adj[w] };
            stack_push(st, nw);
        } else {
            stack_pop(st);
        }
    }
    stack_free(st);
}

void GRAPHdfs_iter(Graph G) {
    int pre[MAXV];
    int cnt = 0;
    for (int v=0; v<G->V; ++v) pre[v] = -1;
    for (int v=0; v<G->V; ++v) {
        if (pre[v] == -1) dfsR_iter(G, v, pre, &cnt);
    }
    printf("pre[] =\n");
    for (int v=0; v<G->V; ++v) printf("%d ", pre[v]);
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s adjacency_file.txt\n", argv[0]);
        return 1;
    }
    Graph G = readAdjFile(argv[1]);
    GRAPHdfs_iter(G);
    freeGraph(G);
    return 0;
}
