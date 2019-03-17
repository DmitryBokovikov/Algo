#pragma once

#include "UtilAPI.h"

#include <vector>

using ll = long long;

namespace util_ns
{
    std::vector<ll> UTIL_API gen_data(int i_size, int i_left = 1, int i_right = 10'000);

    int UTIL_API get_random(int i_start_range, int i_end_range);

    template <class Container>
    ll lsize(const Container& i_container)
    {
	return static_cast<ll>(size(i_container));
    }

    template <class Container>
    int isize(const Container& i_container)
    {
	return static_cast<int>(size(i_container));
    }

    template <class T = int>
    T constexpr INF = std::numeric_limits<T>::max;
}

