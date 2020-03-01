/*
Written by Giancarlo Calle
Function implementations of array generators
*/

#include <stdio.h>
#include <stdlib.h>
#include <unordered_set>

//returns an array w/ random numbers of size n
int* getRandomArray(int n){
  //creates array to return
  int *arr = (int*)calloc(n, sizeof(int));

  //creates set to store unique random numbers and populates it
  std::unordered_set<int> uniqueNums;
  while(uniqueNums.size() != n){
    uniqueNums.insert(rand());
  }

  //populates array w/ random numbers
  int i;
  std::unordered_set<int>::iterator itr = uniqueNums.begin();
  for(i = 0; i < n; i++, itr++){
    arr[i] = *itr;
  }

  return arr;
}

//returns a sorted array [n, n-1, n-2, ... , 1]
int* getSortedArray(int n){
  //creates array to return
  int *arr = (int*)calloc(n, sizeof(int));

  //populates array
  int i;
  for(i = 0; i < n; i++){
    arr[i] = n-i;
  }

  return arr;
}

//prints array for testing
void printArray(int *arr, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(){
  //creates random and sorted array and prints
  int *random = getRandomArray(5);
  printArray(random, 5);
  int *sorted = getSortedArray(5);
  printArray(sorted, 5);
  return 0;
}
