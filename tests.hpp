#ifndef CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#endif


#include <cstring>
#include "DSstring.h"
#include "DSvector.h"
//#include "DSlinkedList.h"

TEST_CASE("DSstring class", "[string]"){

    DSstring s[10];
    s[0] = DSstring("testDSstring");
    s[1] = DSstring("a test string");
    s[2] = DSstring("");
    s[3] = DSstring("THIS IS AN UPPERCASE STRING");
    s[4] = DSstring("this is an uppercase string");
    s[5] = DSstring("\n");
    s[6] = DSstring("");
    s[7] = DSstring("  split  split  split  ");
    s[8] = DSstring("                          ");
    s[9] = DSstring("testDSstring");

    SECTION("Equality operators"){
        REQUIRE(s[0] == DSstring("testDSstring"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Assignment operators"){
        DSstring str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = DSstring("testDSstring");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = DSstring("\n");
        REQUIRE(str == s[5]);
    }

    SECTION("Addition operator"){
        REQUIRE(DSstring("testDSstringtestDSstring") == s[0]+s[9]);
        REQUIRE(s[6] + s[6] == "");
        REQUIRE(s[5] + s[6] == DSstring("\n"));
        REQUIRE(s[0] + s[1] + s[2] == "testDSstringa test string");
    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[9][-1] == 'g');
        REQUIRE(s[3][-3] == 'I');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
    }

    SECTION("Size function"){
        REQUIRE(s[9].size() == 12);
        REQUIRE(s[2].size() == 0);
        REQUIRE(s[8].size() == 26);
        REQUIRE(s[3].size() == 27);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testD");
        REQUIRE(s[1].substring(-6, -1) == "tring");
        REQUIRE(s[9].substring(0, -3) == "testDSstri");
        REQUIRE(s[9].substring(0, -1) == s[9]);
        REQUIRE(s[4].substring(0, 4) == "this");
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].c_str(), "testDSstring") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

}

TEST_CASE("DSvector class", "[vector]") {


    DSvector<int> ll1;
    DSvector<int> ll2;
    DSvector<int> ll3;

    ll1.add(1);
    ll1.add(2);
    ll2.add(0);

    
    SECTION("Equality operators"){
        DSvector<int> temp;
        temp.add(1);
        temp.add(2);
        REQUIRE(ll1 == temp);
        REQUIRE(temp == ll1);
        REQUIRE(temp != ll2);
        REQUIRE(temp != ll3);
    }
    
    SECTION("Assignment operators"){
        DSvector<int> test;
        test = ll1;
        REQUIRE(test == ll1);
        test.add(3);
        REQUIRE(test != ll1);
    }
    SECTION("Contains method"){
        REQUIRE(ll1.contains(2));
        REQUIRE(ll2.contains(0));
        REQUIRE(!ll2.contains(2));
        REQUIRE(!ll3.contains(2));
    }
    

}
