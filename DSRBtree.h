#ifndef DS_RB_TREE_H
#define DS_RB_TREE_H

#include <iostream>
#include "DSsortedLinkedList.h"

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
        bool insertNoRepeat(T key, K value) {
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
                return true;
            }
            
            DSRBnode<T,K>* current = rootNode;
            DSRBnode<T,K>* currentParent;
            while(!(current->key==sentinel)) {
                if(key == current->key) {
                    current->values->add(value);
                    return false;
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

            return true;
        }
        void storeKeyValue(T key, K value) { 
            insertNoRepeat(key,value);

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
};
#endif
