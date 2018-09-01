#include "stdafx.h"

#include "Util.h"

namespace util_ns
{
    std::vector<int> gen_data(size_t size)
    {
	struct GetRandom
	{
	    GetRandom() : dist_(1, 10000)
	    {
		std::random_device rd;
		mt_ = std::mt19937(rd());
	    }
	    int operator()() { return dist_(mt_); }
	private:
	    std::mt19937 mt_;
	    std::uniform_int_distribution<int> dist_;
	};

	std::vector<int> testData(size);
	std::generate_n(testData.begin(), size, GetRandom());
	return testData;
    }
}
