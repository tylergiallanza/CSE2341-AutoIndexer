#ifndef DS_LINKED_LIST_H
#define DS_LINKED_LIST_H

/*DSlinkedList Class - Tyler Giallanza
 * A custom linked list implementation.
 *
 * This class is templated to work with any class of object.
 *
*/

#include <iostream>
using namespace std;

template <class T>
class DSlinkedListNode;
template <class T>
class DSlinkedListNode {
    public:
        T value;
        DSlinkedListNode* next;
        //NOTE: no constructor is used
        //NOTE: no copy constructor, assignment operator, or deconstructor
        //needed because no memory is dynamically allocated

        // << Operator
        friend ostream& operator<<(ostream& os, const DSlinkedListNode& dsn) {
            os << dsn.value;
            if(dsn.next != NULL) {
                os << " " << *(dsn.next);
            }
            return os;
        }

};
template <class T>
class DSlinkedList {
    private:
        DSlinkedListNode<T>* rootNode;
        DSlinkedListNode<T>* lastNode;
    public:
 
        DSlinkedList<T>() {
            rootNode = NULL;
            lastNode = NULL;
        }

        //Copy constructor
        DSlinkedList<T>(const DSlinkedList& list) {
            DSlinkedListNode<T>* current = list.rootNode;
            DSlinkedListNode<T>* newRoot = NULL;
            while(current != NULL) {
                DSlinkedListNode<T>* temp = new DSlinkedListNode<T>; 
                temp->value = current->value;
                temp->next = NULL;
                if(newRoot != NULL) {
                    newRoot->next = temp;
                } else {
                    newRoot = temp;
                }
           
                current = current->next;
                lastNode = temp;
            }

            rootNode = list.rootNode;
        }

        //Deconstructor
        ~DSlinkedList<T>() {
            DSlinkedListNode<T>* current = rootNode;
            DSlinkedListNode<T>* nextNode;
            while(current != NULL) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
        void add(T item) {
            DSlinkedListNode<T>* temp = new DSlinkedListNode<T>;
            temp->value = item;
            temp->next = NULL;
            if(rootNode == NULL) {
                rootNode = temp;

            } else {
                lastNode->next = temp;
            }
            lastNode = temp;
        }
        bool isEmpty() { return !rootNode;}
        
        bool contains(T item) {
            if(rootNode == NULL) {
                //cout << "didn't find b/c root dne" << endl;
                return false;
            }
            DSlinkedListNode<T>* current = rootNode;
            if(current->value == item) {
                //cout << "did find at root" << endl;
                return true;
            }

            while(current->next != NULL) {
                if(current->next->value == item) {
                    //cout << "found at " << current->next->value;
                    return true;
                }
                //cout << "did not find at " << current->next->value << endl;
                current = current->next;
            }
            return false;
        }

        friend ostream& operator<<(ostream& os, const DSlinkedList& dsl) {
            os << "linked list <" << *(dsl.rootNode) << ">";
            return os;
        }
            
        //Assignment operator
        DSlinkedList<T>& operator= (const DSlinkedList<T> &list) {
            if(&list != this) {
            DSlinkedListNode<T>* current = list.rootNode;
            DSlinkedListNode<T>* newRoot = NULL;
            while(current != NULL) {
                DSlinkedListNode<T>* temp = new DSlinkedListNode<T>; 
                temp->value = current->value;
                temp->next = NULL;
                if(newRoot != NULL) {
                    newRoot->next = temp;
                } else {
                    newRoot = temp;
                }
           
                current = current->next;
            }

            rootNode = list.rootNode;
            }
            return *this;
        }
};
#endif
