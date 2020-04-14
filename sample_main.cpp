#include "nfiftest.hpp"


using namespace nfiftest;

std::vector<TestPair> test_cases = {
{"String Test", [] {
        auto target = std::string("abc");
        REQUIRE(target.size() == 3);

        if(SECTION("Empty string copy assign and size")) { SG g;
            target = "";
            REQUIRE(target.size() == 0);
        }
        if(SECTION("Add def")) { SG g;
            target = target+"def";
            REQUIRE(target == "abcdef");
            if(SECTION("Add another ghi")) { SG g;
                target = target+"ghi";
                REQUIRE(target == "abcdefghi");
                // fail on pupose for test.
                // REQUIRE(target == "hogehoge");
            }
        }
        if(SECTION("Add another xyz")) { SG g;
            target = target+"xyz";
            REQUIRE(target == "abcxyz");
        }

    }
},
{"Vector Test",
    []{
        std::vector<int> v;
        REQUIRE( v.size() == 0 );

        auto iter = find(v.begin(), v.end(), 2);
        REQUIRE(iter == v.end());

        if(SECTION("Add 1, 2, 3")) { SG g;
            v.push_back(1);
            v.push_back(2);
            v.push_back(3);
            REQUIRE(v.size() == 3);

            if(SECTION("Find 2 sould be success")) { SG g;
                auto iter = find(v.begin(), v.end(), 2);
                REQUIRE(iter != v.end());
            }
            if(SECTION("Find 5 should be fail")) { SG g;
                auto iter = find(v.begin(), v.end(), 5);
                REQUIRE(iter == v.end());
            }
        }
        if(SECTION( "Add 4, 5" )) { SG g;
            v.push_back(4);
            v.push_back(5);
            REQUIRE(v.size() == 2);

            if(SECTION("Find 2 sould be fail")) { SG g;
                auto iter = find(v.begin(), v.end(), 2);
                REQUIRE(iter == v.end());
            }
            if(SECTION("Find 5 should be success")) { SG g;
                auto iter = find(v.begin(), v.end(), 5);
                REQUIRE(iter != v.end());
            }

        }
    }
}
};

int main()
{
    RunTests(test_cases);
    return 0;
}