// Util.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "Util.h"

#include <random>
#include <algorithm>

namespace util_ns
{
    std::vector<ll> gen_data(int i_size, int i_left, int i_right)
    {
	struct get_random
	{
	    get_random(int i_left = 1, int i_right = 10'000) : m_dist(i_left, i_right)
	    {
		std::random_device rd;
		m_mt = std::mt19937(rd());
	    }
	    long long operator()() { return m_dist(m_mt); }
	private:
	    std::mt19937 m_mt;
	    std::uniform_int_distribution<long long> m_dist;
	};

	std::vector<ll> test_data(i_size);
	std::generate_n(begin(test_data), i_size, get_random(i_left, i_right));
	return test_data;
    }
}
