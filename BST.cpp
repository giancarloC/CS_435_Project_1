/*
Written by Giancarlo Calle
Binary Search Tree Method Implementations
*/

#include "BST.h"
#include <stdlib.h>
#include <stdio.h>
#define FALSE 0
#define TRUE 1

//helper function for printBST()
void BST::printHelper(Node *node){
  if(node == NULL)
    return;
  printHelper(node->left);
  printf("%d ", node->data);
  printHelper(node->right);
}

//prints elements in order
void BST::printBST(){
  printHelper(root);
  printf("\n");
}

//creates node to be added
Node* BST::createNode(int val){
  Node *node = (Node*)malloc(sizeof(Node));
  node->data = val;
  return node;
}

//adds node as a left child
void BST::addNodeLeft(Node *parentNode, int val){
  //adds node to left child and adds parent pointer
  Node *node = createNode(val);
  parentNode->left = node;
  node->parent = parentNode;
}

//adds node as a right child
void BST::addNodeRight(Node *parentNode, int val){
  //adds node to left child and adds parent pointer
  Node *node = createNode(val);
  parentNode->right = node;
  node->parent = parentNode;
}

//recursive helper function for insertRec()
void BST::insertRecHelper(Node *curr, int val){
  int valCurr = curr->data;
  if(val > valCurr){
    if(curr->right == NULL)
      addNodeRight(curr, val);
    else
      insertRecHelper(curr->right, val);
  }
  else{
    if(curr->left == NULL)
      addNodeLeft(curr, val);
    else
      insertRecHelper(curr->left, val);
  }
}

//inserts value onto BST
void BST::insertRec(int val){
  //checks if tree is empty (edge case)
  if(root == NULL){
    root = createNode(val);
    return;
  }

  //recursively goes through nodes
  insertRecHelper(root, val);
}

//Finds the rightmost node
Node* BST::rightMostNode(Node *node){
  if(node->right == NULL)
    return node;
  return rightMostNode(node->right);
}

//Finds the leftmost node
Node* BST::leftMostNode(Node *node){
  if(node->left == NULL)
    return node;
  return leftMostNode(node->left);
}

//find min in tree
Node* BST::findMinRec(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return leftMostNode(root);
}

//find max in tree
Node* BST::findMaxRec(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return rightMostNode(root);
}

//finds parent with data bigger than the value
Node* BST::biggerParent(Node *node, int val){
  if(node == NULL)
    return NULL;
  if(node->data > val)
    return node;
  return biggerParent(node->parent, val);
}

//finds parent with data smaller than the value
Node* BST::smallerParent(Node *node, int val){
  if(node == NULL)
    return NULL;
  if(node->data < val)
    return node;
  return smallerParent(node->parent, val);
}

Node* BST::findNextRec(Node *node){
  //recursively searches to the left of the right leaf
  if(node->right != NULL)
    return leftMostNode(node->right);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return biggerParent(node->parent, node->data);
}

Node* BST::findPrevRec(Node *node){
  //recursively searches to the right of the left leaf
  if(node->left != NULL)
    return rightMostNode(node->left);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return smallerParent(node->parent, node->data);
}

//finds a node and returns it
Node* BST::findNode(Node *curr, int val){
  if(curr == NULL)
    return NULL;
  else if(curr->data == val)
    return curr;
  else if(val > curr->data)
    return findNode(curr->right, val);
  else
    return findNode(curr->left, val);
}

//deletes from BST. Helper for deleteRec()
void BST::deleteNode(Node *node){
  //if node does not exist, do nothing (edge case)
  if(node == NULL)
    return;

  int val = node->data;

  //if it is root, we will not do anything with parent pointers
  Node *parent = node->parent;
  int isRoot = TRUE;
  if(parent != NULL)
    isRoot = FALSE;

  //case if it has no children
  if(node->left == NULL && node->right == NULL){
    //simply removes node if it is root and no children
    if(isRoot){
      root = NULL;
      return;
    }
    //changes parent pointer while removing pointer
    node = NULL;
    if(val >= parent->data)
      parent->right = NULL;
    else
      parent->left = NULL;
    return;
  }

  //case if it has one leaf node
  Node *toReplace;
  if(node->left == NULL || node->right == NULL){
    //finds node to replace
    if(node->left == NULL)
      toReplace = node->right;
    else
      toReplace = node->left;

    //swaps nodes
    toReplace->parent = parent;
    if(isRoot)
      root = toReplace;
    //changes parent pointers if not root
    else{
      if(toReplace->data > parent->data)
        parent->right = toReplace;
      else
        parent->left = toReplace;
    }
    return;
  }

  //case if two leaf nodes
  Node *next = findNextRec(node);
  node->data = next->data;
  deleteNode(next);
}

