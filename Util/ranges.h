#pragma once

#include <algorithm>
#include <functional>
#include <iterator>
#include <cassert>
#include <tuple>
#include <type_traits>
#include <numeric>

namespace range_ns
{
    template<class Container, class Compare = std::less<typename Container::value_type>>
    void sort(Container& io_container, Compare i_compare = Compare())
    {
	std::sort(io_container.begin(), io_container.end(), i_compare);
    }

    template<class Container, class T = typename Container::value_type>
    bool binary_search(const Container& i_container, const T& i_elem)
    {
	return std::binary_search(i_container.begin(), i_container.end(), i_elem);
    }

    template<class Container, class T>
    decltype(auto) find(Container& i_container, const T& i_elem)
    {
	return std::find(i_container.begin(), i_container.end(), i_elem);
    }

    template<class Container, class Condition>
    decltype(auto) find_if(Container& i_container, Condition i_condition)
    {
	return std::find_if(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class Condition = std::less<typename Container::value_type>>
    decltype(auto) max_element(Container& i_container, Condition i_condition = Condition())
    {
	return std::max_element(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class Condition = std::less<typename Container::value_type>>
    decltype(auto) min_element(Container& i_container, Condition i_condition = Condition())
    {
	return std::min_element(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class Condition = std::less<typename Container::value_type>>
    decltype(auto) minmax_element(Container& i_container, Condition i_condition = Condition())
    {
	return std::minmax_element(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class Condition>
    bool any_of(const Container& i_container, Condition i_condition)
    {
	return std::any_of(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class Condition>
    bool all_of(const Container& i_container, Condition i_condition)
    {
	return std::all_of(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class T>
    decltype(auto) count(const Container& i_container, const T& i_elem)
    {
	return std::count(i_container.begin(), i_container.end(), i_elem);
    }

    template<class Container, class Condition>
    decltype(auto) count_if(const Container& i_container, Condition i_condition)
    {
	return std::count_if(i_container.begin(), i_container.end(), i_condition);
    }

    template<class Container, class T, class Compare = std::less<typename Container::value_type>>
    decltype(auto) equal_range(Container& i_container, const T& i_elem, Compare i_compare = Compare())
    {
	return std::equal_range(i_container.begin(), i_container.end(), i_elem, i_compare);
    }

    template<class Container, class T, class Compare = std::less<typename Container::value_type>>
    decltype(auto) lower_bound(Container& i_container, const T& i_elem, Compare i_compare = Compare())
    {
	return std::lower_bound(i_container.begin(), i_container.end(), i_elem, i_compare);
    }

    template<class Container, class T>
    decltype(auto) upper_bound(Container& i_container, const T& i_elem)
    {
	return std::upper_bound(i_container.begin(), i_container.end(), i_elem);
    }

    template<class Container, class Condition>
    void erase_remove_if(Container& io_container, Condition i_condition)
    {
	io_container.erase(std::remove_if(io_container.begin(), io_container.end(), i_condition), io_container.end());
    }

    template<class Container, class Condition>
    Container copy_if(const Container& i_container, Condition i_condition)
    {
	Container container_result;
	std::copy_if(i_container.begin(), i_container.end(), std::back_inserter(container_result), i_condition);
	return container_result;
    }

    template <typename T, typename = void>
    struct has_push_back : std::false_type {};

    template <typename T>
    struct has_push_back<T, std::void_t<decltype(std::declval<T>().push_back(std::declval<T::value_type>()))>> : std::true_type {};

    template <typename T>
    constexpr bool has_push_back_v = has_push_back<T>::value;

    template<class ContainerIn, class ContainerOut>
    typename std::enable_if<has_push_back<ContainerOut>::value>::type copy(const ContainerIn& i_container, ContainerOut& o_container)
    {
	o_container.reserve(size(i_container) + size(o_container));
	std::copy(i_container.begin(), i_container.end(), std::back_inserter(o_container));
    }

    template<class ContainerIn, class ContainerOut>
    typename std::enable_if<!has_push_back<ContainerOut>::value>::type copy(const ContainerIn& i_container, ContainerOut& o_container)
    {
	std::copy(i_container.begin(), i_container.end(), std::inserter(o_container, end(o_container)));
    }

    template<class ContainerIn, class ContainerOut, class Condition>
    void copy_if(const ContainerIn& i_container, ContainerOut& o_container, Condition i_condition)
    {
	if constexpr (has_push_back_v<ContainerOut>)
	    std::copy_if(i_container.begin(), i_container.end(), std::back_inserter(o_container), i_condition);
	else
	    std::copy_if(i_container.begin(), i_container.end(), std::inserter(o_container, end(o_container)), i_condition);
    }

    template <class Container, class Condition>
    decltype(auto) partition(Container& io_container, Condition i_condition)
    {
	return std::partition(begin(io_container), end(io_container), i_condition);
    }

    template <class Container, class ContainerOut1, class ContainerOut2, class Condition>
    void partition_copy(
	const Container& i_container,
	ContainerOut1& o_match_condition,
	ContainerOut2& o_not_match_condition,
	Condition i_condition)
    {
	std::partition_copy(
	    cbegin(i_container),
	    cend(i_container),
	    std::back_inserter(o_match_condition),
	    std::back_inserter(o_not_match_condition),
	    i_condition);
    }

    template <class Container>
    void reverse(Container& io_container)
    {
	std::reverse(io_container.begin(), io_container.end());
    }

    struct sum_functor
    {
	template<class T>
	T operator()(T i_sum, T i_value) const
	{
	    return i_sum + i_value;
	}
    };

    template<class Container, class T = int, class Func = sum_functor>
    T accumulate(const Container& i_container, T i_init_value = 0, Func i_func = sum_functor())
    {
	return std::accumulate(i_container.begin(), i_container.end(), i_init_value, i_func);
    }

    template<class Container, class Func = std::equal_to<typename Container::value_type>>
    decltype(auto) adjacent_find(Container& i_container, Func i_func = Func())
    {
	return std::adjacent_find(i_container.begin(), i_container.end(), i_func);
    }

    template<class InContainer, class OutContainer, class Func>
    void transform(const InContainer& i_container, OutContainer& o_container, Func i_transform_function)
    {
	if constexpr (has_push_back_v<OutContainer>)
	{
	    o_container.reserve(size(i_container) + size(o_container));
	    std::transform(i_container.begin(), i_container.end(), std::back_inserter(o_container), i_transform_function);
	}
	else
	{
	    std::transform(i_container.begin(), i_container.end(), std::inserter(o_container, end(o_container)), i_transform_function);
	}
    }

    template <class Container>
    void fill(Container& io_container, typename Container::value_type i_value)
    {
	std::fill(begin(io_container), end(io_container), i_value);
    }

    template <class integral_t = int>
    class indices
    {
	class Iterator
	{
	public:
	    Iterator(integral_t i) : m_i(i) {}
	    integral_t operator++ () { return ++m_i; }
	    integral_t operator*() { return m_i; }
	    bool operator!=(const Iterator& it) const { return m_i != it.m_i; }

	    using iterator_category = std::random_access_iterator_tag;
	    using value_type = integral_t;
	    using difference_type = integral_t;
	    using pointer = integral_t;
	    using reference = void;
	private:
	    integral_t m_i;
	};

	integral_t m_begin = 0;
	integral_t m_end;

    public:
	indices(integral_t n) : m_end(n) {}
	indices(integral_t l, integral_t r) : m_begin(l), m_end(r)
	{
	    static_assert(std::is_integral_v<integral_t>, "Type should be integral");
	    assert(m_begin <= m_end);
	}
	Iterator begin() const { return Iterator(m_begin); }
	Iterator end() const { return Iterator(m_end); }
    };

    template<typename Func, typename Tuple>
    void for_each_element_of_tuple(Tuple&& i_tuple, Func&& i_func)
    {
	std::apply([&i_func](auto& ...x) {(..., i_func(x)); }, i_tuple);
    }

    template<typename Container>
    bool ends_with(const Container& i_container, const Container& i_tail)
    {
	return std::mismatch(std::rbegin(i_container), std::rend(i_container), std::rbegin(i_tail), std::rend(i_tail)).second == std::rend(i_tail);
    }

    template<typename Container>
    bool begins_with(const Container& i_container, const Container& i_begin)
    {
	return std::mismatch(std::begin(i_container), std::end(i_container), std::begin(i_begin), std::end(i_begin)).second == std::end(i_begin);
    }

    template<typename Container>
    bool contains(const Container& i_container, const Container& i_other)
    {
	return std::search(begin(i_container), end(i_container), begin(i_other), end(i_other)) != end(i_container);
    }

    template <typename T, typename = void>
    struct has_find : std::false_type {};

    template <typename T>
    struct has_find<T, std::void_t<decltype(std::declval<T>().find(std::declval<T::key_type>()))>> : std::true_type {};

    template <typename T>
    constexpr bool has_find_v = has_find<T>::value;

    template<typename Container, typename T>
    bool contains(const Container& i_container, const T& i_val)
    {
	if constexpr (has_find_v<Container>)
	    return i_container.find(i_val) != cend(i_container);
	else
	    return find(i_container, i_val) != cend(i_container);
    }

    template<typename Container, typename Condition>
    bool contains_if(const Container& i_container, Condition i_condition)
    {
	return find_if(i_container, i_condition) != cend(i_container);
    }

    template<class Container1, class Container2, class BinaryPredicate = std::equal_to<typename Container1::type_name>>
    bool equal(const Container1& i_container1, const Container2& i_container2, const BinaryPredicate& i_predicate)
    {
	if (i_container1.size() != i_container2.size())
	    return false;

	return std::mismatch(i_container1.begin(), i_container1.end(), i_container2.begin(), i_predicate).first == i_container1.end();
    }

    struct identity
    {
	template <class T>
	T&& operator()(T&& i_val)
	{
	    return std::forward<T>(i_val);
	}
    };

    struct get_first
    {
	template <class T>
	auto operator()(const T& i_val)
	{
	    return std::get<0>(i_val);
	}
    };

    struct get_second
    {
	template <class T>
	auto operator()(const T& i_val)
	{
	    return std::get<1>(i_val);
	}
    };

    template<class ContainerOut, class ContainerIn, class Transform = identity>
    ContainerOut get_as(const ContainerIn& i_container, Transform i_transform = Transform())
    {
	ContainerOut res;
	transform(i_container, res, i_transform);
	return res;
    }

    namespace filter_internals
    {
	template <class Container, class Predicate>
	class filtered_range
	{
	private:
	    template <class container_iterator>
	    class iterator_imp
	    {
	    public:
		using iterator_category = typename container_iterator::iterator_category;
		using value_type = typename container_iterator::value_type;
		using difference_type = typename container_iterator::difference_type;
		using pointer = typename container_iterator::pointer;
		using reference = typename container_iterator::reference;

		iterator_imp(const container_iterator& i_pos, const container_iterator& i_end, Predicate i_predicate)
		    : m_i(i_pos), m_end(i_end), m_pred(std::move(i_predicate))
		{

		}

		iterator_imp& operator=(const iterator_imp& i_other)
		{
		    m_i = i_other.m_i;
		    return *this;
		}

		iterator_imp& operator++()
		{
		    while (m_i != m_end)
		    {
			++m_i;
			if (m_i == m_end || m_pred(*m_i))
			    break;
		    }
		    return *this;
		}

		reference operator*() { return *m_i; }
		bool operator!=(const iterator_imp& it) const { return m_i != it.m_i; }
		bool operator==(const iterator_imp& it) const { return m_i == it.m_i; }
	    private:
		container_iterator m_i;
		const container_iterator m_end;
		Predicate m_pred;
	    };

	public:
	    using iterator = iterator_imp<typename Container::iterator>;
	    using const_iterator = iterator_imp<typename Container::const_iterator>;
	    using iterator_type = std::conditional_t<std::is_same_v<decltype(std::declval<Container>().begin()), typename Container::const_iterator>, const_iterator, iterator>;

	private:
	    iterator_type m_begin;
	    iterator_type m_end;

	public:
	    filtered_range(Container& i_container, Predicate i_predicate) :
		m_begin(find_if(i_container, i_predicate), std::end(i_container), i_predicate),
		m_end(std::end(i_container), std::end(i_container), i_predicate)
	    {

	    }

	    iterator_type begin() const { return m_begin; }
	    iterator_type end() const { return m_end; }
	    bool empty() const { return m_begin == m_end; }
	};
    }

    template <typename T, typename = void>
    struct has_value_type : std::false_type {};

    template <typename T>
    struct has_value_type<T, std::void_t<decltype(std::declval<T::value_type>())>> : std::true_type {};

    template <typename T>
    constexpr bool has_value_type_v = has_value_type<T>::value;

    template <class Container, class Predicate, class ...Args>
    decltype(auto) filtered(Container&& i_cont, Predicate&& i_pred, Args&&... i_args)
    {
	static_assert(!has_value_type_v<Container> || !std::is_rvalue_reference_v<decltype(std::declval<Container&&>())>, "Can not work with rvalue");
	if constexpr (sizeof...(i_args) > 0)
	    return filtered(filter_internals::filtered_range(i_cont, i_pred), std::forward<Args>(i_args)...);
	else
	    return filter_internals::filtered_range(i_cont, i_pred);
    }

    template <class Container>
    Container partial_sum(const Container& i_container)
    {
	Container o_container;
	o_container.reserve(size(i_container));
	std::partial_sum(cbegin(i_container), cend(i_container), std::back_inserter(o_container));
	return o_container;
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

    template <class Container, class Condition>
    decltype(auto) stable_partition(Container& container, Condition condition)
    {
	return std::stable_partition(begin(container), end(container), condition);
    }
}
