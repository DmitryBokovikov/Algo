#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace math_ns
{
    ll bin_pow_mod(ll a, ll n, ll m)
    {
	if (a == 0)
	    return 0;
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

    // Euler's theorem 
    ll inverse_element(ll a, ll p)
    {
	return bin_pow_mod(a, p - 2, p);
    }

    ll euclidean_algorithm_gcd(ll a, ll b)
    {
	return a == b ? a : (a > b ? euclidean_algorithm_gcd(a % b, b) : euclidean_algorithm_gcd(a, b % a));
    }

    std::pair<ll, ll> extended_euclidean_algorithm_gcd(ll a, ll b)
    {
	if (a == 0)
	    return std::pair(0, 1);

	auto[x, y] = extended_euclidean_algorithm_gcd(b % a, a);
	return std::pair(y - (b / a) * x, x);
    }

    ll inverse_element_euclid(ll a, ll p)
    {
	// gcd(a, p) = 1 = x * a + y * p = x * a mod p < - > 1 / a = x mod p
	auto[x, y] = extended_euclidean_algorithm_gcd(a, p);
	return x;
    }

    /*
    x = ri mod ai
    ...
    x = rn mod an
    */
    ll chinese_remainder_theorem(const std::vector<ll>& a, const std::vector<ll> r)
    {
	const ll M = range_ns::reduce(a, ll(1), std::multiplies<ll>());
	ll ans = 0;
	for (ll i : range_ns::xrange(size(a)))
	{
	    const ll m = M / a[i];
	    ans = (ans + r[i] * m * inverse_element_euclid(m, a[i])) % M;
	}
	return ans;
    }
}
