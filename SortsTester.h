#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <functional>
#include <vector>
#include <fstream>

namespace tests_ns
{
    class SortsTester
    {
    public:
	SortsTester(std::string fileName = "sorts_out.txt");

	enum class SortName
	{
	    bubble_sort,
	    dwarf_sort,
	    selection_sort,
	    insertion_sort,
	    merge_sort,
	    quick_sort,
	    heap_sort,
	    radix_sort
	};

	void TestAll();
	void TestSpecific(const SortName& sortName);

    private:
	using VIterator = std::vector<int>::iterator;
	using SortFunc = std::function<void(VIterator, VIterator)>;
	using SortsMap = std::unordered_map<SortName, SortFunc>;
	using SortPair = SortsMap::value_type;
	enum SortHashMapValue { sort_name, sort_func };

	void TestOnSmallCases(const SortPair& sortPair);
	void TestOnBigCase(const SortPair& sortPair);
	void InitSmallCases();
	void InitBigCase();
	void LogSortTime(std::string_view name, int milliseconds);
	std::string SortIdToString(const SortName& sortId);
	bool HasFastComplexity(const SortName& sortId);

    private:
	std::vector<std::vector<int>> smallCases_;
	std::vector<std::vector<int>> smallCasesEtalons_;
	std::vector<int> bigCase_;
	std::vector<int> bigCaseEtalon_;
	SortsMap implementedSorts_;
	std::ofstream out_;

	static constexpr size_t BIG_CASE_LENGTH = 1'000'000;
	static constexpr size_t SMALL_CASES_NUMBER = 100;
    };
}
