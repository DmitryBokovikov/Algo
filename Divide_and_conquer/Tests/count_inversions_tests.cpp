#include "stdafx.h"
#include "CppUnitTest.h"

#include <Divide_and_conquer/count_inversions.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace divide_and_conquer_ns::tests
{
    using namespace util_ns;

    auto naive_count_permutations = [](const std::vector<ll>& i_vec)
    {
	ll ans = 0;
	for (ll i : range_ns::xrange(lsize(i_vec)))
	    for (ll j : range_ns::xrange(i + 1, lsize(i_vec)))
		if (i_vec[j] < i_vec[i])
		    ++ans;
	return ans;
    };

    TEST_CLASS(count_inversions_tests)
    {
    public:
	TEST_METHOD(count_inversions_one_element)
	{
	    std::vector<ll> vec = { 1 };
	    Assert::AreEqual(0, static_cast<int>(count_inversions(vec)));
	}

	TEST_METHOD(count_inversions_two_elements)
	{
	    std::vector<ll> vec = { 1, 2 };
	    Assert::AreEqual(0, static_cast<int>(count_inversions(vec)));
	    range_ns::reverse(vec);
	    Assert::AreEqual(1, static_cast<int>(count_inversions(vec)));
	}
	TEST_METHOD(count_inversions_no_permutations)
	{
	    std::vector<ll> vec(1'000);
	    std::iota(begin(vec), end(vec), 1);
	    Assert::AreEqual(0, static_cast<int>(count_inversions(vec)));
	}

	TEST_METHOD(count_inversions_max_permutations)
	{
	    constexpr ll n = 1'000;
	    std::vector<ll> vec(n);
	    std::iota(begin(vec), end(vec), 1);
	    range_ns::reverse(vec);
	    Assert::IsTrue(n * (n - 1) / 2 == static_cast<int>(count_inversions(vec)));
	}

	TEST_METHOD(count_inversions_in_random_permutation)
	{
	    constexpr ll n = 10'000;
	    constexpr ll iterations_count = 10;
	    std::vector<ll> vec(n);
	    std::iota(begin(vec), end(vec), 1);
	    for (ll i : range_ns::xrange(iterations_count))
	    {
		random_permutate(vec);
		ll inversions_count = naive_count_permutations(vec);
		ll inversions_count_smart = count_inversions(vec);
		Assert::IsTrue(inversions_count == inversions_count_smart);
	    }
	}

	TEST_METHOD(count_inversions_million_elements)
	{
	    constexpr ll n = 1'000'000;
	    std::vector<ll> vec(n);
	    std::iota(begin(vec), end(vec), 1);
	    random_permutate(vec);
	    ll inversions_count = count_inversions(vec);
	    Assert::IsTrue(inversions_count > 0);
	}
    };
}
