#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace math_ns
{
    using factorization_map = std::unordered_map<ll, ll>;

    factorization_map factorize(ll n)
    {
	factorization_map res;
	ll sqrt_val = static_cast<ll>(sqrt(n));
	for (ll i = 2; i < sqrt_val; ++i)
	{
	    while (n % i == 0)
	    {
		++res[i];
		n /= i;
		sqrt_val = static_cast<ll>(sqrt(n));;
	    }
	}

	if (n != 1)
	    ++res[n];
	return res;
    }
}