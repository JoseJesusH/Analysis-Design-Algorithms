#include <stdio.h>
#include <string.h>

void insertionSortStrings(char* arr[], int n) {
    for (int j = 1; j < n; ++j) {
        char* key = arr[j];
        int i = j-1;
        while (i >= 0 && strcmp(arr[i], key) > 0) {
            arr[i+1] = arr[i];
            --i;
        }
        arr[i+1] = key;
    }
}

int main() {
    char* a[] = {"pera", "manzana", "banana", "uva"};
    int n = sizeof(a)/sizeof(a[0]);
    insertionSortStrings(a, n);
    for (int i=0;i<n;i++) printf("%s\n", a[i]);
}

