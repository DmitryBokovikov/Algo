#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace sort_ns
{
    template <class Container = std::vector<ll>>
    void bubble_sort(Container& io_container)
    {
	for (ll i : xrange(size(io_container)))
	    for (ll j : xrange(1, size(io_container) - i))
		if (io_container[j - 1] > io_container[j])
		    std::swap(io_container[j - 1], io_container[j]);	
    }

    template <class Container = std::vector<ll>>
    void selection_sort(Container& io_container)
    {
	for (auto it = begin(io_container); it != end(io_container); ++it)
	    std::iter_swap(it, std::min_element(it, end(io_container)));
    }

    // almost the same as bubble
    template <class Container = std::vector<ll>>
    void dwarf_sort(Container& io_container)
    {
	ll i = 0;
	while (i < lsize(io_container))
	{
	    if (i > 0 && io_container[i - 1] > io_container[i])
	    {
		std::swap(io_container[i], io_container[i - 1]);
		--i;
	    }
	    else
	    {
		++i;
	    }
	}
    }

    template <class Container = std::vector<ll>>
    void insertion_sort(Container& io_container)
    {
	for (auto it = begin(io_container); it != end(io_container); ++it)
	{
	    auto it_insert = std::upper_bound(begin(io_container), it, *it);
	    std::rotate(it_insert, it, it + 1);
	}
    }
}
