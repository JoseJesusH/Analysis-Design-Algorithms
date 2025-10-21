#include <stdio.h>

void insertionSortRecursive(int v[], int n) {
    if (n <= 1) return;              // caso base
    insertionSortRecursive(v, n-1);  // ordenar v[0..n-2]
    int last = v[n-1];
    int i = n-2;
    while (i >= 0 && v[i] > last) {  // desplazar
        v[i+1] = v[i];
        --i;
    }
    v[i+1] = last;                   // insertar
}

int main() {
    int a[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(a)/sizeof(a[0]);
    insertionSortRecursive(a, n);
    for (int i=0;i<n;i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

