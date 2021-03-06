#include "DSstring.h"
#include <algorithm>
#include <stdio.h>

/*DSstring Class - Tyler Giallanza
 * A custom implementation of the std::string class.
 *
 * Contains basic text manipulation functions.
*/

/* ----- Constructors ----- */
//Primary constructor - take a cstring
DSstring::DSstring(char* cstringIn) {
    //Get length of input cstring
    length=0;
    while(cstringIn[length] != '\0') {
        length++;
    }
    
    //Plus 1 for the null terminator
    cstring = new char[length+1];
    for(int i=0;i<length;i++) {
        cstring[i] = cstringIn[i];
    }
    cstring[length] = 0;
}

//Int constructor - take an int
DSstring::DSstring(int i) {
    char cstringIn[12];
    sprintf(cstringIn, "%d", i);

    //Get length of input cstring
    length=0;
    while(cstringIn[length] != '\0') {
        length++;
    }
    
    //Plus 1 for the null terminator
    cstring = new char[length+1];
    for(int i=0;i<length;i++) {
        cstring[i] = cstringIn[i];
    }
    cstring[length] = 0;
}

//Deconstructor
DSstring::~DSstring() {
    delete [] cstring;
}

//Copy constructor
DSstring::DSstring(const DSstring & str) {
    length = str.length;
    cstring = new char[str.length + 1];
    int index = 0;
    while (str.cstring[index]) {
        cstring[index] = str.cstring[index];
        index++;
    }
    cstring[index] = 0;
}

//Default constructor - unused
DSstring::DSstring() {
    cstring = NULL;
    length = 0;
}


/* ----- Operators ----- */

//Assignment operator
DSstring& DSstring::operator= (DSstring str) {
    swap(*this, str);

    return *this;
}


//Equality operator
bool DSstring::operator== (const DSstring& other) {
    if(other.length != length) {
        return false;
    }
    for(int i=0;i<length;i++) {
        if(cstring[i] != other.cstring[i]) {
            return false;
        }
    }

    return true;
}


//[] operator (same functionality as charAt)
char& DSstring::operator[] (int index) const {
    if(length == 0 || index>=length) {
        static char s;
        s = 0;
        return s;
    }
    if(index < 0) {
        index = length+index;
    }

    return cstring[index];
}


// > operator
bool DSstring::operator> (const DSstring &str) {
    for(int i=0;i<min(length,str.size());i++) {
        if(charAt(i)>str[i]) {
            return true;
        }
        if(str[i]>charAt(i)) {
            return false;
        }
    }
    //If they have the same prefix, return the longer one
    return length>=str.size();
}
// < operator
bool DSstring::operator< (const DSstring &str) {
    return !(*this>str || *this==str);
}

//+ operator
DSstring DSstring::operator+ (const DSstring &str) {
    int len = length+str.size();
    char temp[len+1];

    for(int i=0;i<len;i++) {
        if(i<length) {
            temp[i] = charAt(i);
        } else {
            temp[i] = str[i-length];
        }
    }

    temp[len] = 0;

    DSstring dstemp(temp);
    return dstemp;
}

//+ operator for int
DSstring DSstring::operator+ (int i) {
    DSstring iString(i);
    return *this+iString;
}

/* ----- Other Functionality ----- */

//Substring starting at start and ending right before end
DSstring DSstring::substring(int start, int end) {
    //Catch negative start and end indices
    if(start < 0) {
        start = length + start + 1;
    }
    if(end < 0) {
        end = length + end + 1;
    }
    char temp[end-start+1];
    for(int i=0;i<end-start;i++) {
        temp[i] = charAt(i+start);
    }

    //Null terminator
    temp[end-start] = '\0';

    DSstring dstemp(temp);
    return dstemp;
}

//Get the lowercase version of the string
DSstring DSstring::lower() {
    char temp[length+1];
    for(int i=0;i<length;i++) {
        temp[i] = tolower(cstring[i]);
    }

    //Null terminator
    temp[length] = '\0';

    DSstring dstemp(temp);
    return dstemp;
}


//Get the underlying cstring
char* DSstring::c_str() {
    return cstring;
}


//Remove whitespace and punctuation from the start and end of a word
DSstring DSstring::trimPunct() {
    if(length == 0)
        return *this;


    int i = 0;
    while(charAt(i) == ' ' || charAt(i) == '.' || charAt(i) == ';' || charAt(i) == ':' || charAt(i) == '-' || charAt(i) == '!' || charAt(i) == '?' || charAt(i) == ',') {
        i++;
    }

    int j = 0;
    while(charAt(length-j-1) == ' ' || charAt(length-j-1) == '.' || charAt(length-j-1) == ';' || charAt(length-j-1) == ':' || charAt(length-j-1) == '-'|| charAt(length-j-1) == '!'|| charAt(length-j-1) == '?'|| charAt(length-j-1) == ',') {
        j++;
    }

    if(i+j >= length) {
        char newChar[1];
        newChar[0] = '\0';
        DSstring temp(newChar);
        return temp;
    } else {
        char newChar[length-i-j+1];
        for(int k=i;k<length-j;k++) {
            newChar[k-i] = charAt(k);
        }
        newChar[length-i-j] = '\0';
        DSstring temp(newChar);
        return temp;
    }

}

//Split a string of words on any number of spaces, storing the number
//of words into numWords
DSstring* DSstring::splitIntoWords(int& numWords) {
    int start = 0;

    //use to skip a block of multiple spaces
    bool spaceBlock = false;
    for(int i=0;i<length;i++) {
        //Line starts or ends with a space
        if( (charAt(i) == ' ') && (i==0 || i ==length-1))
            continue;

        //A word occurs when a new space block begins
        if(charAt(i) == ' ' && !spaceBlock) {
            spaceBlock = true;
            numWords++;
        //We're in a space block
        } else if(charAt(i) != ' ') {
            spaceBlock = false;
        }
    }


    //Store the words into lineArray
    DSstring* lineArray = new DSstring[numWords+1];

    numWords = 0;
    spaceBlock = false;
    for(int i=0;i<length;i++) {
        if(i != 0 && i != length-1 && charAt(i) == ' ' && !spaceBlock) {
            lineArray[numWords] = substring(start, i);
            numWords++;
            start = i+1;
        } else if(charAt(i) != ' ') {
            spaceBlock = false;
        }
    }
    lineArray[numWords] = substring(start, length);
    numWords++;

    return lineArray;
}

int DSstring::toInt() {
    return std::atoi(cstring);
}

//Get the length of the string
int DSstring::size() const {
    return length;
}

// Returns the character at the given position.
char DSstring::charAt(int index) const {
    if(length == 0 || index>=length) {
        static char s;
        s = 0;
        return s;
    }
    if(index < 0) {
        index = length+index;
    }

    return cstring[index];
}

/* ----- Friend Functions ----- */

//Swap method
void swap(DSstring& first, DSstring& second) {
    using std::swap;

    swap(first.length, second.length);
    swap(first.cstring, second.cstring);
}

//<< Operator
ostream& operator<< (ostream& os, const DSstring& dss) {
    os << dss.cstring;
    return os;
}
