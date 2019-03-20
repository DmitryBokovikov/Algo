#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace divide_and_conquer_ns
{
    template <class Container = std::vector<ll>>
    ll count_inversions(Container& io_container)
    {
	using it_t = Container::iterator;

	auto merge = [](it_t it_beg, it_t it_med, it_t it_end)
	{
	    ll inversions_count = 0, left_processed = 0, right_processed = 0;
	    ll total_left_count = it_med - it_beg, total_right_count = it_end - it_med;
	    std::vector<Container::value_type> temp_container;
	    temp_container.reserve(it_end - it_beg);
	    while (left_processed != total_left_count && right_processed != total_right_count)
	    {
		if (*(it_beg + left_processed) < *(it_med + right_processed))
		{
		    temp_container.emplace_back(*(it_beg + left_processed));
		    ++left_processed;
		}
		else
		{
		    temp_container.emplace_back(*(it_med + right_processed));
		    ++right_processed;
		    inversions_count += (total_left_count - left_processed);
		}
	    }

	    std::copy(it_beg + left_processed, it_med, std::back_inserter(temp_container));
	    std::copy(it_med + right_processed, it_end, std::back_inserter(temp_container));
	    std::copy(
		std::make_move_iterator(begin(temp_container)),
		std::make_move_iterator(end(temp_container)),
		it_beg);

	    return inversions_count;
	};

	std::function<ll(it_t, it_t)> count_inversions_impl;
	count_inversions_impl = [&merge, &count_inversions_impl](it_t it_beg, it_t it_end) -> ll
	{
	    if (it_end - it_beg <= 1)
		return 0;
	    auto it_med = it_beg + (it_end - it_beg) / 2;
	    ll count_inversions_left = count_inversions_impl(it_beg, it_med);
	    ll count_inversions_right = count_inversions_impl(it_med, it_end);
	    return count_inversions_left + count_inversions_right + merge(it_beg, it_med, it_end);
	};

	return count_inversions_impl(begin(io_container), end(io_container));
    }
}
