// Algo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Util.h"
#include "SortsTester.h"
#include "SegmentTreeTester.h"

using namespace algo_ns::segment_tree_ns;
using namespace std;

int main()
{
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    max_segment_tree<int> seg_tree_max(vec);
    cout << seg_tree_max.get_value(2, 5) << "\n";
    sum_segment_tree<int> seg_tree_sum(vec);
    cout << seg_tree_sum.get_value(2, 5) << "\n";

    return 0;
}

