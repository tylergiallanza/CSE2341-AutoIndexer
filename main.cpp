#include <iostream>
#include <fstream>
#include "DSstring.h"
#include "DSvector.h"
#include "DSRBtree.h"
#include "tests.hpp"

DSstring* splitIntoWordsAndPhrases(DSstring* str, int& numWords) {
    return str;
}

void readInFile(const char* inPath) {
    ifstream inFile(inPath);
    int line = 0;
    int currentPage = 0;
    DSstring* str;
    DSRBtree<DSstring, int> tree;
    //max of 80 chars per line
    char A[80];

    //Read each line of the manuscript file
    while(inFile.getline(A,80)) {
        str = new DSstring(A);
        
        //Check if the current line is a page number
        if(str->charAt(0) == '<') {
            currentPage = str->substring(1,str->size()-1).toInt();
            if(currentPage == -1) {
                return;
            }
        } else {
            //Break the line into words and phrases
            int lineLength = 0;
            DSstring* lineArray = splitIntoWordsAndPhrases(str, lineLength);
            //Store each word or phrase into the tree
            for(int index=0;index<lineLength;index++) {
                tree.storeKeyValue(lineArray[index], currentPage);
            }
        }

        line++;

        delete str;
    }
    inFile.close();
    inFile.clear();

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
