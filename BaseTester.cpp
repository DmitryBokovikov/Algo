#include "stdafx.h"

#include "BaseTester.h"
#include "Util.h"

#include <future>

namespace tests_ns
{
    tester_base::tester_base(std::string_view out_file_name) : out_(out_file_name.data())
    {
	if (!out_.is_open())
	    throw std::runtime_error(std::string("Can not open file ") + out_file_name.data());
    }

    void tester_base::init()
    {
	init_test_functions();
	init_etalon_function();
	init_test_cases();
    }

    void tester_base::test_all()
    {
	for (const auto& func : test_functions)
	    test_specific(func.first);
    }

    void tester_base::test_specific(const std::string& func_name)
    {
	auto it = test_functions.find(func_name);
	if (test_functions.end() == it)
	    throw std::runtime_error("Couldn't find func with name " + func_name);

	test_separated_func(*it, small_cases_, small_cases_etalons_);
	if (has_fast_complexity(func_name))
	    test_separated_func(*it, big_cases_, big_cases_etalons_, true);
    }

    void tester_base::test_on_small_cases()
    {
	test_on_cases(small_cases_, small_cases_etalons_);
    }

    void tester_base::test_on_long_cases()
    {
	test_on_cases(big_cases_, big_cases_etalons_, true);
    }

    void tester_base::test_on_cases(const tests& cases, const tests& etalons, bool need_log)
    {
	for (const auto& test_func : test_functions)
	    test_separated_func(test_func, cases, etalons, need_log);
    }

    void tester_base::test_separated_func(
	const test_functions_map_type& test_function, 
	const tests& cases, 
	const tests& etalons, 
	bool need_log)
    {
	auto[func_name, func] = test_function;
	for (size_t i = 0; i < size(etalons); ++i)
	{
	    const auto& case_copy = cases[i];
	    auto[res, time_spend] = util_ns::spend_time(func, case_copy);
	    if (res != etalons[i])
		throw std::runtime_error("Error in implementaion of " + func_name);
	    if (need_log)
		log_func_time(func_name, (int)time_spend);
	}
    }

    void tester_base::init_test_cases()
    {
	std::future<void> small_case_future = std::async([this]() { init_small_cases(); });
	std::future<void> long_cases_future = std::async([this]() { init_long_cases(); });
	small_case_future.get();
	long_cases_future.get();
    }

    void tester_base::init_small_cases()
    {
	std::vector<int> numbers(SMALL_CASES_NUMBER);
	std::iota(numbers.begin(), numbers.end(), 1);
	small_cases_.reserve(SMALL_CASES_NUMBER);
	std::transform(
	    numbers.begin(),
	    numbers.end(),
	    std::back_inserter(small_cases_),
	    [](int n) { return util_ns::gen_data(n); });

	small_cases_etalons_.reserve(SMALL_CASES_NUMBER);
	std::transform(
	    small_cases_.begin(),
	    small_cases_.end(),
	    std::back_inserter(small_cases_etalons_),
	    [this](const auto& small_case)
	{
	    return etalon_function.second(small_case);
	});
    }

    void tester_base::init_long_cases()
    {
	auto long_case = util_ns::gen_data(BIG_CASE_LENGTH);
	auto[long_case_etalon, ms_spend] = util_ns::spend_time(etalon_function.second, long_case);
	log_func_time(etalon_function.first, (int)ms_spend);
	big_cases_.push_back(std::move(long_case));
	big_cases_etalons_.push_back(std::move(long_case_etalon));
    }

    void tester_base::log_func_time(std::string_view name, int milliseconds)
    {
	out_ << std::setw(15) << std::left << name << " : ";
	out_ << std::setw(12) << milliseconds << " milliseconds\n";
    }
}
