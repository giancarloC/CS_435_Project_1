/*
Written by Giancarlo Calle
AVL Tree Class
*/

#include <stdio.h>

struct Node{
  int data;
  Node *parent;
  Node *left;
  Node *right;
};

class AVL{
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
    AVL(){
      root = NULL;
    }

    //other methods
    void printAVL();
    void printRoot(){
      printf("Root is %d\n", root->data);
    };

  private:
    //AVL rotation methods
    void rotationR(Node *a);
    void rotationL(Node *a);

    //recursive helpers
    int heightRec(Node *node);
    int bfRec(Node *node);
    void balanceRec(Node *node);
    void insertRecHelper(Node *curr, int val);
    Node* rightMostNode(Node *node);
    Node* leftMostNode(Node *node);
    Node* biggerParent(Node *node, int val);
    Node* smallerParent(Node *node, int val);
    Node* findNode(Node *curr, int val);
    void balanceUpRec(Node *node);
    void deleteNode(Node *node);

    //iterative helpers
    int heightIter(Node *node);
    int bfIter(Node *node);
    void balanceIter(Node *node);
    Node* rightMostNodeIter(Node *node);
    Node* leftMostNodeIter(Node *node);
    Node* biggerParentIter(Node *node, int val);
    Node* smallerParentIter(Node *node, int val);
    Node* findNodeIter(Node *curr, int val);
    void balanceUpIter(Node *node);


    //other helpers
    void printHelper(Node *node);
    Node *createNode(int val);
    void addNodeLeft(Node *parentNode, int val);
    void addNodeRight(Node *parentNode, int val);
    int isRoot(Node *node);
    int isLeftChild(Node *node);
};
