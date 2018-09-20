// Algo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Util.h"
#include "SortsTester.h"
#include "SegmentTreeTester.h"

int main()
{
    auto test_func = []() { tests_ns::sorts_tester("out_sorts.txt").test_all(); };
    //auto test_func = []() { tests_ns::segment_tree_tester().test_all(); };
    //util_ns::safe_execute([]() {  });
    util_ns::safe_execute([test_func]()
    { 
	std::invoke(test_func);
	std::cout << "Success!\n";
    });
    return 0;
}

