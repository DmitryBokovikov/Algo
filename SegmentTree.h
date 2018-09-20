#pragma once

#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <optional>

namespace algo_ns::segment_tree_ns
{
    template <class T, class binary_func>
    class segment_tree
    {
    public:
	segment_tree(const std::vector<T>& elems) 
	    : tree_(4 * size(elems)), binary_op_(binary_func{}), tree_size_(size(elems))
	{
	    static_assert(
		std::is_constructible_v<std::function<T(T, T)>, binary_func>,
		"wrong binary_func arg : it must be convertible to std::function<T(T, T)>");
	    
	    build(elems, 1, 0, tree_size_ - 1);
	}

	T get_value(size_t left, size_t right) const
	{
	    auto opt_value = get_value_int(1, 0, tree_size_ - 1, left, right);
	    if (opt_value.has_value())
		return opt_value.value();

	    throw std::runtime_error("logical error : left > right");
	}

	void update(size_t pos, T new_value)
	{
	    update_int(1, 0, tree_size_ - 1, pos, new_value);
	}
    private:
	void build(const std::vector<T>& cont, size_t vertex, size_t left, size_t right)
	{
	    if (left == right)
	    {
		tree_[vertex] = cont[left];
	    }		
	    else
	    {
		size_t center = (left + right) / 2;
		build(cont, vertex * 2, left, center);
		build(cont, vertex * 2 + 1, center + 1, right);
		tree_[vertex] = binary_op_(tree_[vertex * 2], tree_[vertex * 2 + 1]);
	    }
	}

	std::optional<T> get_value_int(size_t vertex, size_t tree_left, size_t tree_right, size_t left, size_t right) const
	{
	    if (left > right)
		return std::nullopt;
	    if (left == tree_left && right == tree_right)
		return tree_[vertex];
	    size_t center = (tree_left + tree_right) / 2;

	    auto first = get_value_int(vertex * 2, tree_left, center, left, std::min(right, center));
	    auto second = get_value_int(vertex * 2 + 1, center + 1, tree_right, std::max(left, center + 1), right);
	    if (first.has_value() && second.has_value())
		return binary_op_(first.value(), second.value());
	    else if (first.has_value())
		return first.value();
	    else
		return second.value();
	}

	void update_int(size_t vertex, size_t tree_left, size_t tree_right, size_t pos, T new_value)
	{
	    if (tree_left == tree_right)
	    {
		tree_[vertex] = new_value;
	    }		
	    else
	    {
		size_t center = (tree_left + tree_right) / 2;
		if (pos <= center)
		    update_int(vertex * 2, tree_left, center, pos, new_value);
		else
		    update_int(vertex * 2 + 1, center + 1, tree_right, pos, new_value);
		tree_[vertex] = binary_op_(tree_[vertex * 2], tree_[vertex * 2 + 1]);
	    }
	}
    private:
	std::vector<T> tree_;
	const size_t tree_size_;
	std::function<T(T, T)> binary_op_;
    };

    template <class T>
    using sum_segment_tree = segment_tree<T, std::plus<T>>;

    template <class T>
    struct max_s
    {
	T operator()(T lhs, T rhs) const { return std::max<T>(lhs, rhs); }
    };
    template <class T>
    using max_segment_tree = segment_tree <T, max_s<T>> ;

    template <class T>
    struct min_s
    {
	T operator()(T lhs, T rhs) const { return std::min<T>(lhs, rhs); }
    };
    template <class T>
    using min_segment_tree = segment_tree<T, min_s<T>>;
}
