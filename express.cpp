//Vikram Tharakan 5/30/17
//express.cpp

#include "express.h"
#include <cstdlib>
#include <iostream>
using std::cout;


// CONSTRUCTORS and DESTRUCTOR
ExpressionTree::ExpressionTree(double value){
  //Just sets the tree to have one leaf node set to value
  data = value;
  left = NULL;
  right = NULL;
}

ExpressionTree::ExpressionTree(const ExpressionTree& source){
  //Apparently gotta use the word this to make it a deep copy
  // ^Figure out why that is so
  this->data = source.data;
  this->operation = source.operation;

  //Sets the left branch of the tree (if it exists) through a recursive call
  if(source.left != NULL)
    this->left = new ExpressionTree(*(source.left));
  else
    this->left = NULL;
  
  //Sets the right branch of the tree (if it exists) through recursive call
  if(source.left != NULL)
    this->right = new ExpressionTree(*(source.right));
  else
    this->right = NULL;
  
}

ExpressionTree::~ExpressionTree( ){
  //We only need to delete the left and right child of the tree
  delete left;
  left = NULL;
  delete right;
  right = NULL;
}

// ASSIGNMENT OPERATOR
ExpressionTree& ExpressionTree::operator =(const ExpressionTree& source){
  //We can write this usin the same method as the copy constructor
  //Only difference is we need to return *this at the end due to return type

  //Once again gott use "this". WHY
  this->data = source.data;
  this->operation = source.operation;

  //Sets the left branch of the tree (if it exists) through a recursive call
  if(source.left != NULL)
    this->left = new ExpressionTree(*(source.left));
  else
    this->left = NULL;

  //Sets the right branch of the tree (if it exists) through recursive call
  if(source.left != NULL)
    this->right = new ExpressionTree(*(source.right));
  else
    this->right = NULL;

  return *this;

}

// CONSTANT MEMBER FUNCTIONS
double ExpressionTree::evaluate( ) const{
  //Base case: all we have is one leaf
  if(left == NULL && right == NULL){
    return data;
  }
  //Expand for 2nd case: There IS a left and right child
  else{
    if(operation == '+')
      return left->evaluate() + right->evaluate();
    else if(operation == '*')
      return left->evaluate() * right->evaluate();
  }
}

void ExpressionTree::printPre() const{
  if(left == NULL && right == NULL)
    cout << data << " ";
  else{
    cout << operation;
    cout << " ";
    left->printPre();
    right->printPre();
  }
}

void ExpressionTree::printPost() const{
  if(left == NULL && right == NULL)
    cout << data << " ";
  else{
    left->printPost();
    right->printPost();
    cout << operation;
    cout << " ";
  }

}

void ExpressionTree::printIn() const{
  if(left == NULL && right == NULL)
    cout << data << " ";
  else{
    if(operation == '+'){
      cout << "( ";
      left->printIn();
      cout << operation;
      cout << " ";
      right->printIn();
      cout << ") ";
    }
    else if(operation == '*'){
      left->printIn();
      cout << operation;
      cout << " ";
      right->printIn();
    }
  }
  
}

// NONMEMBER FUNCTIONS FOR BUILDING BIGGER EXPRESSION TREES:
ExpressionTree operator +(const ExpressionTree& e1, const ExpressionTree& e2){
  ExpressionTree *e = new ExpressionTree;
  e->operation = '+';
  e->left = new ExpressionTree(e1);
  e->right = new ExpressionTree(e2);
  return *e;
}

ExpressionTree operator *(const ExpressionTree& e1, const ExpressionTree& e2){
  ExpressionTree *e = new ExpressionTree;
  e->operation = '*';
  e->left = new ExpressionTree(e1);
  e->right = new ExpressionTree(e2);
  return *e;
}
