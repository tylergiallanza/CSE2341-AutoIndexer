#ifndef DS_VECTOR_H
#define DS_VECTOR_H

#include <iostream>

/*DSvector Class - Tyler Giallanza
 * A custom implementation of the std::vector class.
 *
 * Serves as a dynamically resizable array.
*/

using namespace std;

template <class T>
class DSvector {
    private:
        T* arr;
        int max_size;
        int length;
    public:
        /* ----- Constructors ----- */
        //Default constructor - reserve 10 spaces
        DSvector<T>() {
            length=0;
            max_size=10;
            arr = new T[max_size];
        };
        //Copy constructor
        DSvector(const DSvector& v) {
            length = v.length;
            max_size = v.max_size;

            arr = new T[max_size];

            for(int i=0;i<length;i++) {
                arr[i] = v.arr[i];
            }
        };
        //Deconstructor
        ~DSvector() {
            delete [] arr;
        }
        /* ----- Operators ----- */
        //Swap function
        void friend swap(DSvector& first, DSvector& second) {
            using std::swap;

            swap(first.length, second.length);
            swap(first.max_size, second.max_size);
            swap(first.arr, second.arr);
        }
        //Assignment operator
        DSvector<T>& operator= (DSvector<T> v) {
            swap(*this, v);

            return *this;
        }
        bool operator==(const DSvector<T> &v) {
            if(size() != v.size()) {
                return false;
            }
            for(int i=0;i<size();i++) {
                if(get(i) != v.get(i)) {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const DSvector<T> &v) {
            return !(*this==v);
        }
        // << operator
        friend ostream& operator<<(ostream& os, const DSvector& dsv) {
            os << "<";

            for(int i=0;i<dsv.length;i++) {
                os << dsv.arr[i] << " ";
            }

            os << ">" << endl;
            

            return os;
        }

        /* ----- Other Functionality ----- */
        //Expand the size of the vector
        void resize() {
                max_size*=2;
                T* temp = new T[max_size];
                for(int i=0;i<length;i++) {
                    temp[i] = arr[i];
                }
                delete [] arr;
                arr = temp;
        }
        //Add item to the end of the vector
        void add(const T &item) {
            if(length+1==max_size) {
                resize();
            }

            arr[length] = item;
            length++;
        }
        //Add item to the vector at index
        void add(const T &item, int index) {
            if(index>length+1)
                return;
            if(length+1==max_size) {
                resize();
            }

            for(int i=length;i>index;i--) {
                arr[i] = arr[i-1];
            }
            arr[index] = item;
            length++;
        }
        //Overwrite the element in the vector at the given index
        void remove(int index) {
            if(index>=length || index<0)
                return;
            if(length == 1) {
                length = 0;
            } else {
                for(int i=index;i<length-1;i++)
                    arr[i] = arr[i+1];
            }
        }
        //Get item at the ith index of the vector
        T get(int i) const{
            return arr[i];
        }
        //Get item at the ith index of the vector
        T& operator[] (int index) const {
            return arr[index];
        }
        int size() const {return length;}
        bool isEmpty() { return length==0;}
        bool contains(T value) {
            for(int i=0;i<length;i++) {
                if(get(i) == value) {
                    return true;
                }
            }
            return false;
        }
};
#endif
