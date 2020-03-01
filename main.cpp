/*
Written by Giancarlo Calle
Main method used to test AVL implementation.
*/

#include "AVL.h"
#include "BST.h"
#include "ArrayCreators.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  //creates AVL and BST
  AVL a;
  BST b;

  int n = 10;

  int *arr = (int*)calloc(n, sizeof(int));
  arr[0] = 0;
  arr[10] = 2;
  printf("%d\n", arr[1]);
  /*
  int* array = getSortedArray(n);

  //populates AVL and BST
  int i, num;
  for(i = 0; i < n; i++){
    num = array[i];
    a.insertRec(num);
    b.insertRec(num);
  }

  a.printAVL();
  b.printBST();*/

  return 0;
}
