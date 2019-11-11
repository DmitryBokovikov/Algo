#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace sort_ns
{
    template<class Container = std::vector<ll>>
    void merge_sort(Container& io_container)
    {
	using it_t = Container::iterator;

	std::function<void(it_t, it_t)> merge_sort_impl;
	merge_sort_impl = [&merge_sort_impl](it_t it_beg, it_t it_end)
	{
	    if (it_end - it_beg <= 1)
		return;

	    auto it_med = it_beg + (it_end - it_beg) / 2;
	    merge_sort_impl(it_beg, it_med);
	    merge_sort_impl(it_med, it_end);
	    std::inplace_merge(it_beg, it_med, it_end);
	};

	merge_sort_impl(begin(io_container), end(io_container));
    }
}
