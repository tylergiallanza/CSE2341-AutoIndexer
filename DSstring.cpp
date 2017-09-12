#include "DSstring.h"
#include <algorithm>

/*DSstring Class - Tyler Giallanza
 * A custom implementation of the std::string class.
 *
 * Contains basic text manipulation functions.
*/

using namespace std;

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

// Returns the character at the given position.
char DSstring::charAt(int loc) const {
    return cstring[loc];

}

//Assignment operator
DSstring& DSstring::operator= (const DSstring &str) {
    length = str.length;
    cstring = new char[length + 1];
    int index = 0;
    while (str.cstring[index]) {
        cstring[index] = str.cstring[index];
        index++;
    }
    cstring[index] = 0;


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

/* Dynamic programming implementation of the Levenshtein Distance algorithm.
 * For all i and j, d[i][j] holds the Levenshtein distance between the first
 * i characters of *this and the first j characters of other.
*/
int DSstring::levDist(const DSstring& other) {
    int n = length;
    int m = other.length;
    int i,j,cost,temp;

    //Initialize values - that way if the other string is length 0, the length
    //of the current prefix is the edit distance
    for(i=0;i<=n;i++) {
        d[i][0] = i;
    }
    for(j=0;j<=m;j++) {
        d[0][j] = j;
    }

    //Calculate the distance between the first i and j characters and store it
    //at d[i][j]
    for(i=1;i<=n;i++) {
        for(j=1;j<=m;j++) {
            if(charAt(i-1) == other.charAt(j-1))  {
                cost = 0;
            } else {
                cost = 1;
            }
            temp = min((d[i-1][j]+1),(d[i][j-1]+1));
            d[i][j] = min(temp,(d[i-1][j-1]+cost));
        }
    }

    return d[n][m];
}

//<< Operator
ostream& operator<< (ostream& os, const DSstring& dss) {
    os << dss.cstring;
    return os;
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


//Get the length of the string
int DSstring::size() const {
    return length;
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

DSstring DSstring::substring(int start, int end) {
    //Catch negative start and end indices
    if(start < 0) {
        start = length + start + 1;
    }
    if(end < 0) {
        end = length + end + 1;
    }
    char* temp = new char[end-start+1];
    for(int i=0;i<end-start;i++) {
        temp[i] = charAt(i+start);
    }

    //Null terminator
    temp[end-start] = '\0';

    DSstring* dstemp = new DSstring(temp);
    return *dstemp;
}


//Get the underlying cstring
char* DSstring::c_str() {
    return cstring;
}

//+ operator
DSstring& DSstring::operator+ (const DSstring &str) {
    int len = length+str.size();
    char* temp = new char[len+1];

    for(int i=0;i<len;i++) {
        if(i<length) {
            temp[i] = charAt(i);
        } else {
            temp[i] = str[i-length];
        }
    }

    temp[len] = 0;

    DSstring* dstemp = new DSstring(temp);
    return *dstemp;
}

//Remove whitespace and punctuation from the start and end of a word
DSstring& DSstring::trimPunct() {
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
        DSstring* temp = new DSstring(newChar);
        return *temp;
    } else {
        char newChar[length-i-j+1];
        for(int k=i;k<length-j;k++) {
            newChar[k-i] = charAt(k);
        }
        newChar[length-i-j] = '\0';
        DSstring* temp = new DSstring(newChar);
        return *temp;
    }

}

//Split a string of words on any number of spaces, storing the number
//of words into numWords
DSstring* DSstring::splitIntoWords(int& numWords) {
    DSstring* lineArray;
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
    lineArray = new DSstring[numWords+1];

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
