#include <iostream>
#include "AutoIndexer.h"
#include "tests.hpp"

using namespace std;



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

        //Run the auto indexer and write to out file
        AutoIndexer ai(argv[1]);
        ai.writeToFile(argv[2]);

        //Output total runtime
        t = clock() - t;
        cout << "Ran in " << t/(double)CLOCKS_PER_SEC << " seconds" << endl;
    }
}
