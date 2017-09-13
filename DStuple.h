#ifndef DS_TUPLE_H
#define DS_TUPLE_H

#include <iostream>

/*DStuple Class - Tyler Giallanza
 * A custom implementation of a tuple.
 *
 * Simple data container that holds two differently-typed values.
*/

using namespace std;

template <class T, class K>
class DStuple {
    private:
    public:
        T* first;
        K* second;
        //Default constructor
        DStuple<T,K>() {
        }
        //Copy constructor
        DStuple(const DStuple& other) {
        }
        //Deconstructor
        ~DStuple() {
        }
        //Assignment operator
        DStuple<T,K>& operator= (const DStuple<T,K> &other) {
        }
        bool contains(T key) {
            return false;
        }
        friend ostream& operator<<(ostream& os, const DStuple<T,K>& tree) {
            return os;
        }
};
#endif
