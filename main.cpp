#include <iostream>
#include <fstream>
#include "DSstring.h"
#include "DSvector.h"
#include "DSRBtree.h"
#include "tests.hpp"
#include "DSsortedLinkedList.h"
#include "DSRBtree.h"

DSstring* splitIntoWordsAndPhrases(DSstring* str, int& numWords) {
    int numWordsTemp = 0;

    //Split the input line into words first
    DSstring* arrTemp = str->splitIntoWords(numWordsTemp);

    //Count the number of words/phrases
    bool inPhrase = false;
    for(int i=0;i<numWordsTemp;i++) {
        if(arrTemp[i][0] == '[') {
            //Started a phrase
            inPhrase = true;
        } else if(arrTemp[i][-1] == ']') {
            //Ended a phrase
            inPhrase = false;
            numWords++;
        } else if(!inPhrase) {
            //Added a non-phrase word
            numWords++;
        }
    }

    //Add words/phrases to a new array
    inPhrase = false;
    DSstring tempStr;
    DSstring* lineArray = new DSstring[numWords];
    //Concat words in a phrase with a space in between
    DSstring space(" ");
    numWords = 0;
    for(int i=0;i<numWordsTemp;i++) {
        if(arrTemp[i][0] == '[') {
            //Store first word of phrase into tempStr
            inPhrase = true;
            tempStr = arrTemp[i].substring(1,arrTemp[i].size());
        } else if(arrTemp[i][-1] == ']') {
            //Add last word of phrase to tempStr and store into array
            inPhrase = false;
            tempStr = tempStr + space + arrTemp[i].substring(0,-2);
            lineArray[numWords++] = tempStr;
        } else if(!inPhrase){
            //Add non-phrase word into array
            lineArray[numWords++] = arrTemp[i];
        } else {
            //Add word to phrase
            tempStr = tempStr + space + arrTemp[i];
        }
    }

    return lineArray;
}

void readInFile(const char* inPath) {
    ifstream inFile(inPath);
    int line = 0;
    int currentPage = 0;
    DSstring* str;
    DSRBtree<DSstring, int> tree("\0");
    //max of 80 chars per line
    char A[80];

    //Read each line of the manuscript file
    while(inFile.getline(A,80)) {
        str = new DSstring(A);
        
        //Check if the current line is a page number
        if(str->charAt(0) == '<') {
            currentPage = str->substring(1,str->size()-1).toInt();
            //cout << currentPage << endl;
            if(currentPage == -1) {
                inFile.close();
                inFile.clear();
                cout << tree << endl;
                delete str;
                return;
            }
        } else {
            //Break the line into words and phrases
            int lineLength = 0;
            //cout << *str << endl;
            DSstring* lineArray = splitIntoWordsAndPhrases(str, lineLength);
            //Store each word or phrase into the tree
            for(int index=0;index<lineLength;index++) {
                //cout << "    " << lineArray[index].trimPunct().lower() << endl;
                tree.storeKeyValue(lineArray[index].trimPunct().lower(), currentPage);
            }
        }

        line++;

        delete str;
    }

}

void writeOutFile(const char* outPath) {
    ofstream outFile(outPath);

    outFile.close();
    outFile.clear();

}
int main(int argc, const char * argv[]) {
    if(argc == 2 && strcmp(argv[1],"-t") == 0) {
        //Run the test code
        int result = Catch::Session().run();
        return (result < 0xff ? result : 0xff);
    } else if (argc != 3) {
        //Alert the user to impoper command line usage
        cout << "Automatic Indexer program - Tyler Giallanza" << endl;
        cout << "Usage: ./a.out [path to input file] [path to output file]" << endl;
    } else {
        //Run the program

        //Keep track of how long it takes to run
        clock_t t;
        t = clock();

        readInFile(argv[1]);

        //Output total runtime
        t = clock() - t;
        cout << "Ran in " << t/(double)CLOCKS_PER_SEC << " seconds" << endl;
    }
}
