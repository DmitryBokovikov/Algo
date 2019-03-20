#include "stdafx.h"
#include "CppUnitTest.h"

#include <Data_structures/Binary_search_tree/binary_search_tree.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace data_structures_ns::tests
{		
    TEST_CLASS(binary_search_tree_tests)
    {
    public:
	TEST_METHOD(test_insert)
	{
	    binary_search_tree<int> tree;
	    tree.insert(5);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5 });
	    tree.insert(7);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5, 7 });
	    tree.insert(9);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5, 7, 9 });
	    tree.insert(3);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5, 3, 7, 9 });
	    tree.insert(1);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5, 3, 7, 1, 9 });
	    tree.insert(4);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5, 3, 7, 1, 4, 9 });
	    tree.insert(2);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 5, 3, 7, 1, 4, 9, 2 });

	    tree.reset();
	    tree.insert(1);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1 });
	    tree.insert(1);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1, 1 });
	    tree.insert(1);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1, 1, 1 });
	    tree.insert(2);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1, 1, 2, 1 });
	    tree.insert(2);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1, 1, 2, 1, 2 });
	}
	
	TEST_METHOD(test_find)
	{
	    binary_search_tree<ll> tree;
	    for (ll value : util_ns::gen_data(10'000))
	    {
		tree.insert(value);
		Assert::IsTrue(tree.find(value), L"value was not found in tree");
	    }
	}

	TEST_METHOD(test_size)
	{
	    binary_search_tree<ll> tree;
	    auto data = util_ns::gen_data(1'000);
	    Assert::AreEqual(tree.size(), 0, L"size should be zero");
	    for (ll i : range_ns::xrange(size(data)))
	    {
		tree.insert(data[i]);
		Assert::AreEqual(tree.size(), static_cast<int>(i + 1), L"unexpected tree size");
	    }
	    // TBD : check deletion
	}
	TEST_METHOD(test_get_sorted)
	{
	    binary_search_tree<ll> tree;
	    auto elements = util_ns::gen_data(10'000);
	    for (ll value : elements)
		tree.insert(value);
	    auto sorted = tree.get_sorted();
	    range_ns::sort(elements);
	    Assert::IsTrue(sorted == elements);
	    // TBD : check deletion
	}
    };
}
