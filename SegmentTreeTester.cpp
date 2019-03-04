#include "stdafx.h"

#include "SegmentTreeTester.h"

void segment_tree_tester::test_all()
{

}
class segment_tree_tester : tester_base
{
public:
    void test_all() override;
private:
    void test_max_segment_tree();
    void test_sum_segment_tree();

    template <class binary_func>
    std::vector<ll> calc_index_vector(const std::vector<ll>& vec)
    {
	binary_func binary_functor;
	std::vector<ll> res(vec);
	for (size_t i = 1; i < size(vec) - 1; ++i)
	    res[i] = binary_functor(res[i - 1], res[i]);

	return res;
    }
};