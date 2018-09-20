#pragma once

#include "SegmentTree.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>

namespace algo_ns
{
    template <class RAIterator>
    void bubble_sort(RAIterator itBeg, RAIterator itEnd)
    {
	for (auto it = itBeg; it < itEnd; ++it)
	    for (auto itInt = itBeg + 1; itInt < itEnd - (it - itBeg); ++itInt)
		if (*itInt < *(itInt - 1))
		    std::iter_swap(itInt, itInt - 1);
    }

    template <class RAIterator>
    void selection_sort(RAIterator itBeg, RAIterator itEnd)
    {
	for (auto it = itBeg; it < itEnd; ++it)
	    std::iter_swap(it, std::min_element(it, itEnd));
    }

    template <class RAIterator>
    void selection_sort_fast(RAIterator itBeg, RAIterator itEnd)
    {
	using valueT = typename std::iterator_traits<RAIterator>::value_type;
	segment_tree_ns::min_segment_tree<valueT> min_tree(std::vector<valueT>(itBeg, itEnd));

	size_t last = itEnd - itBeg - 1;
	for (auto it = itBeg; it < itEnd; ++it)
	{
	    size_t pos = it - itBeg;
	    auto min_value = min_tree.get_value(pos, last);
	    // use binary search to find index of min element in segment tree
	    size_t left = pos;
	    size_t right = last;
	    while (left != right)
	    {
		size_t middle = (left + right) / 2;
		if (min_tree.get_value(left, middle) == min_value)
		    right = middle;
		else
		    left = middle + 1;
	    }

	    size_t found_pos = left;
	    min_tree.update(found_pos, *it);
	    std::iter_swap(it, itBeg + found_pos);
	}	    
    }

    template <class RAIterator>
    void quick_sort(RAIterator itBeg, RAIterator itEnd)
    {
	if (itEnd - itBeg <= 1)
	    return;

	auto pivot = *(itBeg + (itEnd - itBeg) / 2);
	auto itGreater = std::partition(itBeg, itEnd, [pivot](auto val) { return val <= pivot; });
	auto itEqual = std::partition(itBeg, itGreater, [pivot](auto val) { return val < pivot; });
	quick_sort(itBeg, itEqual);
	quick_sort(itGreater, itEnd);
    }

    template <class RAIterator>
    void merge(RAIterator itBeg, RAIterator itMiddle, RAIterator itEnd)
    {
	auto itLeft = itBeg, itRight = itMiddle;
	using valueT = typename std::iterator_traits<RAIterator>::value_type;
	std::vector<valueT> merged;
	merged.reserve(itEnd - itBeg);
	while (itLeft < itMiddle && itRight < itEnd)
	    merged.push_back(*itLeft < *itRight ? *itLeft++ : *itRight++);

	std::copy(itLeft, itMiddle, std::back_inserter(merged));
	std::copy(itRight, itEnd, std::back_inserter(merged));
	std::copy(merged.begin(), merged.end(), itBeg);
    }

    template <class RAIterator>
    void merge_sort(RAIterator itBeg, RAIterator itEnd)
    {
	if (itEnd - itBeg <= 1)
	    return;

	auto itMiddle = itBeg + (itEnd - itBeg) / 2;
	merge_sort(itBeg, itMiddle);
	merge_sort(itMiddle, itEnd);
	merge(itBeg, itMiddle, itEnd);
    }

    template <class RAIterator>
    void insertion_sort(RAIterator itBeg, RAIterator itEnd)
    {
	for (auto it = itBeg + 1; it < itEnd; ++it)
	{
	    auto itInsert = std::upper_bound(itBeg, it, *it);
	    // same effect as std::rotate(itInsert, it, it + 1); but faster
	    auto val = *it;
	    std::copy_backward(itInsert, it, it + 1);
	    *itInsert = val;	    
	}
    }
}
