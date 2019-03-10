#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace sort_ns
{
    template <class Container = std::vector<ll>>
    void quick_sort(Container& io_container)
    {
	using it_t = Container::iterator;
	function<void(it_t, it_t)> quick_sort_impl;
	quick_sort_impl = [&quick_sort_impl](it_t it_beg, it_t it_end)
	{
	    if (it_end - it_beg <= 1)
		return;

	    auto it_pivot = it_beg + (it_end - it_beg) / 2;
	    auto it_bigger = std::partition(it_beg, it_end, [pivot_value = *it_pivot](const auto& val) { return val <= pivot_value; });
	    auto it_equal = std::partition(it_beg, it_bigger, [pivot_value = *it_pivot](const auto& val) { return val < pivot_value; });
	    quick_sort_impl(it_beg, it_equal);
	    quick_sort_impl(it_bigger, it_end);
	};

	quick_sort_impl(begin(io_container), end(io_container));
    }
}