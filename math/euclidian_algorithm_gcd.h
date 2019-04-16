#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace math_ns
{
    ll euclidean_algorithm_gcd(ll a, ll b)
    {
	return a == b ? a : (a > b ? euclidean_algorithm_gcd(a % b, b) : euclidean_algorithm_gcd(a, b % a));
    }

    // gcd(a, b) = x * a + y * b
    std::pair<ll, ll> extended_euclidean_algorithm_gcd(ll a, ll b)
    {
	if (a == 0)
	    return std::pair(0, 1);

	auto[x, y] = extended_euclidean_algorithm_gcd(b % a, a);
	return std::pair(y - (b / a) * x, x);
    }
}
