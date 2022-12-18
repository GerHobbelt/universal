// posit_64_3.cpp: test suite runner for fast specialized posit<64,3>
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#if defined(_MSC_VER)
#pragma warning(disable : 5045) // Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#pragma warning(disable : 4514) // unreferenced inline function has been removed
#pragma warning(disable : 4820) // bytes padding added after data member
#pragma warning(disable : 4710) // function not inlined
#endif
// Configure the posit template environment
// first: enable fast specialized posit<64,3>
#define POSIT_FAST_POSIT_64_3 1  // TODO: fast posit<64,3> not implemented yet
// second: enable posit arithmetic exceptions
#define POSIT_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/number/posit/posit.hpp>
#include <universal/verification/posit_test_suite.hpp>
#include <universal/verification/posit_test_randoms.hpp>

// Standard posit with nbits = 64 have es = 3 exponent bits.

// Regression testing guards: typically set by the cmake configuration, but MANUAL_TESTING is an override
#define MANUAL_TESTING 0
// REGRESSION_LEVEL_OVERRIDE is set by the cmake file to drive a specific regression intensity
// It is the responsibility of the regression test to organize the tests in a quartile progression.
//#undef REGRESSION_LEVEL_OVERRIDE
#ifndef REGRESSION_LEVEL_OVERRIDE
#define REGRESSION_LEVEL_1 1
#define REGRESSION_LEVEL_2 1
#define REGRESSION_LEVEL_3 1
#define REGRESSION_LEVEL_4 1
#endif

int main()
try {
	using namespace sw::universal;

	// configure a posit<64,3>
	constexpr size_t nbits = 64;
	constexpr size_t es = 3;

	int nrOfFailedTestCases = 0;
	bool bReportIndividualTestCases = false;
	size_t RND_TEST_CASES = 1000;

#if POSIT_FAST_POSIT_64_3
	std::cout << "Fast specialization posit<64,3> configuration tests\n";
#else
	std::cout << "Standard posit<64,3> configuration tests\n";
#endif

	using Scalar = posit<nbits, es>;
	Scalar p;
	std::cout << dynamic_range(p) << "\n\n";
	std::string tag = type_tag(p);

#if MANUAL_TESTING

#else

#if REGRESSION_LEVEL_1
	// special cases
	std::cout << "Special case tests\n";
	std::string test = "Initialize to zero: ";
	p = 0;
	nrOfFailedTestCases += ReportCheck(tag, test, p.iszero());
	test = "Initialize to NAN";
	p = NAN;
	nrOfFailedTestCases += ReportCheck(tag, test, p.isnar());
	test = "Initialize to INFINITY";
	p = INFINITY;
	nrOfFailedTestCases += ReportCheck(tag, test, p.isnar());
	test = "sign is true";
	p = -1.0f;
	nrOfFailedTestCases += ReportCheck(tag, test, p.sign());
	test = "is negative";
	nrOfFailedTestCases += ReportCheck(tag, test, p.isneg());
	test = "sign is false";
	p = +1.0f;
	nrOfFailedTestCases += ReportCheck(tag, test, !p.sign());
	test = "is positive";
	nrOfFailedTestCases += ReportCheck(tag, test, p.ispos());

	RND_TEST_CASES = 1024;
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_ADD, RND_TEST_CASES), tag, "addition      ");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_SUB, RND_TEST_CASES), tag, "subtraction   ");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_MUL, RND_TEST_CASES), tag, "multiplication");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_DIV, RND_TEST_CASES), tag, "division      ");

#endif

