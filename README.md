# What nfiftest?

nfiftest (Not Fancy Intellisence Friendly test) is header-only, less macro using, somewhat verbose test library based on C++11.

Concept and API is similar to [Catch2](https://github.com/catchorg/Catch2), but this is more primitive and you nedd to write more ugly code.
The reward is less macro. It's much more intellisence friendly (That's all I need!).

### Instlation

Grap nfiftest.hpp and include it.

### example

I think just skim sample is enough for most of C++ programmer (Especially if you know Catch2).

[sample_main.cpp](./sample_main.cpp)


## Basic Concept

- test case
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

### REQUIRE

REQUIRE is just put expression which should be true.

```
    REQUIRE(3+5 == 8);
```

This use macro. This is the only place where macro is used.

### Not supported

- No multiple file test (At least not yet)
- No command line handling
- No fancy output
