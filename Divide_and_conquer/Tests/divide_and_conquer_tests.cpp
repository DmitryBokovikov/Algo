#include "stdafx.h"
#include "CppUnitTest.h"

#include <Divide_and_conquer/nth_element.h>
#include <Util/Util.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace divide_and_conquer_ns::tests
{		
    using namespace util_ns;
    using namespace divide_and_conquer_ns;

    auto get_std_nth_element = [](auto& vec, int pos)
    {
	std::nth_element(begin(vec), begin(vec) + pos, end(vec));
	return *(begin(vec) + pos);
    };

    TEST_CLASS(divide_and_conquer_tests)
    {
    public:
	TEST_METHOD_INITIALIZE(init_test_data)
	{
	    for (int data_size : { 1, 2, 3, 5, 20, 100, 1'000, 10'000, 100'000, 1'000'000 })
		m_test_cases.emplace_back(gen_data(data_size));
	}

	template<class n_th_element_func>
	void test_nth_element_func(n_th_element_func i_n_th_element_func)
	{
	    for (const auto& data : m_test_cases)
	    {
		int pos = get_random(0, isize(data));
		auto copy_data1 = data, copy_data2 = data;
		ll my_nth = i_n_th_element_func(copy_data1, pos);
		ll std_nth = get_std_nth_element(copy_data2, pos);
		const std::wstring error_text =
		    L"Bad nth_element impl for data size = " + std::to_wstring(size(data))
		    + L" and pos = " + std::to_wstring(pos);
		Assert::IsTrue(my_nth == std_nth, error_text.c_str());
	    }
	}
	TEST_METHOD(test_nth_element)
	{
	    test_nth_element_func(nth_element<>);
	}

	TEST_METHOD(test_std_nth_element)
	{
	    test_nth_element_func(get_std_nth_element);
	}

    private:
	vector<vector<ll>> m_test_cases;
    };
}