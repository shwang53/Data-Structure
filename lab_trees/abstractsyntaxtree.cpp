#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */

 double toInt(string s)
{
    double num = 0;
    for (double i=0; i<s.length();  i++)
        num = num*10 + (double(s[i])-48);
    return num;
}
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    typename BinaryTree<std::string>::Node* root = AbstractSyntaxTree::getRoot();
    // empty tree

    return evals(root);
}

double AbstractSyntaxTree::evals(typename BinaryTree<std::string>::Node* root) const {
    // @TODO Your code goes here...
  //  typename BinaryTree<std::string>::Node* root = AbstractSyntaxTree::getRoot();
    // empty tree

  if (!root){return 0; }
  if (!root->left && !root->right){  return toInt(root->elem);}

  double leftValue = evals(root->left);
  double rightValue = evals(root->right);

  if (root->elem=="+"){ return leftValue+rightValue; }
  if (root->elem=="-"){ return leftValue-rightValue; }
  if (root->elem=="*"){ return leftValue*rightValue;}
  if (root->elem=="/"){ return leftValue/rightValue; }
  return 0;

}
