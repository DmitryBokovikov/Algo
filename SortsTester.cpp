#include "stdafx.h"

#include "SortsTester.h"
#include "Sorts.h"
#include "Util.h"

#include <thread>

namespace tests_ns
{
    SortsTester::SortsTester(std::string fileName) : out_(fileName)
    {
	if (!out_.is_open())
	    throw std::runtime_error("Can not open file " + fileName);

	using namespace algo_ns;
	implementedSorts_ =
	{
	    { "BubbleSort",	    bubble_sort<VIterator> },
	    //{ "DwarfSort",	    dwarf_sort<VIterator> },
	    { "SelectionSort",	    selection_sort<VIterator> }
	    //{ "InsertionSort",  insertion_sort<VIterator> },
	    //{ "MergeSort",	    merge_sort<VIterator> },
	    //{ "QuickSort",	    quick_sort<VIterator> },
	    //{ "HeapSort",	    heap_sort<VIterator> },
	    //{ "RadixSort",	    radix_sort<VIterator> }
	};

	std::thread initSmallCasesThread{ [this]() { InitSmallCases(); } };
	std::thread initBigCaseThread{ [this]() { InitBigCase(); } };
	initSmallCasesThread.join();
	initBigCaseThread.join();
    }

    void SortsTester::InitSmallCases()
    {
	std::vector<int> numbers(SMALL_CASES_NUMBER);
	std::iota(numbers.begin(), numbers.end(), 1);
	smallCases_.reserve(SMALL_CASES_NUMBER);
	std::transform(
	    numbers.begin(),
	    numbers.end(),
	    std::back_inserter(smallCases_),
	    [](int n) { return util_ns::gen_data(n); });

	smallCasesEtalons_.reserve(SMALL_CASES_NUMBER);
	std::transform(
	    smallCases_.begin(),
	    smallCases_.end(),
	    std::back_inserter(smallCasesEtalons_),
	    [](const auto& smallCase)
	{
	    auto caseCopy = smallCase;
	    std::sort(caseCopy.begin(), caseCopy.end());
	    return caseCopy;
	});
    }

    void SortsTester::InitBigCase()
    {
	bigCase_ = util_ns::gen_data(BIG_CASE_LENGTH);
	bigCaseEtalon_ = bigCase_;
	auto spendTime = util_ns::spend_time(std::sort<VIterator>, bigCaseEtalon_.begin(), bigCaseEtalon_.end());
	LogSortTime("std::sort", (int)spendTime);
    }

    void SortsTester::TestAll()
    {
	for (const auto& sort : implementedSorts_)
	    TestSpecific(std::get<sort_name>(sort));
    }

    void SortsTester::TestSpecific(std::string_view sort)
    {
	auto it = implementedSorts_.find(sort.data());
	if (implementedSorts_.end() == it)
	    throw std::runtime_error(std::string("Couldn't find sort alg with name ") + sort.data());

	TestOnSmallCases(*it);
	TestOnBigCase(*it);
    }

    void SortsTester::TestOnSmallCases(const SortPair& sortPair)
    {
	auto[name, sortFunc] = sortPair;
	for (size_t i = 0; i < size(smallCasesEtalons_); ++i)
	{
	    auto caseCopy = smallCasesEtalons_[i];
	    sortFunc(caseCopy.begin(), caseCopy.end());
	    if (caseCopy != smallCasesEtalons_[i])
		throw std::runtime_error("Error in implementaion of " + name);
	}
    }

    void SortsTester::TestOnBigCase(const SortPair& sortPair)
    {
	auto[name, sortFunc] = sortPair;
	auto caseCopy = bigCase_;
	auto spendTime = util_ns::spend_time(sortFunc, caseCopy.begin(), caseCopy.end());
	if (caseCopy != bigCaseEtalon_)
	    throw std::runtime_error("Error in implementaion of " + name);
	LogSortTime(name, (int)spendTime);
    }

    void SortsTester::LogSortTime(std::string_view name, int milliseconds)
    {
	out_ << std::setw(15) << std::left << name << " : ";
	out_ << std::setw(12) << milliseconds << " milliseconds\n";
    }
}
