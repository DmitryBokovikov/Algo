#include "stdafx.h"
#include "CppUnitTest.h"

#include <Util/Util.h>
#include <Util/ranges.h>

#include <math/chinese_remainder_theorem.h>
#include <math/primes.h>
#include <math/euclidian_algorithm_gcd.h>
#include <math/bin_pow_mod.h>
#include <math/inverse_element.h>
#include <math/factorize.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math_ns::tests
{	
    using namespace util_ns;
    using namespace range_ns;

    TEST_CLASS(math_tests)
    {
    public:

	// Google Code Jam 2019 Golf Gophers (https://codingcompetitions.withgoogle.com/codejam/round/0000000000051635/0000000000104f1a)
	TEST_METHOD(chinese_remainder_theorem_tests)
	{
	    constexpr ll test_cases_count = 1'000;
	    for (ll i : xrange(test_cases_count))
	    {
		ll x = get_random(1, 1'000'000);
		auto a = get_primes(100);
		random_permutate(a);
		a.resize(9); // to avoid overflow of ll value (10^18)
		std::vector<ll> r;
		for (ll mod : a)
		    r.push_back(x % mod);
		Assert::IsTrue(x == chinese_remainder_theorem(a, r), L"Wrong answer");
	    }
	}

	TEST_METHOD(gcd_tests)
	{
	    constexpr ll test_cases_count = 1'000;
	    for (ll i : xrange(test_cases_count))
	    {
		ll x = get_random(1, 1'000'000);
		ll y = get_random(1, 1'000'000);
		auto[a, b] = extended_euclidean_algorithm_gcd(x, y);
		Assert::IsTrue(euclidean_algorithm_gcd(x, y) == std::gcd(x, y));
		Assert::IsTrue(a * x + b * y == std::gcd(x, y));
	    }
	}

	TEST_METHOD(bin_pow_mod_tests)
	{
	    constexpr ll test_cases_count = 1'000;
	    for (ll i : xrange(test_cases_count))
	    {
		ll x = get_random(1, 1'000'000);
		ll n = get_random(1, 10'000);
		ll y = get_random(1, 1'000'000);
		ll ans = 1;
		for (ll i : xrange(n))
		    ans = (ans * x) % y;
		Assert::IsTrue(ans == bin_pow_mod(x, n, y));
	    }
	}

	TEST_METHOD(inverse_element_tests)
	{
	    const ll mod = static_cast<ll>(pow(10, 9)) + 7;
	    constexpr ll test_cases_count = 1'000;
	    for (ll i : xrange(test_cases_count))
	    {
		ll x = get_random(1, 1'000'000);
		ll inverse_euclid = inverse_element_euclid(x, mod);
		ll inverse_euler = inverse_element(x, mod);
		Assert::IsTrue(inverse_euclid == inverse_euler);
		Assert::IsTrue(x * inverse_euclid % mod == 1);
	    }
	}

	TEST_METHOD(factorize_tests)
	{
	    constexpr ll test_cases_count = 1'000;
	    for (ll i : xrange(test_cases_count))
	    {
		ll x = get_random(1, 10'000'000);
		auto fact_map = factorize(x);
		for (auto[val, degree] : fact_map)
		{
		    for (ll i : xrange(degree))
		    {
			Assert::IsTrue(x % val == 0);
			x /= val;
		    }
		}
		Assert::IsTrue(x == 1);
	    }

	    auto fact_map = factorize(1);
	    Assert::IsTrue(empty(fact_map));
	    std::vector<std::pair<ll, ll>> val_degrees = { {2, 5}, {3, 4}, {1000000007, 1}, { 7, 1 } };
	    fact_map = factorize(reduce(val_degrees, ll(1), [](ll sum, const auto& p) 
	    {
		auto[val, degree] = p;
		return sum * static_cast<ll>(pow(val, degree));
	    }));
	    Assert::IsTrue(size(fact_map) == size(val_degrees));
	    for (auto[val, degree] : val_degrees)
		Assert::IsTrue(fact_map[val] == degree);    
	}
    };
}