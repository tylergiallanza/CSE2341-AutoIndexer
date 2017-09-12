#ifndef DS_STRING_H
#define DS_STRING_H

#include <iostream>
#include "DSvector.h"
using namespace std;

class DSstring {
    private:
        char* cstring;
        int d[32][32];
        int recursiveLevDist(int i, int j, const DSstring& other);
    public:
        DSstring& trimPunct();
        int length;
        DSstring(char* cstringIn);
        ~DSstring();
        DSstring(const DSstring& str);
        DSstring();
        int levDist(const DSstring& other);
        int size() const;
        char charAt(int loc) const;
        char* c_str();
        friend ostream& operator<<(ostream& os, const DSstring& dss);
        DSstring& operator= (const DSstring &str);
        DSstring& operator+ (const DSstring &str1);
        bool operator> (const DSstring &str);
        bool operator== (const DSstring &other);
        char& operator[] (int index) const;
        DSstring substring(int start, int end);
        DSstring* splitIntoWords(int& numWords);
        int toInt();
};
#endif
