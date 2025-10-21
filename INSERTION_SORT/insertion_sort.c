for (int j = 1; j < n; ++j) {
   int x = v[j];
   for (int i = j-1; i >= 0 && v[i] > x; --i) {
      v[i+1] = v[i];
      v[i] = x;
   }
}

