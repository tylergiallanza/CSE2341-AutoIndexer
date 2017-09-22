#ifndef DS_SORTED_LINKED_LIST_H
#define DS_SORTED_LINKED_LIST_H

/*DSsortedLinkedList Class - Tyler Giallanza
 * A custom sorted linked list implementation.
 *
 * Elements are automatically inserted to perserve the ascending order of the linked list.
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
                os << ", " << *(dsn.next);
            }
            return os;
        }
};
template <class T>
class DSsortedLinkedList {
    private:
        DSlinkedListNode<T>* rootNode;
        DSlinkedListNode<T>* lastNode;
        int length;
    public:
 
        DSsortedLinkedList<T>() {
            rootNode = NULL;
            lastNode = NULL;
            length = 0;
        }

        //Copy constructor
        DSsortedLinkedList<T>(const DSsortedLinkedList& list) {
            //cout << "copying list" << endl;
            length = list.length;
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
        ~DSsortedLinkedList<T>() {
            DSlinkedListNode<T>* temp = NULL;
            while(rootNode) {
                temp = rootNode->next;
                delete rootNode;
                rootNode = temp;
            }
            rootNode = NULL;
            lastNode = NULL;
        }
        void add(T item) {
            length++;
            DSlinkedListNode<T>* temp = new DSlinkedListNode<T>;
            temp->value = item;
            temp->next = NULL;
            if(rootNode == NULL) {
                //This is the first element -- add it as root
                rootNode = temp;
                lastNode = temp;
                //cout << "Added " << item << " as new root" << endl;
            } else {
                DSlinkedListNode<T>* current = rootNode;

                if(item == current->value) {
                    //It's already in the list as the root
                    length--;
                    //Delete the node we created to store the item
                    delete temp;
                    return;
                }
                if(item < current->value) {
                    //This is the smallest element -- add it as root
                    temp->next = current;
                    rootNode = temp;
                    return;
                    //cout << "Displaced existing root" << endl;
                }
                while(current->next != NULL) {
                    if(item == current->value) {
                        //It's already in the list
                        length--;
                        delete temp;
                        return;
                    }
                    if(item < current->next->value) {
                        //We found the place for this element -- insert it
                        temp->next = current->next;
                        current->next = temp;
                        //cout << "Inserted into the middle" << endl;
                        return;
                    }
                    current = current->next;
                }
                if(item == lastNode->value) {
                    //It's already in the list
                    length--;
                    return;
                }
                //This is the largest element -- add it as the lastNode
                lastNode->next = temp;
                lastNode = temp;
                //cout << "Added at the end" << endl;
            }
        }
        T get(int index) {
            if(index>=length)
                return NULL;
            DSlinkedListNode<T>* temp = rootNode;
            int i=0;
            while(i<index) {
                temp = temp->next;
                i++;
            }
            return temp->value;
        }
        int size() {return length;}
        bool isEmpty() { return !rootNode;}
        
        bool contains(T item) {
            if(rootNode == NULL) {
                return false;
            }
            DSlinkedListNode<T>* current = rootNode;
            if(current->value == item) {
                return true;
            }

            while(current->next != NULL) {
                if(current->next->value == item) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }

        friend ostream& operator<<(ostream& os, const DSsortedLinkedList& dsl) {
            os << *(dsl.rootNode);
            return os;
        }
            
        //Swap method
        friend void swap(DSsortedLinkedList<T>& first, DSsortedLinkedList<T>& second) {
            using std::swap;

            swap(first.rootNode, second.rootNode);
            swap(first.lastNode, second.lastNode);
            swap(first.length, second.length);
        }
        //Assignment operator
        DSsortedLinkedList<T>& operator= (DSsortedLinkedList<T> other) {
            //cout << "Assigning list" << endl;
            swap(*this, other);
            return *this;
        }
};
#endif
