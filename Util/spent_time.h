#pragma once

#include <chrono>
#include <functional>

namespace util_ns
{
    template<class Func, class ...Args>
    auto spent_time(Func func, Args&& ...args)
    {
	using namespace std::chrono;
	auto start = steady_clock::now();
	auto res = func(args...);
	auto millisecond_spend = duration_cast<milliseconds>(steady_clock::now() - start).count();
	return std::pair(res, millisecond_spend);
    }

}