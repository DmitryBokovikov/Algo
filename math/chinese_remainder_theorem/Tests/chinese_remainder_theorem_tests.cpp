#include "stdafx.h"
#include "CppUnitTest.h"
#include <math/chinese_remainder_theorem/chinese_remainder_theorem.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math_ns::tests
{		
    TEST_CLASS(chinese_reminder_theorem_tests)
    {
    public:

	TEST_METHOD(test_simple_case)
	{
	    Assert::IsTrue(2 == chinese_remainder_theorem({ 4, 9 }, { 2, 2 }));
	}
    };
}