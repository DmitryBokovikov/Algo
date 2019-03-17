#pragma once

#include <Util/std.h>
#include <Util/ranges.h>

namespace sort_ns
{
    template<class T = int>
    class pyramid
    {
    public:
	pyramid(std::vector<T>& i_elements) : m_elements(i_elements), m_size(isize(i_elements))
	{
	    static_assert(std::is_integral_v<T>);
	    for (int i = isize(m_elements) / 2; i >= 0; --i)
		max_heapify(i);
	}

	void make_sort()
	{
	    for (int i = m_size - 1; i >= 0; --i)
	    {
		std::swap(m_elements[i], m_elements[0]);
		m_size -= 1;
		max_heapify(0);
	    }
	}

    private:
	static int parent(int i) { return (i - 1) / 2; }

	static int left(int i) { return 2 * (i + 1) - 1; }

	static int right(int i) { return 2 * (i + 1); }

	void max_heapify(int idx)
	{
	    int max_idx = idx, left_idx = left(idx), right_idx = right(idx);
	    if (left_idx < m_size && m_elements[left_idx] > m_elements[max_idx])
		max_idx = left_idx;
	    if (right_idx < m_size && m_elements[right_idx] > m_elements[max_idx])
		max_idx = right_idx;
	    if (max_idx != idx)
	    {
		std::swap(m_elements[max_idx], m_elements[idx]);
		max_heapify(max_idx);
	    }
	}

    private:
	std::vector<T>& m_elements;
	int m_size = 0;
    };

    template<class Container = std::vector<ll>>
    void heap_sort(Container& io_container)
    {
	pyramid<Container::value_type> p(io_container);
	p.make_sort();
    }
}
