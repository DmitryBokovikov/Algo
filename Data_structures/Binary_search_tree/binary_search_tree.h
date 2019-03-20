#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace data_structures_ns
{
    template<class T>
    class binary_search_tree
    {
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

	}

	bool find(const T& i_elem) const
	{
	    std::function<bool(const shared_node_ptr&)> find_impl;
	    find_impl = [&find_impl, &i_elem](const shared_node_ptr& i_node_ptr)
	    {
		if (!i_node_ptr)
		    return false;

		if (i_node_ptr->m_value == i_elem)
		    return true;

		return i_node_ptr->m_value > i_elem ? find_impl(i_node_ptr->m_left_ptr) : find_impl(i_node_ptr->m_right_ptr);
	    };

	    return find_impl(m_tree_ptr);
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

	std::vector<T> get_in_bfs_order() const
	{
	    std::vector<T> res;
	    res.reserve(m_size);

	    std::queue<const node*> queue;
	    if (m_tree_ptr)
		queue.emplace(m_tree_ptr.get());
	    while (!empty(queue))
	    {
		auto ptr = queue.front();
		queue.pop();
		res.emplace_back(ptr->m_value);
		if (ptr->m_left_ptr)
		    queue.emplace(ptr->m_left_ptr.get());
		if (ptr->m_right_ptr)
		    queue.emplace(ptr->m_right_ptr.get());
	    }
	    return res;
	}

	int size() const { return m_size; }

	int height() const { return m_height; }

    private:


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

	shared_node_ptr m_tree_ptr;
	int m_size = 0;
    };
}
