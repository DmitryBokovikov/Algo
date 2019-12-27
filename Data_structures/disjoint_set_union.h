#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <optional>

namespace data_structures_ns
{
    class disjoint_set_union
    {
    public:
	disjoint_set_union(int n) : m_parent(std::vector<int>(n, -1)), m_unions(std::vector<std::vector<int>>(n))
	{
	    for (int i = 0; i < n; ++i)
	    {
		make_set(i);
		m_unions[i].push_back(i);
	    }
	}

	void union_sets(int a, int b)
	{
	    a = find_set(a);
	    b = find_set(b);
	    if (a != b)
	    {
		if (size(m_unions[a]) < size(m_unions[b]))
		    std::swap(a, b);

		auto& unions_a = m_unions[m_parent[a]];
		auto& unions_b = m_unions[m_parent[b]];
		unions_a.insert(end(unions_a), cbegin(unions_b), cend(unions_b));
		std::vector<int>().swap(unions_b);

		m_parent[b] = a;
	    }
	}

	bool in_different_sets(int a, int b)
	{
	    return find_set(a) != find_set(b);
	}

	const std::vector<int>& get_union() const
	{
	    return *std::find_if(cbegin(m_unions), cend(m_unions), [](const auto& vec) { return !empty(vec); });
	}

	int get_unions_count() const
	{
	    return std::count_if(cbegin(m_unions), cend(m_unions), [](const auto& i_union) { return !empty(i_union); });
	}

    private:
	void make_set(int v)
	{
	    m_parent[v] = v;
	}

	int find_set(int v)
	{
	    if (v == m_parent[v])
		return v;
	    return m_parent[v] = find_set(m_parent[v]);
	}

    private:
	std::vector<int> m_parent;
	std::vector<std::vector<int>> m_unions;
    };
}
