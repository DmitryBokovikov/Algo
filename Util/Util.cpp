// Util.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "Util.h"

#include <random>
#include <algorithm>
#include <chrono>

namespace util_ns
{
    template<class integral_t = ll>
    struct get_random_struct
    {
	get_random_struct(int i_left = 1, int i_right = 10'000) : m_dist(i_left, i_right)
	{
	    std::random_device rd;
	    m_mt = std::mt19937(rd());
	}
	integral_t operator()() { return m_dist(m_mt); }
    private:
	std::mt19937 m_mt;
	std::uniform_int_distribution<integral_t> m_dist;
    };

    std::vector<ll> gen_data(int i_size, int i_left, int i_right)
    {
	std::vector<ll> test_data(i_size);
	std::generate_n(begin(test_data), i_size, get_random_struct(i_left, i_right));
	return test_data;
    }

    int get_random(int i_start_range, int i_end_range)
    {
	return std::invoke(get_random_struct<int>(i_start_range, i_end_range - 1));
    }

    void random_permutate(std::vector<ll>& io_vec)
    {
	unsigned int seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(begin(io_vec), end(io_vec), std::default_random_engine(seed));
    }
}
