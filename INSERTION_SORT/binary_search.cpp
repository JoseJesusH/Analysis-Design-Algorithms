#include <iostream>
#include <vector>
using namespace std;

// devuelve el índice donde insertar key en v[0..high-1] (inclusivo)
int binarySearchInsert(const vector<int>& v, int low, int high, int key) {
    // buscamos el primer índice i en [low..high] tal que v[i] > key
    while (low <= high) {
        int mid = low + (high - low)/2;
        if (v[mid] <= key) low = mid + 1;
        else high = mid - 1;
    }
    return low; // posición de inserción
}

void insertionSortBinary(vector<int>& v) {
    int n = v.size();
    for (int j = 1; j < n; ++j) {
        int key = v[j];
        int pos = binarySearchInsert(v, 0, j-1, key);
        // desplazar v[pos..j-1] a la derecha
        for (int k = j-1; k >= pos; --k) v[k+1] = v[k];
        v[pos] = key;
    }
}

int main(){
    vector<int> a = {5,2,9,1,5,6};
    insertionSortBinary(a);
    for (int x: a) cout << x << ' ';
    cout << '\n';
}

