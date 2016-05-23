/*
 * Copyright (c) 2011-2016 Dmitry Marakasov <amdmi3@amdmi3.ru>
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
#include <string>
#include <sstream>
#include <functional>

#ifdef _WIN32
#	define TESTING_NO_COLOR
#endif

//
// Helper class for literal quoting / extra processing
//
// You may instance this template for printing your own classes
//
template<class T>
std::string QuoteLiteral(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

template<>
std::string QuoteLiteral<std::string>(std::string value) {
	return std::string("\"") + value + std::string("\"");
}

template<>
std::string QuoteLiteral<const char*>(const char* value) {
	return std::string("\"") + value + std::string("\"");
}

//
// Test registry
//
class Tester {
private:
	int num_tests_;               // Total numer of tests registered
	int num_failures_;            // Number of tests failed
	bool use_color_;              // Whether to use color

	bool unexpected_exception_;   // Whether unexpected exception was encountered

	int permanent_flags_;         // Flags which affect each test invocation

public:
	// Test results
	enum Result {
		PASS,
		FAIL,
		WARN,
	};

	// Flags to control test bahavior
	enum Flags {
		NON_FATAL = 0x01,
		HIDE_MESSAGE = 0x02,
	};

	// Styles for coloring
	enum Styles {
		PASS_BANNER,
		FAIL_BANNER,
		WARN_BANNER,
		LITERAL,
		EXPRESSION,
		DESCRIPTION,
	};

	// Dummy type for preprocessor magic to happen
	struct DummyArgument {
	};

private:
	//
	// Apply named style to a string
	//
	std::string Stylify(Styles style, const std::string& str) const {
		if (!use_color_)
			return str;

		bool bright = false;
		int color = 0;

		switch (style) {
		case PASS_BANNER: bright = false; color = 2; break;
		case WARN_BANNER: bright =  true; color = 3; break;
		case FAIL_BANNER: bright =  true; color = 1; break;
		case LITERAL:     bright =  true; color = 5; break;
		case EXPRESSION:  bright =  true; color = 7; break;
		case DESCRIPTION: bright =  true; color = 4; break;
		default:
			return str;
		}

		std::ostringstream ss;
		ss << "\033[" << (bright ? '1' : '0') << ';' << (30 + color) << 'm' << str << "\033[0m";
		return ss.str();
	}

	//
	// Main test handling routine
	//
	// This method handles test counters and formats messages
	//
	void RegisterTest(bool passed, int flags, const std::string& message, const std::string& description) {
		num_tests_++;

		if (passed) {
			std::cerr << Stylify(PASS_BANNER, "PASS: ");
		} else if ((flags | permanent_flags_) & NON_FATAL) {
			std::cerr << Stylify(WARN_BANNER, "WARN: ");
		} else {
			std::cerr << Stylify(FAIL_BANNER, "FAIL: ");
			num_failures_++;
		}

		if ((flags | permanent_flags_) & HIDE_MESSAGE && !description.empty()) {
			std::cerr << description;
		} else {
			std::cerr << message;
			if (!description.empty())
				std::cerr << " " << Stylify(DESCRIPTION, std::string("// ") + description);
		}
		std::cerr << std::endl;
	}

public:
	Tester() : num_tests_(0), num_failures_(0), use_color_(true), unexpected_exception_(false), permanent_flags_(0) {
#ifdef TESTING_NO_COLOR
		use_color_ = false;
#endif
	}

	void EnableColor(bool enable) {
		use_color_ = enable;
	}

	void EnableFlags(int flags) {
		permanent_flags_ |= flags;
	}

	void DisableFlags(int flags) {
		permanent_flags_ &= ~flags;
	}

	void ResetFlags() {
		permanent_flags_ = 0;
	}

	// ExpectTrue
	void ExpectTrue(const std::string& expression_str, bool sample, const std::string& description, int flags, DummyArgument) {
		RegisterTest(sample, flags, Stylify(EXPRESSION, expression_str), description);
	}

	// ExpectEqual
	template<class T1, class T2>
	void ExpectEqual(const std::string& expression_str, const T1& sample, const T2& expected, const std::string& description, int flags, DummyArgument) {
		std::string message;

		if (sample == expected)
			message = Stylify(EXPRESSION, expression_str) + " returned " + Stylify(LITERAL, QuoteLiteral(sample)) + " as expected";
		else
			message = Stylify(EXPRESSION, expression_str) + " returned " + Stylify(LITERAL, QuoteLiteral(sample)) + " while expected " + Stylify(LITERAL, QuoteLiteral(expected));

		RegisterTest(sample == expected, flags, message, description);
	}

	// ExpectException
	template<class E>
	void ExpectException(const std::string& expression_str, std::function<void()>&& func, const std::string& exception_str, const std::string& description, int flags, DummyArgument) {
		bool as_expected = false;
		bool thrown = false;
		bool std_exception = false;

		std::string what;

		try {
			func();
		} catch (E&) {
			as_expected = true;
			thrown = true;
		} catch (std::exception& e) {
			thrown = true;
			std_exception = true;
			what = e.what();
		} catch (...) {
			thrown = true;
		}

		std::string message;

		if (thrown && as_expected)
			message = Stylify(EXPRESSION, expression_str) + " has thrown " + Stylify(EXPRESSION, exception_str) + " as expected";
		else if (thrown && std_exception)
			message = Stylify(EXPRESSION, expression_str) + " has thrown unexpected exception derived from std::exception (what(): " + Stylify(LITERAL, what) + "), while expected " + Stylify(EXPRESSION, exception_str);
		else if (thrown)
			message = Stylify(EXPRESSION, expression_str) + " has thrown unexpected exception not derived from std::exception, while expected " + Stylify(EXPRESSION, exception_str);
		else
			message = Stylify(EXPRESSION, expression_str) + " hasn't thrown expected exception " + Stylify(EXPRESSION, exception_str);

		RegisterTest(thrown && as_expected, flags, message, description);
	}

	// ExpectNoException
	void ExpectNoException(const std::string& expression_str, std::function<void()>&& func, const std::string& description, int flags, DummyArgument) {
		bool thrown = false;
		bool std_exception = false;

		std::string what;

		try {
			func();
		} catch (std::exception& e) {
			thrown = true;
			std_exception = true;
			what = e.what();
		} catch (...) {
			thrown = true;
		}

		std::string message;

		if (thrown && std_exception)
			message = Stylify(EXPRESSION, expression_str) + " has thrown unexpected exception derived from std::exception (what(): " + Stylify(LITERAL, what) + ")";
		else if (thrown)
			message = Stylify(EXPRESSION, expression_str) + " has thrown unexpected exception not derived from std::exception";
		else
			message = Stylify(EXPRESSION, expression_str) + " hasn't thrown any exceptions as expected";

		RegisterTest(!thrown, flags, message, description);
	}

	// ExpectTrue overloads
	void ExpectTrue(const std::string& expression_str, bool sample, DummyArgument dummy) {
		ExpectTrue(expression_str, sample, "", 0, dummy);
	}

	void ExpectTrue(const std::string& expression_str, bool sample, const std::string& description, DummyArgument dummy) {
		ExpectTrue(expression_str, sample, description, 0, dummy);
	}

	void ExpectTrue(const std::string& expression_str, bool sample, int flags, DummyArgument dummy) {
		ExpectTrue(expression_str, sample, "", flags, dummy);
	}

	// ExpectEqual overloads
	template<class T1, class T2>
	void ExpectEqual(const std::string& expression_str, const T1& sample, const T2& expected, DummyArgument dummy) {
		return ExpectEqual<T1, T2>(expression_str, sample, expected, "", 0, dummy);
	}

	template<class T1, class T2>
	void ExpectEqual(const std::string& expression_str, const T1& sample, const T2& expected, const std::string& description, DummyArgument dummy) {
		return ExpectEqual<T1, T2>(expression_str, sample, expected, description, 0, dummy);
	}

	template<class T1, class T2>
	void ExpectEqual(const std::string& expression_str, const T1& sample, const T2& expected, int flags, DummyArgument dummy) {
		return ExpectEqual<T1, T2>(expression_str, sample, expected, "", flags, dummy);
	}

	// ExpectException overloads
	template<class E>
	void ExpectException(const std::string& expression_str, std::function<void()>&& func, const std::string& exception_str, DummyArgument dummy) {
		return ExpectException<E>(expression_str, std::move(func), exception_str, "", 0, dummy);
	}

	template<class E>
	void ExpectException(const std::string& expression_str, std::function<void()>&& func, const std::string& exception_str, const std::string& description, DummyArgument dummy) {
		return ExpectException<E>(expression_str, std::move(func), exception_str, description, 0, dummy);
	}

	template<class E>
	void ExpectException(const std::string& expression_str, std::function<void()>&& func, const std::string& exception_str, int flags, DummyArgument dummy) {
		return ExpectException<E>(expression_str, std::move(func), exception_str, "", flags, dummy);
	}

	// ExpectNoException overloads
	void ExpectNoException(const std::string& expression_str, std::function<void()>&& func, DummyArgument dummy) {
		return ExpectNoException(expression_str, std::move(func), "", 0, dummy);
	}

	void ExpectNoException(const std::string& expression_str, std::function<void()>&& func, const std::string& description, DummyArgument dummy) {
		return ExpectNoException(expression_str, std::move(func), description, 0, dummy);
	}

	void ExpectNoException(const std::string& expression_str, std::function<void()>&& func, int flags, DummyArgument dummy) {
		return ExpectNoException(expression_str, std::move(func), "", flags, dummy);
	}

	void RegisterUnexpectedException() {
		unexpected_exception_ = true;
	}

	void PrintSummary() {
		std::cerr << num_failures_ << " failure(s) out of " << num_tests_ << " tests";
		if (unexpected_exception_)
			std::cerr << ", and was terminated prematurely due to unexpected exception";
		std::cerr << "\n";
	}

	int GetExitCode() {
		return num_failures_ || unexpected_exception_;
	}
};

// core macros
#define BEGIN_TEST(...) \
	int main(__VA_ARGS__) { \
		Tester tester_; \
		try {

#define HANDLE_EXCEPTION(exception) \
		} catch(exception) { \
			tester_.RegisterUnexpectedException();

#define END_TEST() \
		} catch(std::exception& e) { \
			tester_.RegisterUnexpectedException(); \
			std::cerr << "unexpected exception was thrown during the test: " << e.what() << std::endl; \
		} catch (...) { \
			tester_.RegisterUnexpectedException(); \
			std::cerr << "unexpected exception was thrown during the test" << std::endl; \
		} \
		tester_.PrintSummary(); \
		return tester_.GetExitCode(); \
	}

// wrappers to allow true variable number of arguments
#define METHOD_WRAPPER(method, expr, ...) tester_.method(#expr, expr, __VA_ARGS__)
#define METHOD_WRAPPER_EXCEPTION(expr, exception, ...) tester_.ExpectException<exception>(#expr, [&](){expr;}, #exception, __VA_ARGS__)
#define METHOD_WRAPPER_NO_EXCEPTION(expr, ...) tester_.ExpectNoException(#expr, [&](){expr;}, __VA_ARGS__)

// checks
#ifdef _MSC_VER
#	define EXPECT_TRUE(expr, ...)      do { tester_.ExpectTrue(#expr, expr, __VA_ARGS__, Tester::DummyArgument()); } while(0)
#	define EXPECT_EQUAL(expr, ...)     do { tester_.ExpectEqual(#expr, expr, __VA_ARGS__, Tester::DummyArgument()); } while(0)
#	define EXPECT_EXCEPTION(expr, exception, ...) do { tester_.ExpectException<exception>(#expr, [&](){expr;}, #exception, __VA_ARGS__, Tester::DummyArgument()); } while(0)
#	define EXPECT_NO_EXCEPTION(expr, ...) do { tester_.ExpectNoException(#expr, [&](){expr;}, __VA_ARGS__, Tester::DummyArgument()); } while(0)
#else
#	define EXPECT_TRUE(...)      do { METHOD_WRAPPER(ExpectTrue, __VA_ARGS__, Tester::DummyArgument()); } while(0)
#	define EXPECT_EQUAL(...)     do { METHOD_WRAPPER(ExpectEqual, __VA_ARGS__, Tester::DummyArgument()); } while(0)
#	define EXPECT_EXCEPTION(...) do { METHOD_WRAPPER_EXCEPTION(__VA_ARGS__, Tester::DummyArgument()); } while(0)
#	define EXPECT_NO_EXCEPTION(...) do { METHOD_WRAPPER_NO_EXCEPTION(__VA_ARGS__, Tester::DummyArgument()); } while(0)
#endif

// functions
#define ENABLE_FLAGS(flags) do { tester_.EnableFlags(flags); } while(0)
#define DISABLE_FLAGS(flags) do { tester_.DisableFlags(flags); } while(0)
#define RESET_FLAGS() do { tester_.ResetFlags(); } while(0)

// flags
#define NON_FATAL Tester::NON_FATAL
#define HIDE_MESSAGE Tester::HIDE_MESSAGE

#endif // TESTING_H_INCLUDED
