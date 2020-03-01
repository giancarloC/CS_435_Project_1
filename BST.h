/*
Written by Giancarlo Calle
Binary Search Tree Class
*/

#ifndef BST_H
#define BST_H
#include <stdio.h>
#include "Node.h"

class BST{
  public:
    Node *root;

    //recursive methods
    void insertRec(int val);
    void deleteRec(int val);
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

  private:
    //general helper methods
    Node* createNode(int val);
    void addNodeLeft(Node *parentNode, int val);
    void addNodeRight(Node *parentNode, int val);

    //recursive helpers
    void printHelper(Node *node);
    void insertRecHelper(Node *curr, int val);
    Node* rightMostNode(Node *node);
    Node* leftMostNode(Node *node);
    Node* biggerParent(Node *node, int val);
    Node* smallerParent(Node *node, int val);
    Node* findNode(Node *curr, int val);
    void deleteNode(Node *node);

    //iterative helper methods
    Node* rightMostNodeIter(Node *node);
    Node* leftMostNodeIter(Node *node);
    Node* biggerParentIter(Node *node, int val);
    Node* smallerParentIter(Node *node, int val);
    Node* findNodeIter(Node *curr, int val);

};

#endif
