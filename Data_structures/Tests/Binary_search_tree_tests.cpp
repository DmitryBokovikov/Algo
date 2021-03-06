#include "stdafx.h"
#include "CppUnitTest.h"

#include <Data_structures/binary_search_tree.h>

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
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1, 1, 1, 2 });
	    tree.insert(2);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<int>{ 1, 1, 1, 2, 2 });
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
	    const ll data_size = 1'000;
	    const auto data = util_ns::gen_data(data_size);
	    Assert::IsTrue(tree.empty(), L"tree should be empty");
	    for (ll i : range_ns::indices(data_size))
	    {
		tree.insert(data[i]);
		Assert::AreEqual(tree.size(), static_cast<int>(i + 1), L"unexpected tree size");
	    }
	    for (ll i : range_ns::indices(data_size))
	    {
		tree.erase(data[i]);
		Assert::AreEqual(tree.size(), static_cast<int>(data_size - i - 1), L"unexpected tree size");
	    }
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
	    std::multiset<ll> mset(cbegin(sorted), cend(sorted));
	    util_ns::random_permutate(sorted);
	    const auto file_out_path = fs::path("M:\\git\\Algo\\bfs_tree.txt");
	    if (m_need_log) std::ofstream().open(file_out_path);
	    if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
	    for (ll val : sorted)
	    {
		tree.erase(val);
		mset.erase(mset.find(val));
		if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
		Assert::IsTrue(tree.get_sorted() == std::vector<ll>(cbegin(mset), cend(mset)));
	    }
	}

	TEST_METHOD(test_delete_with_less_than_two_childrens)
	{
	    binary_search_tree<ll> tree;
	    tree.insert(1);
	    tree.erase(1);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{});
	    Assert::IsTrue(tree.empty());
	    tree.insert(1);
	    tree.insert(2);
	    tree.erase(1);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{2});
	    Assert::IsTrue(tree.size() == 1);
	    tree.insert(1);
	    tree.erase(1);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{2});
	    Assert::IsTrue(tree.size() == 1);
	    tree.reset();
	    Assert::IsTrue(tree.empty());
	    for (ll val : {1, 2, 3, 4, 5, 6})
		tree.insert(val);
	    Assert::IsTrue(tree.size() == 6);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{1, 2, 3, 4, 5, 6});
	    for (ll val : {2, 3, 4, 5})
		tree.erase(val);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{1, 6});
	    Assert::IsTrue(tree.size() == 2);
	    tree.erase(1);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{6});
	    tree.erase(6);
	    Assert::IsTrue(tree.get_sorted() == std::vector<ll>{});
	    for (ll val : {1, 2, 3, 4, 5, 6})
		tree.insert(val);
	    for (ll val : {1, 2, 3, 4, 5, 6})
	    {
		tree.erase(val);
		const ll expected_size = 6 - val;
		Assert::IsTrue(tree.size() == expected_size);
		std::vector<ll> expected(expected_size);
		std::iota(begin(expected), end(expected), val + 1);
		Assert::IsTrue(tree.get_sorted() == expected);
	    }

	    for (ll val : { 6, 5, 4, 3, 2, 1})
		tree.insert(val);
	    for (ll val : { 6, 5, 4, 3, 2, 1})
	    {
		tree.erase(val);
		const ll expected_size = val - 1;
		Assert::IsTrue(tree.size() == expected_size);
		std::vector<ll> expected(expected_size);
		std::iota(begin(expected), end(expected), 1);
		Assert::IsTrue(tree.get_sorted() == expected);
	    }
	}

	TEST_METHOD(test_delete_with_than_two_childrens)
	{
	    binary_search_tree<ll> tree;
	    for (ll val : {4, 3, 7, 8, 1, 5, 2, 6})
		tree.insert(val);
	    const auto file_out_path = fs::path("M:\\git\\Algo\\bfs_tree.txt");
	    if (m_need_log) std::ofstream().open(file_out_path);
	    if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
	    tree.erase(7);
	    if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<ll>{4, 3, 8, 1, 5, 2, 6});
	    tree.erase(4);
	    if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<ll>{5, 3, 8, 1, 6, 2});
	    tree.erase(5);
	    if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<ll>{6, 3, 8, 1, 2});
	    tree.erase(6);
	    if (m_need_log) tree.test_print_in_bfs_order(file_out_path);
	    Assert::IsTrue(tree.get_in_bfs_order() == std::vector<ll>{8, 3, 1, 2});
	}

	TEST_METHOD(test_find_next)
	{
	    auto data = util_ns::gen_data(10'000);

	    std::multiset<ll> std_set(cbegin(data), cend(data));
	    binary_search_tree<ll> tree(data);

	    for (ll val : data)
	    {
		auto it = std::next(std_set.find(val));
		auto val_opt = tree.find_next(val);
		if (!val_opt)
		    Assert::IsTrue(it == cend(std_set), L"it not equal to end");
		else
		    Assert::IsTrue(val_opt.value() == *it, L"value are not equal");
	    }

	    tree.reset();
	    for (ll val : { 1, 3, 5, 7})
		tree.insert(val);
	    Assert::IsTrue(tree.find_next(5).value() == 7);
	    Assert::IsTrue(!tree.find_next(7).has_value());
	}

	TEST_METHOD(test_find_prev)
	{
	    auto data = util_ns::gen_data(10'000);

	    std::multiset<ll> std_set(cbegin(data), cend(data));
	    binary_search_tree<ll> tree(data);

	    for (ll val : data)
	    {
		auto it = std_set.find(val);
		auto val_opt = tree.find_prev(val);
		if (!val_opt)
		    Assert::IsTrue(it == cbegin(std_set), L"it not equal to begin of set");
		else
		    Assert::IsTrue(val_opt.value() == *std::prev(it), L"value are not equal");
	    }

	    tree.reset();
	    for (ll val : { 1, 3, 5, 7})
		tree.insert(val);
	    Assert::IsTrue(tree.find_prev(5).value() == 3);
	    Assert::IsTrue(!tree.find_prev(1).has_value());
	}

    private:
	const bool m_need_log = false;
    };
}
