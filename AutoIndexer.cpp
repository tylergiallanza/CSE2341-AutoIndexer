#include "AutoIndexer.h"
#include <fstream>
#include "DSstring.h"
#include "DSvector.h"
#include "DSRBtree.h"
#include "DSsortedLinkedList.h"
#include "DSRBtree.h"

using namespace std;

AutoIndexer::AutoIndexer(const char* inPath) {
    inFilePath = inPath;
    tree = new DSRBtree<DSstring, int>("\0");
    readInFile();
}
//Write index results to the output file
void AutoIndexer::writeToFile(const char* outPath) {
    ofstream outFile(outPath);
    char currentChar = '\0';
    DSvector<DSRBnode<DSstring, int>* >* nodes = tree->inOrderTraverse();
    for(int i=0;i<nodes->size();i++)  {
        if(nodes->get(i)->key[0] != currentChar) {
            currentChar = nodes->get(i)->key[0];
            outFile << "[" << currentChar << "]" << endl;
        }

        bool indent = false;
        DSstring commaSpace(", ");
        DSstring* lineBuffer = new DSstring(": ");
        *lineBuffer = nodes->get(i)->key + *lineBuffer;
        for(int j=0;j<nodes->get(i)->values->size();j++) {
            if(indent) {
                delete lineBuffer;
                lineBuffer = new DSstring("    ");
                if(j==nodes->get(i)->values->size()-1)
                    *lineBuffer = *lineBuffer + nodes->get(i)->values->get(j);
                else
                    *lineBuffer = *lineBuffer + nodes->get(i)->values->get(j) + commaSpace;
                indent = false;
            } else {
                if(lineBuffer->size()+sizeInt(nodes->get(i)->values->get(j))+2 > 50) {
                    indent = true;
                    outFile << *lineBuffer << endl;
                    j--;
                    continue;
                }
                if(j==nodes->get(i)->values->size()-1)
                    *lineBuffer = *lineBuffer + nodes->get(i)->values->get(j);
                else
                    *lineBuffer = *lineBuffer + nodes->get(i)->values->get(j) + commaSpace;
            }
        }
        outFile << *lineBuffer << endl;
        delete lineBuffer;
    }

    delete nodes;

    outFile.close();
    outFile.clear();
}
//Destructor
AutoIndexer::~AutoIndexer() {
    delete tree;
}

//Store the input file into the tree
void AutoIndexer::readInFile() {
    ifstream inFile(inFilePath);
    int line = 0;
    int currentPage = 0;
    DSstring* str;
    //max of 80 chars per line
    char A[80];

    //Read each line of the manuscript file
    while(inFile.getline(A,80)) {
        str = new DSstring(A);
        
        //Check if the current line is a page number
        if(str->charAt(0) == '<') {
            currentPage = str->substring(1,str->size()-1).toInt();
            if(currentPage == -1) {
                inFile.close();
                inFile.clear();
                
                delete str;
                return;
            }
        } else {
            //Break the line into words and phrases
            int lineLength = 0;
            DSstring* lineArray = splitIntoWordsAndPhrases(str, lineLength);
            //Store each word or phrase into the tree
            for(int index=0;index<lineLength;index++) {
                tree->storeKeyValue(lineArray[index].trimPunct().lower(), currentPage);
            }

            delete [] lineArray;
        }

        line++;

        delete str;
    }
}

DSstring* AutoIndexer::splitIntoWordsAndPhrases(DSstring* str, int& numWords) {
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

    delete [] arrTemp;

    return lineArray;
}

int AutoIndexer::sizeInt(int i) {
    if(i==0) 
        return 1;

    int length = 0;

    if(i<0) {
        length=1;
        i*=-1;
    }

    while(i>0) {
        i/=10;
        length++;
    }
    return length;

}
