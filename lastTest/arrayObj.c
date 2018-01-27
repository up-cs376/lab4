#include "arrayObj.h"
#include "constants.h"


/* defines the int-array, myArray */
int myArray[] = { 3,VAL1,5,7,2,-4,VAL2};

/* defines the length of myArray */
const int myArrayLen = sizeof myArray / sizeof *myArray;
