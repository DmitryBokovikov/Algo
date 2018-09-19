// Algo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Util.h"
#include "SortsTester.h"
#include "SegmentTreeTester.h"

int main()
{
    //util_ns::safe_execute([]() { tests_ns::sorts_tester("out_sorts.txt").test_all(); });
    util_ns::safe_execute([]() { tests_ns::segment_tree_tester().test_all(); });
    return 0;
}

