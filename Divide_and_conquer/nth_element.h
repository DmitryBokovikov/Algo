#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace
{
    template<class Container = std::vector<ll>, class pivot_func_t>
    typename Container::value_type nth_element_with_pivot_func(Container& io_container, int i_idx, pivot_func_t i_pivot_func)
    {
	using it_t = Container::iterator;
	using value_t = Container::value_type;
	std::function<value_t(it_t, it_t, int)> nth_element_impl;
	nth_element_impl = [&i_pivot_func, &nth_element_impl](it_t it_beg, it_t it_end, int i)
	{
	    if (it_end - it_beg <= 1)
		return *it_beg;
	    auto pivot = i_pivot_func(it_beg, it_end);
	    auto it_greater = std::partition(it_beg, it_end, [&pivot](const auto& value) { return value <= pivot; });
	    auto it_equal = std::partition(it_beg, it_greater, [&pivot](const auto& value) { return value < pivot; });
	    if (it_beg + i >= it_greater)
		return nth_element_impl(it_greater, it_end, static_cast<int>(it_beg + i - it_greater));
	    else if (it_beg + i < it_equal)
		return nth_element_impl(it_beg, it_equal, i);
	    else
		return *it_equal;
	};

	return nth_element_impl(begin(io_container), end(io_container), i_idx);
    }
}

namespace divide_and_conquer_ns
{
    template<class Container = std::vector<ll>>
    typename Container::value_type nth_element(Container& io_container, int i_idx)
    {
	using cit_t = Container::const_iterator;
	auto simple_get_pivot = [](cit_t it_beg, cit_t it_end)
	{
	    return *(it_beg + (it_end - it_beg) / 2);
	};
	return nth_element_with_pivot_func(io_container, i_idx, simple_get_pivot);
    }

    template<class Container = std::vector<ll>>
    typename Container::value_type nth_element_linear(Container& io_container, int i_idx)
    {
	using it_t = Container::iterator;
	std::function<Container::value_type(it_t, it_t)> median_get_pivot;
	median_get_pivot = [&median_get_pivot](it_t it_beg, it_t it_end)
	{
	    if (it_end - it_beg == 1)
		return *it_beg;
	    int constexpr ELEMENTS_IN_GROUP = 5;
	    const int groups_count = util_ns::ceil_div(static_cast<int>(it_end - it_beg), ELEMENTS_IN_GROUP);
	    Container medians;
	    for (ll i : range_ns::indices(groups_count))
	    {
		auto it_current_group_end = std::min(it_beg + ELEMENTS_IN_GROUP * (i + 1), it_end);
		auto it_current_group_beg = it_beg + ELEMENTS_IN_GROUP * i;
		std::sort(it_current_group_beg, it_current_group_end);
		medians.emplace_back(*(it_current_group_beg + (it_current_group_end - it_current_group_beg) / 2));
	    }
		
	    return median_get_pivot(begin(medians), end(medians));
	};
	return nth_element_with_pivot_func(io_container, i_idx, median_get_pivot);
    }
}
