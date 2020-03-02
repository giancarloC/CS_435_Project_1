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

  int *arr = getRandomArray(n);

  //populates AVL and BST
  int i, num;
  int levelAVL = 0;
  int levelBST = 0;
  for(i = 0; i < n; i++){
    num = arr[i];
    levelAVL = levelAVL + a.insertIter(num);
    levelBST = levelBST + b.insertIter(num);
  }

  printf("In AVL, %d levels were traversed.\n", levelAVL);
  printf("In BST, %d levels were traversed.\n", levelBST);

  return 0;
}
