#include "bibl1.h"
#include <stdio.h>
#include <stdlib.h>

int sumuj(int *tab, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += tab[i];
  }
  return sum;
}
double srednia(int *tab, int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += tab[i];
  }
  return sum / n;
}
/*napisz biblioteke ladowana dynamicznie przez program zawierajaca funkcje:

1) zliczajaca sume n elementow tablicy tab:
int sumuj(int *tab, int n);

2) liczaca srednia n elementow tablicy tab
double srednia(int *tab, int n);

*/
