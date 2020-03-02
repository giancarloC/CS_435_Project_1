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

  int n = 10000;

  int *arr = getRandomArray(n);

  //populates AVL and BST
  int i, num;
  for(i = 0; i < n; i++){
    num = arr[i];
    a.insertRec(num);
    b.insertRec(num);
  }

  a.printAVL();
  b.printBST();

  return 0;
}
