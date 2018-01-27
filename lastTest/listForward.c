/* #includes */
#include "stdio.h"
#include "listForward.h"
#include "arrayObj.h"

/* function to list array elements forwards */
void listForward(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

/* main function for testing */
int main(void) {
  listForward(myArray, myArrayLen);
  return 0;
}

