#include "stdafx.h"
#include "CppUnitTest.h"

#include <Util/Util.h>
#include <Util/ranges.h>

#include <math/chinese_remainder_theorem.h>
#include <math/primes.h>

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
    };
}