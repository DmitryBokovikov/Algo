#include "stdafx.h"
#include "CppUnitTest.h"

#include <Util/UtilAPI.h>
#include <Util/Util.h>
#include <Util/ranges.h>
#include <Util/spent_time.h>

#include <numeric>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace util_ns::tests
{		
    TEST_CLASS(Util_tests)
    {
    public:
	TEST_METHOD(gen_data_test)
	{
	    const ll l = 2, r = 7;
	    auto data = util_ns::gen_data(10, l, r);
	    Assert::IsTrue(range_ns::all_of(data, [l, r](ll val) { return val >= l && val <= r; }));
	    Assert::AreEqual(10, isize(data), L"unexpected data size");
	    data = util_ns::gen_data(100);
	    Assert::IsTrue(range_ns::all_of(data, [](ll val) { return val >= 1 && val <= 10'000; }));
	    Assert::AreEqual(100, isize(data), L"unexpected data size");
	    range_ns::sort(data);
	    range_ns::erase_unique(data);
	    Assert::IsTrue(size(data) > 95, L"Bad distribution");
	}

	TEST_METHOD(spent_time_test)
	{
	    auto[data, time] = util_ns::spent_time([]() { return util_ns::gen_data(1'000'000); });
	    Assert::AreEqual(isize(data), 1'000'000, L"unexpected size");
	}

	TEST_METHOD(get_random_test)
	{
	    int random = get_random(2, 3);
	    Assert::IsTrue(random == 2);
	    for (ll i : range_ns::indices(1000))
	    {
		auto[l, r] = std::pair{ 100, 150 };
		random = get_random(l, r);
		Assert::IsTrue(random >= l && random < r);
	    }    
	}

	TEST_METHOD(random_permutate_test)
	{
		constexpr ll n = 100;
		std::vector<ll> vec(n);
		std::iota(begin(vec), end(vec), 1);
		auto vec_other = vec;
		random_permutate(vec);
		random_permutate(vec_other);
		Assert::IsTrue(vec_other != vec, L"vectors should not be equal after random permutation");
	}
    };
}