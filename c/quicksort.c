#include "utils/utils.h"

void quicksort(int *A, int len) {
  if (len < 2)
    return;

  int pivot = A[len / 2];

  int i, j;
  for (i = 0, j = len - 1;; i++, j--) {
    while (A[i] < pivot)
      i++;
    while (A[j] > pivot)
      j--;

    if (i >= j)
      break;

    int tmp_i = A[i];
    A[i] = A[j];
    A[j] = tmp_i;
  }

  quicksort(A, i);
  quicksort(A + i, len - i);
}

int main() {
  int arr[8] = {5, 3, 7, 8, 23, 1, 6, -12};

  print_array(arr, 8);
  printf("\n");
  quicksort(arr, 8);
  print_array(arr, 8);
  printf("\n");
}
