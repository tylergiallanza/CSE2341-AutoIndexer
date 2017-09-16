#ifndef DS_RB_TREE_H
#define DS_RB_TREE_H

#include <iostream>
#include "DSsortedLinkedList.h"
#include "DSvector.h"

/*DSRBtree Class - Tyler Giallanza
 * A custom implementation of a red black tree dictionary that stores (key,val) pairs.
 *
 * Self balancing binary search tree.
 * Includes methods for insertion, searching, and in-order traversal.
*/

using namespace std;

template <class T, class K>
class DSRBnode;

template <class T, class K>
class DSRBnode {
    public:
        bool black;
        T key;
        DSsortedLinkedList<K>* values = new DSsortedLinkedList<K>;
        DSRBnode<T,K> *left, *right, *parent;
        //NOTE: no constructor is used
        //NOTE: no copy constructor, assignment operator, or deconstructor
        //needed because no memory is dynamically allocated

};
template <class T, class K>
class DSRBtree {
    private:
        DSRBnode<T,K>* rootNode;
        T sentinel;
    public:
        //Default constructor
        DSRBtree<T,K>(T s) {
            rootNode = NULL;
            sentinel = s;
        }
        //Copy constructor
        DSRBtree(const DSRBtree& other) {
            rootNode = other.rootNode;
            sentinel = other.sentinel;
        }
        //Deconstructor
        ~DSRBtree() {
        }
        //Assignment operator
        DSRBtree<T,K>& operator= (const DSRBtree<T,K> &other) {
            rootNode = other.rootNode;
            sentinel = other.sentinel;
        }
        bool contains(T key) {
            return false;
        }
        DSRBnode<T, K>* insertNoRepeat(T key, K value) {
            if(rootNode == NULL) {
                rootNode = new DSRBnode<T,K>;
                rootNode->key = key;
                rootNode->values->add(value);
                rootNode->black = true;
                rootNode->left=new DSRBnode<T,K>;
                rootNode->left->key=sentinel;
                rootNode->left->black=true;
                rootNode->right=new DSRBnode<T,K>;
                rootNode->right->key=sentinel;
                rootNode->right->black=true;
                rootNode->parent = NULL;
                return rootNode;
            }
            
            DSRBnode<T,K>* current = rootNode;
            DSRBnode<T,K>* currentParent;
            while(!(current->key==sentinel)) {
                if(key == current->key) {
                    current->values->add(value);
                    return NULL;
                } else if(key < current->key) {
                    currentParent = current;
                    current = current->left;
                } else {
                    currentParent = current;
                    current = current->right;
                }
            }
            current->key = key;
            current->values->add(value);
            current->black=false;
            current->left=new DSRBnode<T,K>;
            current->left->key=sentinel;
            current->left->black=true;
            current->right=new DSRBnode<T,K>;
            current->right->key=sentinel;
            current->right->black=true;
            current->parent = currentParent;

            return current;
        }
        void leftRotate(DSRBnode<T, K>* current) {
            DSRBnode<T, K>* right = current->right;
            current->right = right->left;
            if(current->right && !(current->right->key == sentinel)) {
                current->right->parent = current;
            }
            right->parent = current->parent;
            if(!current->parent || current->parent->key == sentinel) {
                rootNode = right;
            } else if(current->key == current->parent->left->key) {
                current->parent->left = right;
            } else {
                current->parent->right = right;
            }
            right->left = current;
            current->parent = right;
        }
        void rightRotate(DSRBnode<T, K>* current) {
            DSRBnode<T, K>* left = current->left;
            current->left = left->right;
            if(current->left && !(current->left->key == sentinel)) {
                current->left->parent = current;
            }
            left->parent = current->parent;
            if(!current->parent || current->parent->key == sentinel) {
                rootNode = left;
            } else if(current->key == current->parent->left->key) {
                current->parent->left = left;
            } else {
                current->parent->right = left;
            }

            left->right = current;
            current->parent = left;
        }
        void fixViolations(DSRBnode<T, K>* current) {
            DSRBnode<T, K>* parent = NULL;
            DSRBnode<T, K>* grandparent = NULL;

            while( !(current->key == rootNode->key) && !(current->black) && !(current->parent->black)) {
                parent = current->parent;
                grandparent = parent->parent;

                //Parent is a left child
                if(parent->key == grandparent->left->key) {
                    DSRBnode<T, K>* uncle = grandparent->right;
                    //If the uncle is also red, recolor
                    if(!uncle->black) {
                        grandparent->black = false;
                        parent->black = true;
                        uncle->black = true;
                        current = grandparent;
                    } else {
                        //This node is a right child
                        if(current->key == parent->right->key) {
                            leftRotate(current);
                            current = parent;
                            parent = current->parent;
                        }
                        //Either this node was already a left child,
                        //or it became a left child after the leftRotate
                        rightRotate(grandparent);
                        bool temp = parent->black;
                        parent->black = grandparent->black;
                        grandparent->black = temp;
                        current = parent;
                    }
                } else {
                    DSRBnode<T, K>* uncle = grandparent->left;

                    //If the uncle is also red, recolor
                    if(!uncle->black) {
                        grandparent->black = false;
                        parent->black = true;
                        uncle->black = true;
                        current = grandparent;
                    } else {
                        //This node is a left child
                        if(current->key == parent->left->key) {
                            rightRotate(parent);
                            current = parent;
                            parent = current->parent;
                        }
                        //Either this node was already a right child,
                        //or it became one after the rightRotate
                        leftRotate(grandparent);
                        bool temp = parent->black;
                        parent->black = grandparent->black;
                        grandparent->black = temp;
                        current = parent;
                    }
                }
            }

            rootNode->black = true;
        }

        void storeKeyValue(T key, K value) { 
            //Insert into the tree normally
            //True if a new node was created
            DSRBnode<T, K>* current = insertNoRepeat(key,value);
            if(current != NULL) {
                //A new node was created -- check if it violates RBTree properties
                fixViolations(current);
            }

        }
        friend ostream& printHelper(ostream&os, const DSRBtree<T,K>& tree, DSRBnode<T, K>* current) {
                if(!(current->left->key==tree.sentinel)) {
                    printHelper(os,tree,current->left);
                }

                os << current->key << ": " << *(current->values) << endl;

                if(!(current->right->key==tree.sentinel)) {
                    printHelper(os,tree,current->right);
                }

                return os;
        }
        friend ostream& operator<<(ostream& os, const DSRBtree<T,K>& tree) {
            DSRBnode<T, K>* current = tree.rootNode;
            return printHelper(os,tree,current);
        }

        void inOrderHelper(DSRBnode<T, K>* current, DSvector<DSRBnode<T, K>>* v) {
                if(!(current->left->key==sentinel)) {
                    inOrderHelper(current->left, v);
                }

                v->add(*current);

                if(!(current->right->key==sentinel)) {
                    inOrderHelper(current->right, v);
                }
        }
        DSvector<DSRBnode<T, K>> inOrderTraverse() {
            DSvector<DSRBnode<T, K>>* result = new DSvector<DSRBnode<T, K>>;

            inOrderHelper(rootNode,result);

            return *result;
        }
};
#endif
