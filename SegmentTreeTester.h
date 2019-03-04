#pragma once

#include "util.h"
#include "SegmentTree.h"
#include <vector>
#include <algorithm>

namespace tests_ns
{
    using namespace algo_ns;
    class segment_tree_tester
    {
    public:
	void test_all()
	{
	    auto data = util_ns::gen_data(TEST_DATA_LENGTH);
	    std::vector<std::pair<long long, long long>> cases;
	    cases.reserve(TEST_CASES_COUNT);
	    std::generate_n(std::back_inserter(cases), TEST_CASES_COUNT, []()
	    {
		auto test_case = util_ns::gen_data(2);
		test_case[0] = test_case[0] % TEST_CASES_COUNT;
		test_case[1] = test_case[1] % TEST_CASES_COUNT;
		if (test_case[0] > test_case[1])
		    std::swap(test_case[0], test_case[1]);

		return std::make_pair(test_case[0], test_case[1]);
	    });

	    segment_tree_ns::sum_segment_tree<long long> sum_tree(data);
	    segment_tree_ns::min_segment_tree<long long> min_tree(data);

	    test(data, cases, std::plus<long long>(), sum_tree);
	    test(data, cases, segment_tree_ns::min_functor(), min_tree);

	    // update values
	    for (size_t i = 0; i < size(data); ++i)
	    {
		if (i % 2)
		{
		    data[i] += 1;
		    sum_tree.update(i, data[i]);
		    min_tree.update(i, data[i]);
		}
	    }

	    test(data, cases, std::plus<long long>(), sum_tree);
	    test(data, cases, segment_tree_ns::min_functor(), min_tree);
	}
    private:
	template <class binary_functor>
	void test(
	    const std::vector<long long>& vec,
	    const std::vector<std::pair<long long, long long>>& cases,
	    binary_functor functor,
	    const segment_tree_ns::segment_tree<long long, binary_functor>& seg_tree)
	{
	    for (const auto& segment : cases)
	    {
		long long etalon_res = etalon_result(vec, segment, functor);
		long long seg_tree_res = seg_tree.get_value(segment.first, segment.second);
		if (etalon_res != seg_tree_res)
		    throw std::runtime_error("bad impl segment tree");
	    }
	}

	template <class binary_functor>
	long long etalon_result(const std::vector<long long>& vec, const std::pair<long, long>& segment, binary_functor functor)
	{	   
	    long long ans = std::is_same_v<binary_functor, segment_tree_ns::min_functor> ?
		std::numeric_limits<long long>::max() : 0;

	    for (long i = segment.first; i <= segment.second; ++i)
		ans = functor(ans, vec[i]);
	    return ans;
	}
	static constexpr int TEST_DATA_LENGTH = 5000;
	static constexpr int TEST_CASES_COUNT = 1000;
    };
}
