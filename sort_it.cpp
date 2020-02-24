/*
Written by Giancarlo Calle
Sorting algorithm for BST
*/

#include <vector>
#include <stdio.h>
#include "BST.h"
using namespace std;

//sorting method using BST
vector<int> sort(vector<int> vec){
  //populates binary search tree w/ elements in vector
  BST b;
  for(int num : vec){
    b.insertRec(num);
  }

  //creates vector to return
  int size = vec.size();
  vector<int> ret;
  Node *curr = b.findMinRec();

  //continues to get next node while it adds to vector
  int i;
  for(i = 0; i < size; i++){
    ret.push_back(curr->data);
    curr = b.findNextRec(curr);
  }

  return ret;
}

//prints vector
void printVector(vector<int> vec){
  for(int i : vec){
    printf("%d ", i);
  }
  printf("\n");
}

//tests code
int main(){
  vector<int> sample = {5, 2, 6, 8, 3};
  vector<int> ordered = sort(sample);
  printVector(ordered);
  return 0;
}
