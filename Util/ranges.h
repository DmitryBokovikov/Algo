#pragma once

#include <iterator>
#include <algorithm>

namespace range_ns
{
    template<class Container>
    void print(const Container& container, const char* sep = "\n")
    {
	std::copy(container.begin(), container.end(), ostream_iterator<typename Container::value_type>(cout, sep));
    }

    template<class Container, class Compare = std::less<typename Container::value_type>>
    void sort(Container& container, Compare compare = Compare())
    {
	std::sort(container.begin(), container.end(), compare);
    }

    template<class Container, class T>
    decltype(auto) find(Container& container, const T& elem)
    {
	return std::find(container.begin(), container.end(), elem);
    }

    template<class Container, class Condition>
    decltype(auto) find_if(Container& container, Condition condition)
    {
	return std::find_if(container.begin(), container.end(), condition);
    }

    template<class Container, class Condition = std::less<typename Container::value_type>>
    decltype(auto) max_element(Container& container, Condition condition = Condition())
    {
	return std::max_element(container.begin(), container.end(), condition);
    }

    template<class Container, class Condition = std::less<typename Container::value_type>>
    decltype(auto) min_element(Container& container, Condition condition = Condition())
    {
	return std::min_element(container.begin(), container.end(), condition);
    }

    template<class Container, class Condition = std::less<typename Container::value_type>>
    decltype(auto) minmax_element(Container& container, Condition condition = Condition())
    {
	return std::minmax_element(container.begin(), container.end(), condition);
    }

    template<class Container, class Condition>
    decltype(auto) any_of(const Container& container, Condition condition)
    {
	return std::any_of(container.begin(), container.end(), condition);
    }

    template<class Container, class Condition>
    decltype(auto) all_of(const Container& container, Condition condition)
    {
	return std::all_of(container.begin(), container.end(), condition);
    }

    template<class Container, class T>
    decltype(auto) count(const Container& container, const T& elem)
    {
	return std::count(container.begin(), container.end(), elem);
    }

    template<class Container, class Condition>
    decltype(auto) count_if(const Container& container, Condition condition)
    {
	return std::count_if(container.begin(), container.end(), condition);
    }

    template<class Container, class T, class Compare = std::less<typename Container::value_type>>
    decltype(auto) equal_range(Container& container, const T& elem, Compare compare = Compare())
    {
	return std::equal_range(container.begin(), container.end(), elem, compare);
    }

    template<class Container, class T, class Compare = std::less<typename Container::value_type>>
    decltype(auto) lower_bound(Container& container, const T& elem, Compare compare = Compare())
    {
	return std::lower_bound(container.begin(), container.end(), elem, compare);
    }

    template<class Container, class T>
    decltype(auto) upper_bound(Container& container, const T& elem)
    {
	return std::upper_bound(container.begin(), container.end(), elem);
    }

    template<class Container, class T>
    void erase_remove(Container& container, const T& elem)
    {
	container.erase(remove(container.begin(), container.end(), elem), container.end());
    }

    template<class Container, class Condition>
    void erase_remove_if(Container& container, Condition condition)
    {
	container.erase(remove_if(container.begin(), container.end(), condition), container.end());
    }

    template<class Container, class Condition>
    Container copy_if(const Container& container, Condition condition)
    {
	Container container_result;
	copy_if(container.begin(), container.end(), back_inserter(container_result), condition);
	return container_result;
    }

    template <class Container>
    void reverse(Container& container)
    {
	std::reverse(begin(container), end(container));
    }

    using ll = long long;

    struct sum_functor
    {
	ll operator()(ll sum, ll value) const { return sum + value; }
    };

    template<class Container, class Func = sum_functor, class T = ll>
    T reduce(const Container& container, T init_value = T(), Func func = sum_functor())
    {
	return std::accumulate(container.begin(), container.end(), init_value, func);
    }

    template<class Container, class Func = std::equal_to<typename Container::value_type>>
    decltype(auto) adjacent_find(const Container& container, Func func = Func())
    {
	return std::adjacent_find(container.begin(), container.end(), func);
    }

    template<class InContainer, class OutContainer, class TransformFunction>
    void transform(const InContainer& in_container, OutContainer& out_container, TransformFunction transform_function)
    {
	if (out_container.capacity() == 0)
	    out_container.reserve(size(in_container) + size(out_container));
	std::transform(in_container.begin(), in_container.end(), back_inserter(out_container), transform_function);
    }

    class xrange
    {
	class Iterator
	{
	public:
	    Iterator(ll i) : m_i(i) {}
	    ll operator++ () { return ++m_i; }
	    ll operator*() { return m_i; }
	    bool operator!=(const Iterator& it) const { return m_i != it.m_i; }

	    using iterator_category = std::random_access_iterator_tag;
	    using value_type = ll;
	    using difference_type = ll;
	    using pointer = ll;
	    using reference = void;
	private:
	    ll m_i;
	};

	ll m_begin = 0;
	ll m_end;

    public:
	xrange(ll n) : m_end(n) {}
	xrange(ll l, ll r) : m_begin(l), m_end(r) {}
	Iterator begin() { return Iterator(m_begin); }
	Iterator end() { return Iterator(m_end); }
    };

    template <class Container>
    decltype(auto) enumerate(const Container& container)
    {
	using return_type = vector<pair<typename Container::value_type, ll>>;
	return_type out_container;
	const ll n = lsize(container);
	out_container.reserve(n);
	for (ll i : xrange(n))
	    out_container.emplace_back(container[i], i);

	return out_container;
    }

    template <class Container, class PredicateCompare = std::equal_to<typename Container::value_type>>
    void erase_unique(Container& container, PredicateCompare compare = PredicateCompare())
    {
	container.erase(
	    std::unique(
		begin(container),
		end(container),
		compare),
	    end(container));
    }

    template <class Container, class SearchT>
    decltype(auto) search(Container& container, const SearchT& to_search)
    {
	return std::search(
	    begin(container),
	    end(container),
	    begin(to_search),
	    end(to_search)
	);
    }

    template <class Container, class Compare = std::less<typename Container::value_type>>
    bool binary_search(const Container& container, typename Container::value_type& elem, Compare compare = Compare())
    {
	return std::binary_search(cbegin(container), cend(container), elem);
    }
}

using namespace range_ns;