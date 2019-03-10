#include "stdafx.h"
#include "CppUnitTest.h"
#include <Util/std.h>
#include <Util/Util.h>
#include <Sorts/quadratic_sorts.h>
#include <Sorts/quick_sort.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace util_ns;


using ll = long long;

namespace sort_ns::tests
{		
	TEST_CLASS(Sorts_tests)
	{
	public:
	    TEST_METHOD_INITIALIZE(init_test_data)
	    {
		for (ll data_size : { 0, 1, 2, 3, 5, 20, 100, 1'000, 10'000 })
		    m_test_small_cases.emplace_back(gen_data(data_size));

		for (ll data_size : { 100'000, 1'000'000 })
		    m_test_big_cases.emplace_back(gen_data(data_size));
	    }

	    using sort_func_t = std::function<void(vector<ll>&)>;

	    void sort_test(sort_func_t sort_func, const vector<vector<ll>>& test_cases)
	    {
		for (const auto& test_data : test_cases)
		{
		    auto data_copy_1 = test_data;
		    auto data_copy_2 = test_data;
		    std::sort(begin(data_copy_1), end(data_copy_1));
		    sort_func(data_copy_2);
		    Assert::IsTrue(data_copy_2 == data_copy_1, L"Data are not equal after sort");
		}
	    }

	    void slow_sort_method_test(sort_func_t sort_func)
	    {
		sort_test(sort_func, m_test_small_cases);
	    }

	    void fast_sort_method_test(sort_func_t sort_func)
	    {
		sort_test(sort_func, m_test_small_cases);
		sort_test(sort_func, m_test_big_cases);
	    }

	    TEST_METHOD(bubble_sort_test)
	    {
		slow_sort_method_test(bubble_sort<>);
	    }

	    TEST_METHOD(selection_sort_test)
	    {
		slow_sort_method_test(selection_sort<>);
	    }

	    TEST_METHOD(dwarf_sort_test)
	    {
		slow_sort_method_test(dwarf_sort<>);
	    }

	    TEST_METHOD(insertion_sort_test)
	    {
		slow_sort_method_test(insertion_sort<>);
	    }

	    TEST_METHOD(quick_sort_test)
	    {
		fast_sort_method_test(quick_sort<>);
	    }

	private:
	    vector<vector<ll>> m_test_small_cases;
	    vector<vector<ll>> m_test_big_cases;
	};
}