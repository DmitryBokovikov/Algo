#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace math_ns
{
    ll bin_pow_mod(ll a, ll n, ll m)
    {
	if (n == 0)
	    return 1;
	if (n % 2)
	{
	    return (a * bin_pow_mod(a, n - 1, m)) % m;
	}
	else
	{
	    const ll val = bin_pow_mod(a, n / 2, m);
	    return (val * val) % m;
	}
    }
}
