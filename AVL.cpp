/*
Written by Giancarlo Calle
AVL Tree Method Implementations
*/

#include "AVL.h"
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <tuple>
#define FALSE 0
#define TRUE 1

//helper function for printAVL()
void AVL::printHelper(Node *node){
  if(node == NULL)
    return;
  printHelper(node->left);
  printf("%d ", node->data);
  printHelper(node->right);
}

//prints elements in order from AVL tree
void AVL::printAVL(){
  //prints inOrder
  printHelper(root);
  printf("\n");
}

//creates node to be added to AVL tree
Node* AVL::createNode(int val){
  Node *node = (Node*)malloc(sizeof(Node));
  node->data = val;
  return node;
}

//adds node as a left child
Node* AVL::addNodeLeft(Node *parentNode, int val){
  //adds node to left child and adds parent pointer
  Node *node = createNode(val);
  parentNode->left = node;
  node->parent = parentNode;
  return node;
}

//adds node as right child
Node* AVL::addNodeRight(Node *parentNode, int val){
  //adds node to left child and adds parent pointer
  Node *node = createNode(val);
  parentNode->right = node;
  node->parent = parentNode;
  return node;
}

//returns if root or not
int AVL::isRoot(Node *node){
  return node->parent == NULL;
}

//returns if left child or not
int AVL::isLeftChild(Node *node){
  if(node->parent->data > node->data)
    return TRUE;
  return FALSE;
}

//right rotation
void AVL::rotationR(Node *a){
  //grabs left child node for rotation
  Node *b = a->left;

  //grabs children of b
  Node *bLeft = b->left;
  Node *bRight = b->right;

  //case if we are working w/ root, no need to change parent pointers
  if(isRoot(a)){
    root = b;
    b->parent = NULL;
  }
  else{
    Node *parent = a->parent;
    if(isLeftChild(a))
      parent->left = b;
    else
      parent->right = b;
    b->parent = parent;
  }

  a->left = bRight;
  if(bRight != NULL)
    bRight->parent = a;
  a->parent = b;
  b->right = a;
}

//left rotation
void AVL::rotationL(Node *a){
  //grabs left child node for rotation
  Node *b = a->right;

  //grabs children of b
  Node *bLeft = b->left;
  Node *bRight = b->right;

  //case if we are working w/ root, no need to change parent pointers
  if(isRoot(a)){
    root = b;
    b->parent = NULL;
  }
  else{
    Node *parent = a->parent;
    if(isLeftChild(a))
      parent->left = b;
    else
      parent->right = b;
    b->parent = parent;
  }

  a->right = NULL;
  if(bLeft != NULL){
    bLeft->parent = a;
    a->right = bLeft;
  }
  a->parent = b;
  b->left = a;
}

/*
------------------------------------------------------
RECURSIVE METHODS BELOW
------------------------------------------------------
*/

//recursively returns height of tree
int AVL::heightRec(Node *node){
  if(node == NULL)
    return -1;
  int left = heightRec(node->left) + 1;
  int right = heightRec(node->right) + 1;
  return (left > right ? left : right); //returns bigger height
}

//returns balance factor (bf) recursively
int AVL::bfRec(Node *node){
  return heightRec(node->left) - heightRec(node->right);
}

void AVL::balanceRec(Node *node){
  if(node == NULL)
    return;

  int bf = bfRec(node);
  //case if already balanced
  if(bf >= -1 && bf <= 1)
    return;

  //case if needs right rotation
  if(bf > 1){
    //checks if needs left rotation first
    if(bfRec(node->left) <= -1){
      rotationL(node->left);
    }
    rotationR(node);
  }
  //case if needs left rotation
  else{
    //checks if needs right rotation first
    if(bfRec(node->right) >= 1){
      rotationR(node->right);
    }
    rotationL(node);
  }
}

//ensures node and it's parents are balanced
void AVL::balanceUpRec(Node *node){
  if(node == NULL)
    return;
  balanceRec(node);
  balanceUpRec(node->parent);
}

