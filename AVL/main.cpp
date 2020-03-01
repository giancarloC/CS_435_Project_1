/*
Written by Giancarlo Calle
Main method used to test AVL implementation.
*/

#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  AVL a;
  a.insertIter(5);
  a.insertIter(6);
  a.insertRec(7);
  a.insertRec(4);
  a.deleteIter(7);
  a.printAVL();
  printf("root:%d\n", a.root->data);

  return 0;
}
