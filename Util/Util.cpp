// Util.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "Util.h"

#include <random>
#include <algorithm>

namespace util_ns
{
    struct get_random_struct
    {
	get_random_struct(int i_left = 1, int i_right = 10'000) : m_dist(i_left, i_right)
	{
	    std::random_device rd;
	    m_mt = std::mt19937(rd());
	}
	long long operator()() { return m_dist(m_mt); }
    private:
	std::mt19937 m_mt;
	std::uniform_int_distribution<long long> m_dist;
    };

    std::vector<ll> gen_data(int i_size, int i_left, int i_right)
    {
	std::vector<ll> test_data(i_size);
	std::generate_n(begin(test_data), i_size, get_random_struct(i_left, i_right));
	return test_data;
    }

    int get_random(int i_start_range, int i_end_range)
    {
	return std::invoke(get_random_struct(i_start_range, i_end_range - 1));
    }
}
