#include "stdafx.h"
#include "CppUnitTest.h"

#include <Util/Util.h>
#include <Util/ranges.h>
#include <Dynamic_programming/max_segment.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace dp_ns::dynamic_programming_tests
{	
    using namespace util_ns;
    using namespace range_ns;

    std::vector<ll> get_random_vector(ll n)
    {
	auto vec1 = gen_data(n), vec2 = gen_data(n);
	for (ll i : indices(n))
	    vec1[i] *= (vec2[i] % 2 ? 1 : -1);
	return vec1;
    }

    TEST_CLASS(Dynamic_programming_tests)
    {
    public:
	TEST_METHOD(max_segment_tests)
	{
	    constexpr ll test_cases_count = 100;
	    auto get_max_segment_naive = [](const std::vector<ll> vec)
	    {
		auto sums = partial_sum(vec);
		const ll n = lsize(vec);
		ll ans = -INF;
		for (ll i : indices(n))
		    for (ll j : indices(i, n))
			ans = std::max(ans, sums[j] - (i == 0 ? 0 : sums[i - 1]));
		return ans;
	    };

	    for (ll i : indices(test_cases_count))
	    {
		auto vec = get_random_vector(1'000);
		Assert::IsTrue(get_max_segment_naive(vec) == find_max_segment(vec));
	    }
	}

	TEST_METHOD(max_submatrix_tests)
	{
	    auto gen_matrix = [](ll n, ll m)
	    {
		std::vector<std::vector<ll>> matrix(n);
		std::generate_n(begin(matrix), size(matrix), [&]() { return get_random_vector(m); });
		return matrix;
	    };

	    constexpr ll test_cases_count = 1'000;
	    for (ll i : indices(test_cases_count))
	    {
		const ll n = get_random(1, 60), m = get_random(1, 60);
		auto matrix = gen_matrix(n, m);
		ll val = max_submatrix(matrix), val_naive = max_submatrix_naive(matrix);
		Assert::IsTrue(val == val_naive);   
	    }
	}
    };
}
