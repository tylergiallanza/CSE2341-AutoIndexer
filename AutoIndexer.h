#ifndef AUTO_INDEXER_H
#define AUTO_INDEXER_H

#include "DSstring.h"

class AutoIndexer {
    private:
        const char* inFilePath;
        void readInFile();
        DSstring* splitIntoWordsAndPhrases(DSstring* str, int& numWords);
        int sizeInt(int i);
    public:
        AutoIndexer(const char* inPath);
};
#endif
