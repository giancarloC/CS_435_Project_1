/*
Written by Giancarlo Calle
Binary Search Tree Class
*/

#include <stdio.h>

struct Node{
  int data;
  Node *parent;
  Node *left;
  Node *right;
};

class BST{
  public:
    Node *root;

    //recursive methods
    void insertRec(int val);
    void deleteRec(int val);
    void deleteNode(Node *node); //deleteRec helper
    Node* findNextRec(Node *node);
    Node* findPrevRec(Node *node);
    Node* findMinRec();
    Node* findMaxRec();

    //iterative methods
    void insertIter(int val);
    void deleteIter(int val);
    Node* findNextIter(Node *node);
    Node* findPrevIter(Node *node);
    Node* findMinIter();
    Node* findMaxIter();

    //constructor
    BST(){
      root = NULL;
    }

    //other methods
    void printBST();
    void printRoot(){
      printf("Root is %d\n", root->data);
    };
};
