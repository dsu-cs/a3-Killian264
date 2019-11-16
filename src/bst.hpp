#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    if(root != NULL) inorderHelper(vec, root);

    return vec;
}
template<class T>
 std::vector<T> * inorderHelper(std::vector<T> *vec, Node<T>* node )
{
    if(node->get_left() != NULL){
        vec = inorderHelper(vec, node->get_left());
    }
    vec->push_back(node->get_data());
    if(node->get_right() != NULL){
        vec = inorderHelper(vec, node->get_right());
    }
    return vec;
}


template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    if(root != NULL) preorderHelper(vec, root);

    return vec;
}
template<class T>
 std::vector<T> * preorderHelper(std::vector<T> *vec, Node<T>* node )
{
    vec->push_back(node->get_data());
    if(node->get_left() != NULL){
        vec = preorderHelper(vec, node->get_left());
    }
    if(node->get_right() != NULL){
        vec = preorderHelper(vec, node->get_right());
    }
    return vec;
}


template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    if(root != NULL) postorderHelper(vec, root);

    return vec;
}
template<class T>
 std::vector<T> * postorderHelper(std::vector<T> *vec, Node<T>* node )
{
    if(node->get_left() != NULL){
        vec = postorderHelper(vec, node->get_left());
    }
    if(node->get_right() != NULL){
        vec = postorderHelper(vec, node->get_right());
    }
    vec->push_back(node->get_data());
    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    if(root == NULL){
        root = new Node<T>(new_data);
        return;
    }
    insertHelper(new_data, root);
}
template<class T>
void insertHelper(T new_data, Node<T>* node){
    if(node->get_left() == NULL && new_data < node->get_data()){
        node->set_left(new Node<T>(new_data));
    }
    else if(node->get_right() == NULL && new_data > node->get_data()){
        node->set_right(new Node<T>(new_data));
    }
    else if(new_data > node->get_data()){
        insertHelper(new_data, node->get_right());
    }
    else{
         insertHelper(new_data, node->get_left());
    }
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    return(searchHelper(val, root));
}

template<class T>
Node<T>* searchHelper(T val, Node<T>* node)
{
    if(node == NULL){
        return NULL;
    }
    if(val == node->get_data()){
        return node;
    }
    if(val > node->get_data()){
        return(searchHelper(val, node->get_right()));
    }
    else{
         return(searchHelper(val, node->get_left()));
    }
}


template<class T>
void BST<T>::remove(T val)
{
    if(root == NULL){
        return;
    }
    removeHelper(val, root);
}
template<class T>
Node<T>* removeHelper(T val, Node<T>* node){
    Node<T>* tmp;
    if(node == NULL) return NULL;
    else if(val > node->get_data()){
        node->set_right(removeHelper(val, node->get_right()));
    }
    else if(val < node->get_data()){
         node->set_left(removeHelper(val, node->get_left()));
    }
    else{
        Node<T> * tmp;
        if(node->get_left() == NULL ){
            tmp = node->get_right();
            delete(node);
            return tmp;
        }
        else if(node->get_right() == NULL ){
            tmp = node->get_left();
            delete(node);
            return tmp;
        }
        else{
            T maxVal = maxValueHelper(node->get_left());
            node->set_data(maxVal);
            node->set_left(removeHelper(maxVal, node->get_left()));
        }
    }
}
template<class T>
T maxValueHelper(Node<T>* node){
    if(node->get_right() == NULL){
        return node->get_data();
    }
    return(maxValueHelper(node->get_right()));
}

//


template<class T>
int BST<T>::get_size()
{
    return(get_sizeHelper(root));
}
template<class T>
int get_sizeHelper(Node<T>* node)
{
    if(node == NULL){
        return 0;
    }
    return(
        get_sizeHelper(node->get_left()) 
        + get_sizeHelper(node->get_left()) 
        + 1
    );
}
