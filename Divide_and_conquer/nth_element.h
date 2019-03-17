#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace divide_and_conquer_ns
{
    template<class Container = std::vector<ll>>
    typename Container::value_type nth_element(Container& io_container, int idx)
    {
	using it_t = Container::iterator;
	using value_t = Container::value_type;
	std::function<value_t(it_t, it_t, int)> nth_element_impl;
	nth_element_impl = [&nth_element_impl](it_t it_beg, it_t it_end, int i)
	{
	    if (it_end - it_beg <= 1)
		return *it_beg;
	    auto pivot = *(it_beg + (it_end - it_beg) / 2);
	    auto it_greater = std::partition(it_beg, it_end, [&pivot](const auto& value) { return value <= pivot; });
	    auto it_equal = std::partition(it_beg, it_greater, [&pivot](const auto& value) { return value < pivot; });
	    if (it_beg + i >= it_greater)
		return nth_element_impl(it_greater, it_end, static_cast<int>(it_beg + i - it_greater));
	    else if (it_beg + i < it_equal)
		return nth_element_impl(it_beg, it_equal, i);
	    else
		return *it_equal;
	};

	return nth_element_impl(begin(io_container), end(io_container), idx);
    }
}
