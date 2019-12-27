#pragma once

#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

namespace data_structures_ns
{
    class prefix_tree
    {
    public:
	void insert(std::string_view word)
	{
	    tree_node* tree_ptr = &m_tree;
	    for (char ch : word)
	    {
		if (!tree_ptr->m_chldren.count(ch))
		    tree_ptr->m_chldren.emplace(ch, std::make_unique<tree_node>());
		tree_ptr = tree_ptr->m_chldren[ch].get();
	    }
	    tree_ptr->m_chldren.emplace('-', nullptr);
	}

	bool search(std::string_view word)
	{
	    tree_node* tree_ptr = &m_tree;
	    for (char ch : word)
	    {
		if (!tree_ptr->m_chldren.count(ch))
		    return false;
		tree_ptr = tree_ptr->m_chldren[ch].get();
	    }
	    return tree_ptr->m_chldren.count('-');
	}

	bool startsWith(std::string_view prefix)
	{
	    tree_node* tree_ptr = &m_tree;
	    for (char ch : prefix)
	    {
		if (!tree_ptr->m_chldren.count(ch))
		    return false;
		tree_ptr = tree_ptr->m_chldren[ch].get();
	    }
	    return true;
	}

	std::vector<std::string> get_all_words() const
	{
	    std::vector<std::string> ans;
	    std::string res;
	    std::function<void(const tree_node*)> backtrack;
	    backtrack = [&](const tree_node* tree_node_ptr)
	    {
		for (const auto&[ch, new_tree_node_ptr] : tree_node_ptr->m_chldren)
		{
		    if (ch == '-')
		    {
			ans.push_back(res);
			continue;
		    }
		    res += ch;
		    backtrack(new_tree_node_ptr.get());
		    res.pop_back();
		}
	    };
	    backtrack(&m_tree);
	    return ans;
	}

	struct tree_node
	{
	    std::unordered_map<char, std::unique_ptr<tree_node>> m_chldren;
	};

	tree_node m_tree;
    };
}

