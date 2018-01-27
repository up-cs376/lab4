/* #includes */
#include "stdio.h"
#include "listBackward.h"
#include "arrayObj.h"

/* function to list array elements backwards */
void listBackward(int arr[], int size) {
  int i;
  for (i = size-1; i >= 0; i--) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

/* main function for testing */
int main(void) {
  listBackward(myArray, myArrayLen);
  return 0;
}

