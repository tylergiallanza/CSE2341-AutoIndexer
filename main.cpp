#include <iostream>
#include <fstream>
#include "DSstring.h"
#include "DSvector.h"
#include "tests.hpp"

int main(int argc, const char * argv[]) {
    if(argc == 2 && strcmp(argv[1],"-t") == 0) {
        //Run the test code
        int result = Catch::Session().run();
        return (result < 0xff ? result : 0xff);
    } else if (argc != 4) {
        //Alert the user to impoper command line usage
        cout << "Spell Checker program - Tyler Giallanza" << endl;
        cout << "Usage: ./a.out [path to dictionary file] [path to manuscript file] [path to output file]" << endl;
    } else {
        //Run the program

        //Keep track of how long it takes to run
        clock_t t;
        t = clock();

        //Output total runtime
        t = clock() - t;
        cout << "Ran in " << t/(double)CLOCKS_PER_SEC << " seconds" << endl;
    }
}
