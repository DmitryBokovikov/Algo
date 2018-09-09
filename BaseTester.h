#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <fstream>

namespace tests_ns
{
    class tester_base
    {
    public:
	tester_base(std::string_view out_file_name);
	void test_all();
	void test_specific(const std::string& func_name);
    protected:
	using ll = long long;
	using test = std::vector<ll>;
	using tests = std::vector<std::vector<ll>>;
	using test_functions_map = std::unordered_map<std::string, std::function<std::vector<ll>(std::vector<ll>)>>;
	using test_functions_map_type = std::pair<test_functions_map::key_type, test_functions_map::mapped_type>;

	void test_on_small_cases();
	void test_on_long_cases();
	void test_separated_func(
	    const test_functions_map_type& test_function, 
	    const tests& cases, 
	    const tests& etalons, 
	    bool need_log = false);
	void init_test_cases();
	void init_small_cases();
	void init_long_cases();
	void test_on_cases(const tests& cases, const tests& etalons, bool need_log = false);
	void log_func_time(std::string_view name, int milliseconds);

	void init();

	virtual bool has_fast_complexity(const std::string& func_name) { return true; }
	virtual void init_test_functions() = 0;
	virtual void init_etalon_function() = 0;
    protected:
	tests small_cases_;
	tests small_cases_etalons_;
	tests big_cases_;
	tests big_cases_etalons_;
	test_functions_map test_functions;
	test_functions_map_type etalon_function;
	std::ofstream out_;

    private:
	static constexpr size_t BIG_CASE_LENGTH = 1'000'000;
	static constexpr size_t SMALL_CASES_NUMBER = 100;
    };
}