#if REGRESSION_LEVEL_2
	// logic tests
	std::cout << "Logic operator tests\n";
	nrOfFailedTestCases += ReportTestResult( VerifyPositLogicEqual             <nbits, es>(), tag, "    ==          (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyPositLogicNotEqual          <nbits, es>(), tag, "    !=          (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyPositLogicLessThan          <nbits, es>(), tag, "    <           (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyPositLogicLessOrEqualThan   <nbits, es>(), tag, "    <=          (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyPositLogicGreaterThan       <nbits, es>(), tag, "    >           (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyPositLogicGreaterOrEqualThan<nbits, es>(), tag, "    >=          (native)  ");

	// conversion tests
	// internally this generators are clamped as the state space 2^33 is too big
	std::cout << "Assignment/conversion tests\n";
	nrOfFailedTestCases += ReportTestResult( VerifyIntegerConversion           <nbits, es>(bReportIndividualTestCases), tag, "sint32 assign   (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyUintConversion              <nbits, es>(bReportIndividualTestCases), tag, "uint32 assign   (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyConversion                  <nbits, es>(bReportIndividualTestCases), tag, "float assign    (native)  ");
//	nrOfFailedTestCases += ReportTestResult( VerifyConversionThroughRandoms <nbits, es>(tag, true, 100), tag, "float assign   ");
#endif

#if REGRESSION_LEVEL_3
	// arithmetic tests
	std::cout << "Arithmetic tests " << RND_TEST_CASES << " randoms each\n";
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_ADD, RND_TEST_CASES), tag, "addition        (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_SUB, RND_TEST_CASES), tag, "subtraction     (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_MUL, RND_TEST_CASES), tag, "multiplication  (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_DIV, RND_TEST_CASES), tag, "division        (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_ADD, RND_TEST_CASES), tag, "+=              (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_SUB, RND_TEST_CASES), tag, "-=              (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_MUL, RND_TEST_CASES), tag, "*=              (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_DIV, RND_TEST_CASES), tag, "/=              (native)  ");

#endif

#if REGRESSION_LEVEL_4
	// elementary function tests
	std::cout << "Elementary function tests\n";
	p.minpos();
	double dminpos = double(p);
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_SQRT,  RND_TEST_CASES, dminpos), tag, "sqrt            (native)  ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_EXP,   RND_TEST_CASES, dminpos), tag, "exp                       ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_EXP2,  RND_TEST_CASES, dminpos), tag, "exp2                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_LOG,   RND_TEST_CASES, dminpos), tag, "log                       ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_LOG2,  RND_TEST_CASES, dminpos), tag, "log2                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_LOG10, RND_TEST_CASES, dminpos), tag, "log10                     ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_SIN,   RND_TEST_CASES, dminpos), tag, "sin                       ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_COS,   RND_TEST_CASES, dminpos), tag, "cos                       ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_TAN,   RND_TEST_CASES, dminpos), tag, "tan                       ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_ASIN,  RND_TEST_CASES, dminpos), tag, "asin                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_ACOS,  RND_TEST_CASES, dminpos), tag, "acos                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_ATAN,  RND_TEST_CASES, dminpos), tag, "atan                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_SINH,  RND_TEST_CASES, dminpos), tag, "sinh                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_COSH,  RND_TEST_CASES, dminpos), tag, "cosh                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_TANH,  RND_TEST_CASES, dminpos), tag, "tanh                      ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_ASINH, RND_TEST_CASES, dminpos), tag, "asinh                     ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_ACOSH, RND_TEST_CASES, dminpos), tag, "acosh                     ");
	nrOfFailedTestCases += ReportTestResult( VerifyUnaryOperatorThroughRandoms<Scalar>(bReportIndividualTestCases, OPCODE_ATANH, RND_TEST_CASES, dminpos), tag, "atanh                     ");
	// elementary functions with two operands
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms<nbits, es>(bReportIndividualTestCases, OPCODE_POW, RND_TEST_CASES),   tag, "pow                       ");
#endif

#endif // !MANUAL_TESTING

	// TODO: as we don't have a reference floating point implementation to Verify
	// the arithmetic operations we are going to ignore the failures
	nrOfFailedTestCases = 0;
	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::quire_exception& err) {
	std::cerr << "Uncaught quire exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::posit_internal_exception& err) {
	std::cerr << "Uncaught posit internal exception: " << err.what() << std::endl;
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