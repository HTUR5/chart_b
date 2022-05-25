#include "doctest.h"
#include <iostream>
#include <vector>

#include "OrgChart.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("ORGANIZTION") { 

    /*                  GOD
              DAD                   MOM
        DVIR       BATEL       HODAYA      RENANA  
     MOR    YAIR               ZOFIA
            HILA
            HILA
    */

    OrgChart org;
        
    //--case: adding son before creating root--
    CHECK_THROWS(org.add_sub("god", "dad")); 
    //-----------------------------------------

    CHECK_NOTHROW(org.add_root("dad"));
    

    //----------case: changing root------------
    CHECK_NOTHROW(org.add_root("god"));
    //-----------------------------------------

    CHECK_NOTHROW(org.add_sub("god", "dad"));
    CHECK_NOTHROW(org.add_sub("god", "mom"));
    CHECK_NOTHROW(org.add_sub("dad", "dvir"));
    CHECK_NOTHROW(org.add_sub("dad", "batEl"));
    CHECK_NOTHROW(org.add_sub("dvir", "mor"));
    CHECK_NOTHROW(org.add_sub("dvir", "yair"));
    CHECK_NOTHROW(org.add_sub("yair", "hila"));
    CHECK_NOTHROW(org.add_sub("mom", "hodaya"));
    CHECK_NOTHROW(org.add_sub("mom", "renana"));
    CHECK_NOTHROW(org.add_sub("hodaya", "zofia"));

    //----------add the same name--------------
    CHECK_NOTHROW(org.add_sub("hila", "hila"));
    //-----------------------------------------

    //------adding to dad who isnt exist-------
    CHECK_THROWS(org.add_sub("aa", "bb")); 
    //-----------------------------------------

    //----------case: not illegal names--------
    CHECK_THROWS(org.add_root(""));
    CHECK_THROWS((org.add_sub("\n", "\t")));
    //-----------------------------------------


        SUBCASE("LEVEL-ORDER"){
            std::vector<std::string> v = {"god", "dad", "mom", "dvir", "batEl", "hodaya", "renana", "mor", "yair", "zofia", "hila", "hila"};
            size_t i = 0;
            for(auto it = org.begin_level_order(); it != org.end_level_order(); ++it){
                CHECK_EQ(*it, v.at(i++));
            }
        }

        SUBCASE("REVERSE-ORDER"){
            std::vector<std::string> v = {"hila","hila","mor","yair","zofia","dvir","batEl","hodaya","renana","dad","mom","god"};
            size_t i = 0;
            for(auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
                CHECK_EQ(*it, v.at(i++));
            }
        }

        SUBCASE("PREORDER"){
            std::vector<std::string> v = {"god", "dad", "dvir", "mor", "yair", "hila", "hila", "batEl", "mom", "hodaya","zofia","renana"};
            size_t i = 0;
            for(auto it = org.begin_preorder(); it != org.end_preorder(); ++it){
                CHECK_EQ(*it, v.at(i++));
            }
        }
}


TEST_CASE("EMPTY TREE") {
    OrgChart org_empty;
    
    //case:level order
    CHECK_THROWS(org_empty.end_level_order());

    //case:reverse-order
    CHECK_THROWS(org_empty.begin_reverse_order());
    CHECK_THROWS(org_empty.reverse_order());

    //case:preorder
    CHECK_THROWS(org_empty.begin_preorder());
    CHECK_THROWS(org_empty.end_preorder());
}
