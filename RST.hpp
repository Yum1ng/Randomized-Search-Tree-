#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <iostream>

using namespace std;

template <typename Data>
class RST : public BST<Data> {

public:


  /* Insert new data into the RST if it is not already present.
   * Input
   *    item - the data to insert.
   *    return - true if the item was inserted. If the item was already contained in
   *       the tree then return false.
   */
  virtual bool insert(const Data& item) {
    if(!(this -> root)){ //Insert at the root
        BST<Data>::root = new BSTNode<Data>(item);
        BST<Data>::root -> priority = rand();
        return true;
    }
    else{
        BSTNode<Data> *last = NULL;
        BSTNode<Data> *curr = BST<Data>::root;
        while(curr != NULL){   
            if (item < curr->data){
                last = curr;
                curr = curr->left; 
            }
            else if (item > curr->data){
                last = curr;
                curr = curr->right;
            } 
            else if (item == curr->data){
                return false;
            }
        }
        BSTNode<Data> *newNode = new BSTNode<Data>(item);
        newNode -> priority = rand(); // Random the priority
        newNode -> parent = last;
        if(item < last -> data){
            last -> left = newNode;
        }
        else{
            last -> right = newNode;
        }
       // Now deal with priority regarding heap structure
       // TODO: the value passing may have problem 
        while(last != NULL && newNode -> priority > last -> priority){
            if (last -> left == newNode){
                rotateRight(last, newNode);   
            }
            if (last -> right == newNode){
               rotateLeft(last, newNode);
            }
            //update last to point to the new parent node
            last = newNode -> parent;
       }
    }
    return true;
  }

private:

  /* Perform a 'right rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a left child
   *    child - the left child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the right-child of 'child'.
   *
   */
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {
        
        par -> left = child -> right;
        if (child -> right != NULL){
            par -> left -> parent = par;
        }   
        child -> right = par;
        child -> parent = par -> parent;
        par -> parent = child;
        // change the pointer of grandparent
        if(child -> parent != NULL && child -> parent -> left == par){
            child -> parent -> left = child;
        }
        else if(child -> parent != NULL && child -> parent -> right == par){
            child -> parent -> right = child;
        }
        else if(child -> parent == NULL){
            BST<Data>::root = child; //set child to root at the end of each rotation
        }
        
        return;        
    // TODO: Implement this function!

  }


  /* Perform a 'left rotation' that changes the structure of the tree without
   * interfering with the size, data content, and left->right order of nodes in the RST.
   * This rotation is done by changing the 'left', 'right', and/or 'parent' pointers
   * of a subset of nodes without changing their 'priority' values.
   *
   * Input
   *    par - a parent node in the RST with a right child
   *    child - the right child of 'par'
   *
   * Output
   *   The resulting tree will have 'par' and 'child' in the same order but switched
   *   in level, meaning 'par' will effectively become the left-child of 'child'.
   *
   */
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child )
  {
        
        par -> right = child -> left;
        if (child -> left != NULL){
            par -> right -> parent = par;
        }
        child -> left = par;
        child -> parent = par -> parent;
        par -> parent = child;
        // change the pointer of grandparent
        if(child -> parent != NULL && child -> parent -> left == par){
            child -> parent -> left = child;
        }
        else if(child -> parent != NULL && child -> parent -> right == par){
            child -> parent -> right = child;
        }
        else if(child -> parent == NULL){
            BST<Data>::root = child; // Set child as root
        }
        return;                
    // TODO: Implement this function!

  }

public:

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Calls BST::insert so we can add data to test rotateRight and rotateLeft before
   * implementing the fully correct version of RST::insert.
   *
   */
  bool BSTinsert(const Data& item) {

    return BST<Data>::insert(item);

  }

  /* THIS FUNCTION IS USED FOR TESTING, DO NOT MODIFY
   *
   * Locates the node for an item and rotates it left or right without changing the
   * left->right order of nodes in the RST
   * Input
   *    item - the Data item to rotate.
   *    leftOrRight - if true then rotateLeft, otherwise rotateRight
   *    output - 0 if item could be found and had a child to rotate with, 1 if not. -1 if
   *         rotation failed for other reasons
   */
  int findAndRotate(const Data& item, bool leftOrRight) {

     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }

     if (current == 0 or current->data != item) {
       return 1;
     }

     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);

       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }

     } else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);

       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};
#endif // RST_HPP
