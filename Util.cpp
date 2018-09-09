#include "stdafx.h"

#include "Util.h"

namespace util_ns
{
    std::vector<long long> gen_data(size_t size)
    {
	struct GetRandom
	{
	    GetRandom() : dist_(1, 10000)
	    {
		std::random_device rd;
		mt_ = std::mt19937(rd());
	    }
	    long long operator()() { return dist_(mt_); }
	private:
	    std::mt19937 mt_;
	    std::uniform_int_distribution<long long> dist_;
	};

	std::vector<long long> testData(size);
	std::generate_n(testData.begin(), size, GetRandom());
	return testData;
    }
}
