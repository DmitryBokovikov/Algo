#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace math_ns
{
    std::vector<ll> get_primes(ll n)
    {
	std::vector<ll> numbers(n + 1);
	std::iota(begin(numbers) + 2, end(numbers), 2);
	for (ll val : numbers)
	    if (val)
		for (ll j = 2 * val; j < util_ns::lsize(numbers); j += val)
		    numbers[j] = 0;
	range_ns::erase_remove_if(numbers, [](ll k) { return k == 0; });
	return numbers;
    }
}