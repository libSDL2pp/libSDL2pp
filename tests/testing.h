/*
 * Copyright (c) 2011-2013 Dmitry Marakasov <amdmi3@amdmi3.ru>
 * All rights reserved.
 *
 * See https://github.com/AMDmi3/testing.h for updates, bug reports,
 * forks etc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include <iostream>
#include <exception>

// Define NO_TEST_COLOR before including testing.h to disable colors
#ifndef NO_TEST_COLOR
#	define TEST_COLOR
#endif

#define TEST_ESCAPE "\033"

#ifdef TEST_COLOR
#	define PASSED TEST_ESCAPE "[0;32mPASSED:" TEST_ESCAPE "[0m "
#	define FAILED TEST_ESCAPE "[1;31mFAILED:" TEST_ESCAPE "[0m "
#else
#	define PASSED "PASSED: "
#	define FAILED "FAILED: "
#endif

// Test begin/end
#define BEGIN_TEST(...) int main(__VA_ARGS__) { int num_failing_tests_ = 0;

#define END_TEST() if (num_failing_tests_ > 0) std::cerr << num_failing_tests_ << " failures" << std::endl; return num_failing_tests_; }

// Equality checks
#define EXPECT_TRUE(expr) { \
		if (!(expr)) { \
			std::cerr << FAILED #expr << std::endl; \
			++num_failing_tests_; \
		} else { \
			std::cerr << PASSED #expr << std::endl; \
		} \
	}

#define EXPECT_STRING(expr, expected) { \
		std::string result = (expr); \
		if (result != expected) { \
			std::cerr << FAILED #expr " returned \"" << result << "\", while expected \"" << expected << "\"" << std::endl; \
			++num_failing_tests_; \
		} else { \
			std::cerr << PASSED #expr " == \"" << expected << "\"" << std::endl; \
		} \
	}

#define EXPECT_EQUAL(type, expr, expected) { \
		type result = (expr); \
		if (result != expected) { \
			std::cerr << FAILED #expr " returned " << result << ", while expected " << expected << std::endl; \
			++num_failing_tests_; \
		} else { \
			std::cerr << PASSED #expr " == " << expected << std::endl; \
		} \
	}

// Range checks
#define EXPECT_VALUE_IN_RANGE(type, expr, from, to) { \
		type result = (expr); \
		if (from <= result && result <= to) { \
			std::cerr << PASSED #expr " returned " << result << ", which is in range [" << from << ", " << to << "] as expected" << std::endl; \
		} else { \
			std::cerr << FAILED #expr " returned " << result << ", which is out of expected range [" << from << ", " << to << "]" << std::endl; \
			++num_failing_tests_; \
		} \
	}

// Shortcuts for above; feel free to ask to add more
#define EXPECT_INT(expr, expected) EXPECT_EQUAL(int, expr, expected)
#define EXPECT_FLOAT_IN_RANGE(expr, from, to) EXPECT_VALUE_IN_RANGE(float, expr, from, to)

// Exception checks
#define EXPECT_EXCEPTION(expr, exception) { \
		bool correct_catch = false; \
		try { \
			expr; \
		} catch (exception &e) { \
			correct_catch = true; \
		} catch (...) { \
		} \
		if (correct_catch) { \
			std::cerr << PASSED #expr " has thrown " #exception << " as expected " << std::endl; \
		} else { \
			std::cerr << FAILED #expr " hasn't thrown expected " #exception << std::endl; \
			++num_failing_tests_; \
		} \
	}

#define EXPECT_NO_EXCEPTION(expr) { \
		bool had_exception = false; \
		const char* what = NULL; \
		try { \
			expr; \
		} catch (std::exception& e) { \
			had_exception = true; \
			what = e.what(); \
		} catch (...) { \
			had_exception = true; \
		} \
		if (had_exception && what) { \
			std::cerr << FAILED #expr << " has thrown unexpected exception derived from std::exception, what() returned \"" << what << "\"" << std::endl; \
			++num_failing_tests_; \
		} else if (had_exception) { \
			std::cerr << FAILED #expr << " has thrown unexpected exception not derived from std::exception" << std::endl; \
			++num_failing_tests_; \
		} else { \
			std::cerr << PASSED #expr << " hasn't thrown any exceptions as expected" << std::endl; \
		} \
	}

#endif // TESTING_H_INCLUDED