//recursive helper function for insertRec()
Node* AVL::insertRecHelper(Node *curr, int val){
  int valCurr = curr->data;
  Node *node;
  if(val > valCurr){
    if(curr->right == NULL)
      return addNodeRight(curr, val);
    else
      return insertRecHelper(curr->right, val);
  }
  else{
    if(curr->left == NULL)
      return addNodeLeft(curr, val);
    else
      return insertRecHelper(curr->left, val);
  }
}

//inserts value onto AVL
void AVL::insertRec(int val){
  //checks if tree is empty (edge case)
  if(root == NULL){
    root = createNode(val);
    return;
  }

  //recursively goes through nodes
  Node *node = insertRecHelper(root, val);
  balanceUpRec(node);
}

//Finds the rightmost node
Node* AVL::rightMostNode(Node *node){
  if(node->right == NULL)
    return node;
  return rightMostNode(node->right);
}

//Finds the leftmost node
Node* AVL::leftMostNode(Node *node){
  if(node->left == NULL)
    return node;
  return leftMostNode(node->left);
}

//find min in tree
Node* AVL::findMinRec(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return leftMostNode(root);
}

//find max in tree
Node* AVL::findMaxRec(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return rightMostNode(root);
}

//finds parent with data bigger than the value
Node* AVL::biggerParent(Node *node, int val){
  if(node == NULL)
    return NULL;
  if(node->data > val)
    return node;
  return biggerParent(node->parent, val);
}

//finds parent with data smaller than the value
Node* AVL::smallerParent(Node *node, int val){
  if(node == NULL)
    return NULL;
  if(node->data < val)
    return node;
  return smallerParent(node->parent, val);
}

Node* AVL::findNextRec(Node *node){
  //recursively searches to the left of the right leaf
  if(node->right != NULL)
    return leftMostNode(node->right);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return biggerParent(node->parent, node->data);
}

Node* AVL::findPrevRec(Node *node){
  //recursively searches to the right of the left leaf
  if(node->left != NULL)
    return rightMostNode(node->left);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return smallerParent(node->parent, node->data);
}

//finds a node and returns it recursively
Node* findNodeRec(Node *curr, int val){
  if(curr == NULL)
    return NULL;
  else if(curr->data == val)
    return curr;
  else if(val > curr->data)
    return findNodeRec(curr->right, val);
  else
    return findNodeRec(curr->left, val);
}

//deletes from AVL. Helper for deleteRec()
void AVL::deleteNode(Node *node){
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
      free(node);
      root = NULL;
      return;
    }
    //changes parent pointer while removing pointer
    node = NULL;
    if(val >= parent->data)
      parent->right = NULL;
    else
      parent->left = NULL;

    free(node);
    balanceUpRec(parent);
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
    free(node);
    balanceUpRec(toReplace);
    return;
  }

  //case if two leaf nodes
  Node *next = findNextRec(node);
  node->data = next->data;
  deleteNode(next);
  balanceUpRec(node);
}

void AVL::deleteRec(int val){
  //finds node to delete recursively
  Node *node = findNodeRec(root, val);

  //deletes node
  deleteNode(node);
}

/*
------------------------------------------------------
ITERATIVE METHODS BELOW
------------------------------------------------------
*/

int AVL::heightIter(Node *node){
  if(node == NULL)
    return -1;

  //creates queue and adds all nodes to queue to find height
  std::queue<std::tuple<Node*, int>> queue;
  std::tuple<Node*, int> firstTup = std::make_tuple(node, 0);
  queue.push(firstTup);

  int maxHeight = 0;
  int height;
  while(queue.size() > 0){

    //gets all the nodes in that level
    int size = queue.size();
    while(size > 0){
      std::tuple<Node*, int> popped = queue.front();
      queue.pop();
      node = std::get<0>(popped);
      height = std::get<1>(popped);

      //replaces height
      if(height > maxHeight)
        maxHeight = height;

      //adds other nodes to queue while incrementing height
      if(node->left != NULL){
        std::tuple<Node*, int> tup(node->left, height+1);
        queue.push(tup);
      }
      if(node->right != NULL){
        std::tuple<Node*, int> tup(node->right, height+1);
        queue.push(tup);
      }
      size--;
    }

  }
  return maxHeight;
}

