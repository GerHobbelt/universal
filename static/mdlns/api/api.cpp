// api.cpp: application programming interface demonstration of fixed-size, arbitrary precision multi-dimensional logarithmic number systems
//
// Copyright (C) 2022-2022 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
// minimum set of include files to reflect source code dependencies
#include <universal/number/mdlns/mdlns.hpp>
#include <universal/number/cfloat/cfloat.hpp>  // bit field comparisons
#include <universal/verification/test_suite.hpp>

// Regression testing guards: typically set by the cmake configuration, but MANUAL_TESTING is an override
#define MANUAL_TESTING 0
// REGRESSION_LEVEL_OVERRIDE is set by the cmake file to drive a specific regression intensity
// It is the responsibility of the regression test to organize the tests in a quartile progression.
//#undef REGRESSION_LEVEL_OVERRIDE
#ifndef REGRESSION_LEVEL_OVERRIDE
#undef REGRESSION_LEVEL_1
#undef REGRESSION_LEVEL_2
#undef REGRESSION_LEVEL_3
#undef REGRESSION_LEVEL_4
#define REGRESSION_LEVEL_1 1
#define REGRESSION_LEVEL_2 1
#define REGRESSION_LEVEL_3 1
#define REGRESSION_LEVEL_4 1
#endif

int main()
try {
	using namespace sw::universal;

	std::string test_suite  = "mdlns API demonstration";
	std::string test_tag    = "api";
	bool reportTestCases    = false;
	int nrOfFailedTestCases = 0;

	ReportTestSuiteHeader(test_suite, reportTestCases);

	// important behavioral traits
//	ReportTrivialityOfType<mdlns<8, 2>>();  // TODO: type_tag fails for mdlns

	// default behavior
	{
		std::cout << "+---------    default mdmdlns bahavior   --------+\n";
		using Real = mdlns<8, 3>;
		Real a(1.0f), b(1.0f), c;
//		ArithmeticOperators<Real>(a, b);
		a = 1;  // integer assignment
		b = 1;
		c = a + b;
//		ReportBinaryOperation(a, "+", b, c);
	}

	// configuration
	{
		std::cout << "+---------    arithmetic operators with explicit alignment bahavior   --------+\n";
//		using mdlns16 = mdlns<16, 5, std::uint16_t>;
//		ArithmeticOperators<mdlns16>(1.0f, 1.0f);

//		using mdlns24 = mdlns<24, 5, std::uint32_t>;
//		ArithmeticOperators<mdlns24>(1.0f, 1.0f);
	}

	{
		std::cout << "+---------    Dynamic ranges of mdlns<> configurations   --------+\n";
//		std::cout << dynamic_range(mdlns< 4, 2>()) << '\n';
//		std::cout << dynamic_range(mdlns< 8, 3>()) << '\n';
//		std::cout << dynamic_range(mdlns<12, 4>()) << '\n';
//		std::cout << dynamic_range(mdlns<16, 5>()) << '\n';
//		std::cout << dynamic_range(mdlns<20, 6>()) << '\n';
	}

	{
		std::cout << "+---------    constexpr and specific values   --------+\n";
		constexpr size_t nbits = 10;
		constexpr size_t rbits = 3;
		using Real = mdlns<nbits, rbits>;  // BlockType = uint8_t, behavior = Saturating

//		CONSTEXPRESSION Real a{}; // zero constexpr
//		std::cout << type_tag<Real>(a) << '\n';  // TODO: type_tag doesn't work for mdlns

		// TODO: needs a constexpr version of log2() function
//		CONSTEXPRESSION Real b(1.0f);  // constexpr of a native type conversion
//		std::cout << to_binary(b) << " : " << b << '\n';

		CONSTEXPRESSION Real c(SpecificValue::minpos);  // constexpr of a special value in the encoding
		std::cout << to_binary(c) << " : " << c << " == minpos" << '\n';

		CONSTEXPRESSION Real d(SpecificValue::maxpos);  // constexpr of a special value in the encoding
		std::cout << to_binary(d) << " : " << d << " == maxpos" << '\n';
	}

	{
		std::cout << "+---------    extreme values   --------+\n";
		constexpr size_t nbits = 10;
		constexpr size_t rbits = 3;
		using Real = mdlns<nbits, rbits>;  // BlockType = uint8_t, behavior = Saturating

		Real a, b, c;

		a = INFINITY;
		b = 2;
		c = a / b;
		std::cout << "scale(" << a << ") = " << a.scale() << '\n';
		std::cout << "scale(" << b << ") = " << b.scale() << '\n';
		ReportBinaryOperation(a, "/", b, c);
	}

	{
		std::cout << "+---------    exceptions   ---------+\n";
		using mdlns = sw::universal::mdlns<16, 8, uint16_t>;
		mdlns a = mdlns(0.0f);
		mdlns b = -mdlns(0.0);
		// if (a != b) std::cout << "you can't compare indeterminate NaN\n";
		if (a.isnan() && b.isnan()) std::cout << "PASS: both +mdlns(0) and -mdlns(0) are indeterminate\n";
		std::cout << "+mdlns(0.0f): " <<  mdlns(0.0f) << "\n";
		std::cout << "-mdlns(0.0f): " << -mdlns(0.0f) << "\n";
	}

	{
		std::cout << "+---------    dynamic ranges of 8-bit mdlns<> configurations   --------+\n";
//		std::cout << dynamic_range(mdlns<8, 0>()) << '\n';
//		std::cout << dynamic_range(mdlns<8, 1>()) << '\n';
//		std::cout << dynamic_range(mdlns<8, 2>()) << '\n';
//		std::cout << dynamic_range(mdlns<8, 3>()) << '\n';
//		std::cout << dynamic_range(mdlns<8, 4>()) << '\n';
//		std::cout << dynamic_range(mdlns<8, 5>()) << '\n';
//		std::cout << dynamic_range(mdlns<8, 6>()) << '\n';
	}

	{
		std::cout << "+---------    comparison to classic floats   --------+\n";
		using MDLNS = mdlns<16, 8, std::uint16_t>;
		using Real = cfloat<16, 5, std::uint16_t>;
		MDLNS a;
		Real b;
		static_assert(std::is_trivially_constructible<MDLNS>(), "mdlns<> is not trivially constructible");
		a = 1;
//		std::cout << std::setw(80) << type_tag(a) << " : " << to_binary(a, true) << " : " << color_print(a, true) << " : " << float(a) << '\n';
		b = 1;
		std::cout << std::setw(80) << type_tag(b) << " : " << to_binary(b, true) << " : " << color_print(b, true) << " : " << float(b) << '\n';
	}
	
	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}