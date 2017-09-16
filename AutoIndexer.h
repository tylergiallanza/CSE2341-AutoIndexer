#ifndef AUTO_INDEXER_H
#define AUTO_INDEXER_H

#include "DSstring.h"
#include "DSRBtree.h"

class AutoIndexer {
    private:
        const char* inFilePath;
        void readInFile();
        DSstring* splitIntoWordsAndPhrases(DSstring* str, int& numWords);
        int sizeInt(int i);
        DSRBtree<DSstring, int>* tree;
    public:
        AutoIndexer(const char* inPath);
        ~AutoIndexer();
        void writeToFile(const char* outPath);
};
#endif
