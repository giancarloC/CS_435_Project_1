/*
Header for Nodes
*/
#ifndef NODE_H
#define NODE_H

struct Node{
  int data;
  Node *parent;
  Node *left;
  Node *right;
};

#endif
