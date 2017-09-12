#ifndef DS_RB_TREE_H
#define DS_RB_TREE_H

#include <iostream>

/*DSRBtree Class - Tyler Giallanza
 * A custom implementation of a red black tree.
 *
 * Self balancing binary search tree.
 * Includes methods for insertion, searching, and in-order traversal.
*/

using namespace std;

template <class T, class K>
class DSRBtree {
    private:
    public:
        //Default constructor
        DSRBtree<T,K>() {
        }
        //Copy constructor
        DSRBtree(const DSRBtree& other) {
        }
        //Deconstructor
        ~DSRBtree() {
        }
        //Assignment operator
        DSRBtree<T,K>& operator= (const DSRBtree<T,K> &other) {
        }
        bool contains(T key) {
            return false;
        }
        void storeKeyValue(T key, K value) { 

        };
        friend ostream& operator<<(ostream& os, const DSRBtree<T,K>& tree) {
            return os;
        }
};
#endif
