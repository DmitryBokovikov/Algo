#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace sort_ns
{
    template<class Container = std::vector<ll>>
    void radix_sort(Container& io_container)
    {
	constexpr ll iterations = sizeof(Container::value_type) * 8;
	for (ll i = 0; i < iterations; ++i)
	    range_ns::stable_partition(io_container, [j = (1 << i)](ll val) { return !(val & j); });
    }

    template<class Container = std::vector<ll>>
    void count_sort(Container& io_container)
    {
	using type_t = Container::value_type;
	std::vector<type_t> buckets(empty(io_container) ? 0 : *range_ns::max_element(io_container) + 1);
	for (type_t val : io_container)
	    ++buckets[val];
	ll j = 0;
	for (ll i : range_ns::xrange(lsize(buckets)))
	{
	    ll n = buckets[i];
	    while (n--)
		io_container[j++] = i;
	}
    }
}
