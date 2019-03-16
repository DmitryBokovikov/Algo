#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace sort_ns
{
    template<class Container = std::vector<ll>>
    void merge_sort(Container& io_container)
    {
	using it_t = Container::iterator;

	auto merge = [](it_t it_beg, it_t it_med, it_t it_end)
	{
	    std::vector<Container::value_type> tmp_container;
	    tmp_container.reserve(it_end - it_beg);
	    ll left_elements_count = it_med - it_beg, right_elements_count = it_end - it_med;
	    ll left_processed = 0, right_processed = 0;
	    while (left_processed != left_elements_count && right_processed != right_elements_count)
	    {
		if (*(it_beg + left_processed) < *(it_med + right_processed))
		{
		    tmp_container.emplace_back(*(it_beg + left_processed));
		    ++left_processed;
		}
		else
		{
		    tmp_container.emplace_back(*(it_med + right_processed));
		    ++right_processed;
		}
	    }

	    std::copy(it_beg + left_processed, it_med, std::back_inserter(tmp_container));
	    std::copy(it_med + right_processed, it_end, std::back_inserter(tmp_container));
	    std::copy(
		std::make_move_iterator(begin(tmp_container)),
		std::make_move_iterator(end(tmp_container)),
		it_beg);
	};

	std::function<void(it_t, it_t)> merge_sort_impl;
	merge_sort_impl = [&merge, &merge_sort_impl](it_t it_beg, it_t it_end)
	{
	    if (it_end - it_beg <= 1)
		return;

	    auto it_med = it_beg + (it_end - it_beg) / 2;
	    merge_sort_impl(it_beg, it_med);
	    merge_sort_impl(it_med, it_end);
	    merge(it_beg, it_med, it_end);
	};

	merge_sort_impl(begin(io_container), end(io_container));
    }
}
