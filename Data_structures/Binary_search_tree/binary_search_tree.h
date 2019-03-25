#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace data_structures_ns
{
    template<class T>
    class binary_search_tree
    {
    private:
	struct node
	{
	    node(const T& i_value) : m_value(i_value) {}

	    std::shared_ptr<node> m_left_ptr;
	    std::shared_ptr<node> m_right_ptr;
	    std::shared_ptr<node> m_parent_ptr;
	    T m_value;
	};

	using shared_node_ptr = std::shared_ptr<node>;

    public:
	void insert(const T& i_value)
	{
	    if (!m_tree_ptr)
	    {
		m_tree_ptr = std::make_shared<node>(i_value);
	    }
	    else
	    {
		shared_node_ptr current_ptr = m_tree_ptr;
		shared_node_ptr previous_ptr;
		while (current_ptr)
		{
		    previous_ptr = current_ptr;
		    if (current_ptr->m_value >= i_value)
			current_ptr = current_ptr->m_left_ptr;
		    else
			current_ptr = current_ptr->m_right_ptr;
		}
		current_ptr = std::make_shared<node>(i_value);
		current_ptr->m_parent_ptr = previous_ptr;
		if (previous_ptr->m_value < i_value)
		    previous_ptr->m_right_ptr = current_ptr;
		else
		    previous_ptr->m_left_ptr = current_ptr;
	    }
	    ++m_size;
	}

	void erase(const T& i_elem)
	{
	    auto find_ptr_opt = find_int(i_elem);
	    if (!find_ptr_opt)
		return;
	    auto find_ptr = find_ptr_opt.value();
	    // no children
	    if (!find_ptr->m_left_ptr && !find_ptr->m_right_ptr)
	    {
		if (auto& parent_ptr = find_ptr->m_parent_ptr)
		    (parent_ptr->m_left_ptr == find_ptr ? parent_ptr->m_left_ptr : parent_ptr->m_right_ptr).reset();
		else
		    m_tree_ptr.reset();
	    }
	    // one child
	    else if (!find_ptr->m_left_ptr || !find_ptr->m_right_ptr)
	    {
		const bool has_left = find_ptr->m_left_ptr != nullptr;
		if (auto& parent_ptr = find_ptr->m_parent_ptr)
		{
		    const bool parent_ptr_left = parent_ptr->m_left_ptr == find_ptr;
		    (parent_ptr_left ? parent_ptr->m_left_ptr : parent_ptr->m_right_ptr) = has_left ? find_ptr->m_left_ptr : find_ptr->m_right_ptr;
		    (has_left ? find_ptr->m_left_ptr : find_ptr->m_right_ptr)->m_parent_ptr = find_ptr->m_parent_ptr;
		}
		else
		{
		    m_tree_ptr = has_left ? find_ptr->m_left_ptr : find_ptr->m_right_ptr;
		    (has_left ? find_ptr->m_left_ptr : find_ptr->m_right_ptr)->m_parent_ptr = nullptr;
		}
	    }
	    // two children
	    else
	    {
		auto left_ptr = find_ptr->m_right_ptr->m_left_ptr;
		if (!left_ptr)
		{
		    auto right_ptr_value = find_ptr->m_right_ptr->m_value;
		    auto right_ptr = find_ptr->m_right_ptr;
		    find_ptr->m_right_ptr = right_ptr->m_right_ptr;
		    if (right_ptr->m_right_ptr)
			right_ptr->m_right_ptr->m_parent_ptr = find_ptr;
		    find_ptr->m_value = right_ptr_value;
		}
		else
		{
		    while (left_ptr->m_left_ptr)
			left_ptr = left_ptr->m_left_ptr;
		    auto left_ptr_value = left_ptr->m_value;
		    find_ptr->m_value = left_ptr_value;
		    if (left_ptr->m_right_ptr)
			left_ptr->m_right_ptr->m_parent_ptr = left_ptr->m_parent_ptr;
		    left_ptr->m_parent_ptr->m_left_ptr = left_ptr->m_right_ptr;
		}
	    }

	    --m_size;
	}

	bool find(const T& i_elem) const
	{
	    return find_int(i_elem).has_value();
	}

	void reset()
	{
	    m_tree_ptr.reset();
	    m_size = 0;
	}

	std::optional<T> find_next(const T& i_elem) const
	{

	}

	std::optional<T> find_prev(const T& i_elem) const
	{

	}

	std::vector<T> get_sorted() const
	{
	    std::vector<T> res;
	    res.reserve(m_size);

	    std::function<void(const shared_node_ptr&)> visit;
	    visit = [&visit, &res, this](const shared_node_ptr& i_tree_ptr)
	    {
		if (!i_tree_ptr)
		    return;

		if (i_tree_ptr->m_left_ptr)
		    visit(i_tree_ptr->m_left_ptr);

		if (i_tree_ptr)
		    res.emplace_back(i_tree_ptr->m_value);

		if (i_tree_ptr->m_right_ptr)
		    visit(i_tree_ptr->m_right_ptr);
	    };
	    visit(m_tree_ptr);
	    return res;
	}

	std::vector<T> get_in_bfs_order(std::function<void(const node&, ll)> i_func = nullptr) const
	{
	    std::vector<T> res;
	    res.reserve(m_size);

	    std::queue<std::pair<const node*, ll>> queue;
	    if (m_tree_ptr)
		queue.emplace(m_tree_ptr.get(), 1);
	    while (!std::empty(queue))
	    {
		auto[ptr, depth] = queue.front();
		queue.pop();
		res.emplace_back(ptr->m_value);
		if (i_func)
		    i_func(*ptr, depth);
		if (ptr->m_left_ptr)
		    queue.emplace(ptr->m_left_ptr.get(), depth + 1);
		if (ptr->m_right_ptr)
		    queue.emplace(ptr->m_right_ptr.get(), depth + 1);
	    }
	    return res;
	}

	int size() const { return m_size; }

	bool empty() const { return !m_size; }

	void test_print_in_bfs_order(const fs::path& i_path)
	{
	    std::ofstream out_file_stream(i_path, std::ios::out | std::ios::app);
	    if (!out_file_stream.is_open())
		throw std::runtime_error("error open file " + i_path.string());
	    ll i = 1;
	    out_file_stream << "depth " << 1 << " : ";
	    auto bfs_func = [&i, &out_file_stream](const node& i_node, ll depth)
	    {
		if (depth > i)
		{
		    i = depth;
		    out_file_stream << "\ndepth " << depth << " : ";
		}
		out_file_stream
		    << "value (" << i_node.m_value << ")"
		    << " parent (" << (i_node.m_parent_ptr ? std::to_string(i_node.m_parent_ptr->m_value) : "nullptr") << ")"
		    << " left (" << (i_node.m_left_ptr ? std::to_string(i_node.m_left_ptr->m_value) : "nullptr") << ")"
		    << " right (" << (i_node.m_right_ptr ? std::to_string(i_node.m_right_ptr->m_value) : "nullptr") << ")"
		    << ", ";
	    };
	    get_in_bfs_order(bfs_func);
	    out_file_stream << "\n---------------------\n";
	}

    private:
	std::optional<shared_node_ptr> find_int(const T& i_elem) const
	{
	    std::function<std::optional<shared_node_ptr>(const shared_node_ptr&)> find_impl;
	    find_impl = [&find_impl, &i_elem](const shared_node_ptr& i_node_ptr) -> std::optional<shared_node_ptr>
	    {
		if (!i_node_ptr)
		    return std::nullopt;

		if (i_node_ptr->m_value == i_elem)
		    return std::make_optional<shared_node_ptr>(i_node_ptr);

		return i_node_ptr->m_value > i_elem ? find_impl(i_node_ptr->m_left_ptr) : find_impl(i_node_ptr->m_right_ptr);
	    };

	    return find_impl(m_tree_ptr);
	}

    private:	
	shared_node_ptr m_tree_ptr;
	int m_size = 0;
    };
}
