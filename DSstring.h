#ifndef DS_STRING_H
#define DS_STRING_H

#include <iostream>
#include "DSvector.h"

class DSstring {
    private:
        char* cstring;
    public:
        int length;
        int size() const;
        //Swap
        friend void swap(DSstring& first, DSstring& second);
        //Constructors
        DSstring(char* cstringIn);
        ~DSstring();
        DSstring(const DSstring& str);
        DSstring(int i);
        DSstring();
        //Operators
        friend ostream& operator<<(ostream& os, const DSstring& dss);
        DSstring& operator= (DSstring str);
        DSstring operator+ (const DSstring &str1);
        DSstring operator+ (int i);
        bool operator> (const DSstring &str);
        bool operator< (const DSstring &str);
        bool operator== (const DSstring &other);
        char& operator[] (int index) const;
        //Other functionality
        char charAt(int index) const;
        char* c_str();
        DSstring substring(int start, int end);
        DSstring lower();
        DSstring* splitIntoWords(int& numWords);
        DSstring trimPunct();
        int toInt();
};
#endif
