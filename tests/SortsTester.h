#pragma once

#include "BaseTester.h"

namespace tests_ns
{
    class sorts_tester : public tester_base<std::function<std::vector<long long>(std::vector<long long>)>>
    {
	public:
		sorts_tester(std::string_view out_file_name);
	private:
		bool has_fast_complexity(const std::string& func_name) final;
		void init_test_functions() final;
		void init_etalon_function() final;

		enum class sort_name
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

		using VLIterator = std::vector<ll>::iterator;
		using sort_func = std::function<void(VLIterator, VLIterator)>;
		using sorts_map = std::unordered_map<sort_name, sort_func>;

		std::string sort_id_to_string(const sort_name& sort_id);
		sort_name string_to_sort_id(const std::string& sort);
		private:
		sorts_map implemented_sorts_;
    };
}
