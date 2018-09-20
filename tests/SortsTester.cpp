#include "stdafx.h"

#include "SortsTester.h"
#include "Sorts.h"

namespace tests_ns
{
    sorts_tester::sorts_tester(std::string_view out_file_name) : tester_base(out_file_name) 
    {
	init();
    }

    bool sorts_tester::has_fast_complexity(const std::string& func_name)
    {
	auto sort_id = string_to_sort_id(func_name);
	switch (sort_id)
	{
	case sort_name::merge_sort:
	case sort_name::quick_sort:
	case sort_name::heap_sort:
	case sort_name::radix_sort:
	case sort_name::selection_sort_fast:
	    return true;
	default:
	    return false;
	}
    }
    void sorts_tester::init_test_functions()
    {
	using namespace algo_ns;
	implemented_sorts_ =
	{
	    { sort_name::bubble_sort,		bubble_sort<VLIterator> },
	    //{ "DwarfSort",			dwarf_sort<VLIterator> },
	    { sort_name::selection_sort,	selection_sort<VLIterator> },
	    { sort_name::selection_sort_fast,	selection_sort_fast<VLIterator> },
	    { sort_name::insertion_sort,	insertion_sort<VLIterator> },
	    { sort_name::merge_sort,		merge_sort<VLIterator> },
	    { sort_name::quick_sort,		quick_sort<VLIterator> }
	    //{ "HeapSort",			heap_sort<VLIterator> },
	    //{ "RadixSort",			radix_sort<VLIterator> }
	};

	for (const auto& impl_sort : implemented_sorts_)
	    test_functions.emplace(
		sort_id_to_string(impl_sort.first), 
		[&impl_sort](const std::vector<ll>& vec) 
		{ 
		    std::vector<ll> ans(vec);  
		    impl_sort.second(ans.begin(), ans.end()); 
		    return ans; 
		}
	    );
    }

    void sorts_tester::init_etalon_function()
    {
	etalon_function = test_functions_map_type(
	    "std::sort",
	    [](const std::vector<ll>& vec)
	    {
		std::vector<ll> ans(vec);
		std::sort(ans.begin(), ans.end());
		return ans;
	    });
    }

    std::string sorts_tester::sort_id_to_string(const sort_name& sort_id)
    {
	switch (sort_id)
	{
	case sort_name::bubble_sort:
	    return "bubble_sort";
	case sort_name::dwarf_sort:
	    return "dwarf_sort";
	case sort_name::selection_sort:
	    return "selection_sort";
	case sort_name::selection_sort_fast:
	    return "selection_sort_fast";
	case sort_name::insertion_sort:
	    return "insertion_sort";
	case sort_name::merge_sort:
	    return "merge_sort";
	case sort_name::quick_sort:
	    return "quick_sort";
	case sort_name::heap_sort:
	    return "heap_sort";
	case sort_name::radix_sort:
	    return "radix_sort";
	default:
	    throw std::runtime_error("Unexpected value in " + std::string(__func__));
	}   
    }

    sorts_tester::sort_name sorts_tester::string_to_sort_id(const std::string& sort)
    {
	if (sort == "bubble_sort")
	    return sort_name::bubble_sort;
	if (sort == "dwarf_sort")
	    return sort_name::dwarf_sort;
	if (sort == "selection_sort")
	    return sort_name::selection_sort;
	if (sort == "selection_sort_fast")
	    return sort_name::selection_sort_fast;
	if (sort == "insertion_sort")
	    return sort_name::insertion_sort;
	if (sort == "merge_sort")
	    return sort_name::merge_sort;
	if (sort == "quick_sort")
	    return sort_name::quick_sort;
	if (sort == "heap_sort")
	    return sort_name::heap_sort;
	if (sort == "radix_sort")
	    return sort_name::radix_sort;

	throw std::runtime_error("Unexpected value " + sort + "in " + std::string(__func__));
    }
}