int AVL::bfIter(Node *node){
  return heightIter(node->left) - heightIter(node->right);
}

void AVL::balanceIter(Node *node){
  if(node == NULL)
    return;

  int bf = bfIter(node);
  //case if already balanced
  if(bf >= -1 && bf <= 1)
    return;

  //case if it needs a right rotation
  if(bf > 1){
    //checks if it needs a left rotation first
    if(bfIter(node->left) <= -1){
      rotationL(node->left);
    }
    rotationR(node);
  }
  //case if needs left rotation
  else{
    //checks if needs right rotation first
    if(bfIter(node->right) >= 1){
      rotationR(node->right);
    }
    rotationL(node);
  }
}

void AVL::balanceUpIter(Node *node){
  while(node != NULL){
    balanceIter(node);
    node = node->parent;
  }
}

int AVL::insertIter(int val){
  //checks if tree is empty (edge case)
  int counter = 0; //counts how many levels we traverse

  if(root == NULL){
    root = createNode(val);
    return counter;
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
        curr = curr->right;
        break;
      }
      else{
        counter++;
        curr = curr->right;
        continue;
      }
    }
    //inserts or loops through left
    else{
      if(curr->left == NULL){
        addNodeLeft(curr, val);
        curr = curr->left;
        break;
      }
      else{
        counter++;
        curr = curr->left;
        continue;
      }
    }
  }

  balanceUpIter(curr);
  return counter;
}

//Finds the rightmost node
Node* AVL::rightMostNodeIter(Node *node){
  while(node->right != NULL){
    node = node->right;
  }
  return node;
}

//Finds the leftmost node
Node* AVL::leftMostNodeIter(Node *node){
  while(node->left != NULL){
    node = node->left;
  }
  return node;
}

//find min in tree
Node* AVL::findMinIter(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return leftMostNodeIter(root);
}

//find max in tree
Node* AVL::findMaxIter(){
  if(root == NULL) //edge case if tree is empty
    return NULL;
  return rightMostNodeIter(root);
}

//finds parent with data bigger than the value
Node* AVL::biggerParentIter(Node *node, int val){
  while(node != NULL){
    if(node->data > val)
      return node;
    node = node->parent;
  }
  return NULL;
}

//finds parent with data smaller than the value
Node* AVL::smallerParentIter(Node *node, int val){
  while(node != NULL){
    if(node->data < val)
      return node;
    node = node->parent;
  }
  return NULL;
}

Node* AVL::findNextIter(Node *node){
  //iteratively searches to the left of the right leaf
  if(node->right != NULL)
    return leftMostNodeIter(node->right);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return biggerParentIter(node->parent, node->data);
}

Node* AVL::findPrevIter(Node *node){
  //iteratively searches to the right of the left leaf
  if(node->left != NULL)
    return rightMostNodeIter(node->left);
  //if has no parent, return NULL
  if(node->parent == NULL)
    return NULL;
  //if parent is bigger, return parent
  return smallerParentIter(node->parent, node->data);
}

Node* AVL::findNodeIter(Node *curr, int val){
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

int AVL::deleteIter(int val){
  int counter = 0;

  //finds node to delete iteratively
  Node *node = root;
  if(root == NULL)
    return counter;
  while(node->data != val){
    if(val > node->data)
      node = node->right;
    else
      node = node->left;
    counter++;
  }

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
        free(node);
        root = NULL;
        return counter;
      }
      //changes parent pointer while removing pointer
      node = NULL;
      if(val >= parent->data)
        parent->right = NULL;
      else
        parent->left = NULL;

      free(node);
      balanceUpIter(parent);
      return counter;
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
      free(node);
      balanceUpIter(toReplace);
      return counter;
    }

    //case if two leaf nodes
    next = findNextIter(node);
    node->data = next->data;
    node = next;
  }
  return counter;
}

/*end of file*/
