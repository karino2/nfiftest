# What nfiftest?

nfiftest (Not Fancy Intellisence Friendly test) is header-only, less macro using, somewhat verbose test library based on C++11.

Concept and API is similar to [Catch2](https://github.com/catchorg/Catch2), but nfiftest is more primitive and you nedd to write more ugly code.
The reward is less macro. It's much more intellisence friendly (That's all I need!) and easier to step-execute.

### Instlation

Grap nfiftest.hpp and include it.

### Example

Just skim sample would be enough for most C++ programmers (Especially if you already know Catch2).

[sample_main.cpp](./sample_main.cpp)


## Basic Concept

- Test case
- SECION
- REQUIRE

REQUIRE and SECTION is somewhat similar to Catch2.
There are no auto registration now but you can write test with lambda.

There are no ASSERT or EXPECT. Just REQUIRE.

### Test case and run

Write testcase like this:

```
std::vector<nfiftest::TestPair> test_cases = {
    {"test name1", []{...}},
    {"test name2", []{...}}
};
```

No macro here.

Then run test like this.

```
    nifitest::RunTests(test_cases);
```

### Section

You can add section like following.

```
    if(SECTION("Some section name")) { SG g;
      ...
    }
```

There is naked `if` and you need to place SG (SectionGuard) object by hand.
No macro here.

`if` itself is semantically meaningless.
Please regard this whole line just as SECTION beginning.

### REQUIRE

REQUIRE is just put expression which should be true.

```
    REQUIRE(3+5 == 8);
```

This use macro. This is the only place where macro is used.

### Multiple test file

There is `_NFIFTEST_SUBTEST_` macro.
There must be only one include without this define, all other must be include with this symbol.
For example:

```
// file test2.cpp
#define _NFIFTEST_SUBTEST_
#include "nfiftest.hpp"

using namespace nfiftest;
static std::vector<TestPair> test_cases1 = {
...
};

void RegisterTest2(std::vector<TestPair>& testCases) {
    testCases.insert(testCases.end(), test_cases1.begin(), test_cases1.end());    
}



// file test1.cpp
#include "nfiftest.hpp"

using namespace nfiftest;
static std::vector<TestPair> test_cases1 = {
...
};

extern void RegisterTest2(std::vector<TestPair>& testCases);
int main() {
    std::vector<TestPair> test_cases;
    test_cases.insert(test_cases.end(), test_cases1.begin(), test_cases1.end());
    RegisterAllocatorTest( test_cases );

    RunTests(test_cases);
    return 0;
}
```

### Not supported

- No command line handling
- No fancy output

# Tips

When I used this library to real project, I found some tips.

### Redefine REQUIRE inside .cpp

Using REQUIRE outside of .cpp sometime makes code analysis slower.
At that time, just re-define REQUIRE.

```
#include "nfiftest.hpp"

#undef REQUIRE
#define REQUIRE(expr) if(!(expr)) throw nfiftest::assert_fail_error(__FILE__, __LINE__, #expr)
```

This is ridiculously effective.

### Split test cases

Sometime, long initializer list of test case makes code analysis slower.
At that time, split test case vector and merge it before RunTest.

```
std::vector<TestPair> test_cases1 = {
    {"test1", []{...}},
    {"test2", []{...}},
    ...
};

std::vector<TestPair> test_cases2 = {
    {"test2_1", []{...}},
    {"test2_2", []{...}},
    ...
};

int main()
{
    std::vector<TestPair> test_cases;
    test_cases.insert(test_cases.end(), test_cases1.begin(), test_cases1.end());
    test_cases.insert(test_cases.end(), test_cases2.begin(), test_cases2.end());

    RunTests(test_cases);
    return 0;
}
```

After splitting test cases, re-open file mitigate slow intellisence update.
