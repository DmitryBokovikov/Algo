#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

#include "inverse_element.h"

namespace math_ns
{
    /*
    x = ri mod ai
    ...
    x = rn mod an
    */
    ll chinese_remainder_theorem(const std::vector<ll>& a, const std::vector<ll> r)
    {
	const ll M = range_ns::accumulate(a, ll(1), std::multiplies<ll>());
	ll ans = 0;
	for (ll i : range_ns::indices(size(a)))
	{
	    const ll m = M / a[i];
	    ans += (r[i] * m * inverse_element_euclid(m, a[i])) % M;
	}
	return ans % M;
    }
}