void BST::deleteRec(int val){
  //finds node to delete recursively
  Node *node = findNode(root, val);

  //deletes node
  deleteNode(node);
}

/*
------------------------------------------------------
ITERATIVE METHODS BELOW
------------------------------------------------------
*/

void BST::insertIter(int val){
  //checks if tree is empty (edge case)
  if(root == NULL){
    root = createNode(val);
    return;
  }

  //loops through the nodes until it finds a place to insert
  Node *curr = root;
  int valCurr;
  while(TRUE){
    valCurr = curr->data;

    //inserts or loops through right
    if(val > valCurr){
      if(curr->right == NULL){
        addNodeRight(curr, val);
        break;
      }
      else{
        curr = curr->right;
        continue;
      }
    }
    //inserts or loops through left
    else{
      if(curr->left == NULL){
        addNodeLeft(curr, val);
        break;
      }
      else{
        curr = curr->left;
        continue;
      }
    }
  }
}

//Finds the rightmost node
Node* BST::rightMostNodeIter(Node *node){
  while(node->right != NULL){
    node = node->right;
  }
  return node;
}

//Finds the leftmost node
Node* BST::leftMostNodeIter(Node *node){
  while(node->left != NULL){
    node = node->left;
  }
  return node;
}

//find min in tree
Node* BST::findMinIter(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return leftMostNodeIter(root);
}

//find max in tree
Node* BST::findMaxIter(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return rightMostNodeIter(root);
}

//finds parent with data bigger than the value
Node* BST::biggerParentIter(Node *node, int val){
  while(node != NULL){
    if(node->data > val)
      return node;
    node = node->parent;
  }
  return NULL;
}

//finds parent with data smaller than the value
Node* BST::smallerParentIter(Node *node, int val){
  while(node != NULL){
    if(node->data < val)
      return node;
    node = node->parent;
  }
  return NULL;
}

Node* BST::findNextIter(Node *node){
  //iteratively searches to the left of the right leaf
  if(node->right != NULL)
    return leftMostNodeIter(node->right);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return biggerParentIter(node->parent, node->data);
}

Node* BST::findPrevIter(Node *node){
  //iteratively searches to the right of the left leaf
  if(node->left != NULL)
    return rightMostNodeIter(node->left);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return smallerParentIter(node->parent, node->data);
}

Node* BST::findNodeIter(Node *curr, int val){
  while(curr != NULL){
    if(curr->data == val)
      return curr;
    else if(val > curr->data)
      curr = curr->right;
    else
      curr = curr->left;
  }
  return NULL;
}

void BST::deleteIter(int val){
  //finds node to delete iteratively
  Node *node = findNodeIter(root, val);

  //variables used in loop
  int isRoot;
  Node *parent, *toReplace, *next;

  //loops through nodes to delete
  while(node != NULL){
    val = node->data;

    //if it is root, we willx not do anything with parent pointers
    parent = node->parent;
    isRoot = TRUE;
    if(parent != NULL)
      isRoot = FALSE;

    //case if it has no children
    if(node->left == NULL && node->right == NULL){
      //simply removes node if it is root and no children
      if(isRoot){
        root = NULL;
        return;
      }
      //changes parent pointer while removing pointer
      node = NULL;
      if(val >= parent->data)
        parent->right = NULL;
      else
        parent->left = NULL;
      return;
    }

    //case if it has one leaf node
    if(node->left == NULL || node->right == NULL){
      //finds node to replace
      if(node->left == NULL)
        toReplace = node->right;
      else
        toReplace = node->left;

      //swaps nodes
      toReplace->parent = parent;
      if(isRoot)
        root = toReplace;
      //changes parent pointers if not root
      else{
        if(toReplace->data > parent->data)
          parent->right = toReplace;
        else
          parent->left = toReplace;
      }
      return;
    }

    //case if two leaf nodes
    next = findNextIter(node);
    node->data = next->data;
    node = next;
  }
}

/*end of file*/
