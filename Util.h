#pragma once

#include <vector>
#include <chrono>
#include <random>
#include <iostream>

namespace util_ns
{
    template<class T, class ... Args>
    decltype(auto) spend_time(T func, Args&& ... args)
    {
	using namespace std::chrono;
	auto start = steady_clock::now();
	func(args...);
	return duration_cast<milliseconds>(steady_clock::now() - start).count();
    }

    template<class T, class ... Args>
    void safe_execute(T func, Args&& ... args)
    {
	try {
	    func(args...);
	}
	catch (std::exception& ex) {
	    std::cout << ex.what() << "\n";
	}
	catch (...) {
	    std::cout << "Unexpected exception caught!\n";
	}
    }

    std::vector<int> gen_data(size_t size);

    // TODO : implement RAII thread
}