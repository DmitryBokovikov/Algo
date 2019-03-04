#include "stdafx.h"
#include "CppUnitTest.h"

#include <Util/UtilAPI.h>
#include <Util/Util.h>
#include <Util/ranges.h>
#include <Util/spent_time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace util_ns
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
    };
}