#pragma once

#include <vector>
#include <algorithm>

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
}
