#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

#include "euclidian_algorithm_gcd.h"
#include "bin_pow_mod.h"

namespace math_ns
{
    // Euler's theorem, suppose that is prime
    ll inverse_element(ll a, ll p)
    {
	return bin_pow_mod(a, p - 2, p);
    }

    ll inverse_element_euclid(ll a, ll p)
    {
	// gcd(a, p) = 1 = x * a + y * p = x * a mod p < - > 1 / a = x mod p
	auto[x, y] = extended_euclidean_algorithm_gcd(a, p);
	// x could be negative
	return (p + x) % p;
    }
}