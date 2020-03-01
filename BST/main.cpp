/*
Written by Giancarlo Calle
Main method used to test BST implementation.
*/

#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
  BST b;
  b.insertRec(4);
  b.insertRec(5);
  b.insertRec(2);
  b.insertRec(3);

  return 0;
}
