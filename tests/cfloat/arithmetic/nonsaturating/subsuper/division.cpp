// division.cpp: test suite runner for division on classic floats
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
// minimum set of include files to reflect source code dependencies
//#define CFLOAT_VERBOSE_OUTPUT
//#define CFLOAT_TRACE_DIV
//#define BLOCKTRIPLE_VERBOSE_OUTPUT
//#define BLOCKTRIPLE_TRACE_DIV
#include <universal/number/cfloat/cfloat.hpp>
#include <universal/verification/test_suite.hpp>
#include <universal/verification/test_suite_random.hpp>
#include <universal/verification/cfloat_test_suite.hpp>

/*
   0 /  inf =    0 : 0b0.00000000.00000000000000000000000
   0 / -inf =   -0 : 0b1.00000000.00000000000000000000000
   1 /  inf =    0 : 0b0.00000000.00000000000000000000000
   1 / -inf =   -0 : 0b1.00000000.00000000000000000000000
 inf /    0 =  inf : 0b0.11111111.00000000000000000000000
 inf /   -0 = -inf : 0b1.11111111.00000000000000000000000
-inf /    0 = -inf : 0b1.11111111.00000000000000000000000
-inf /   -0 =  inf : 0b0.11111111.00000000000000000000000
 inf /  inf = -nan(ind) : 0b1.11111111.10000000000000000000000
 inf / -inf = -nan(ind) : 0b1.11111111.10000000000000000000000
-inf /  inf = -nan(ind) : 0b1.11111111.10000000000000000000000
-inf / -inf = -nan(ind) : 0b1.11111111.10000000000000000000000

   0 /  0 = -nan(ind) : 0b1.11111111.10000000000000000000000
   0 / -0 = -nan(ind) : 0b1.11111111.10000000000000000000000
  -0 /  0 = -nan(ind) : 0b1.11111111.10000000000000000000000
  -0 / -0 = -nan(ind) : 0b1.11111111.10000000000000000000000

   1 /  0 =  inf : 0b0.11111111.00000000000000000000000
   1 / -0 = -inf : 0b1.11111111.00000000000000000000000
  -1 /  0 = -inf : 0b1.11111111.00000000000000000000000
  -1 / -0 =  inf : 0b0.11111111.00000000000000000000000

   0 /  1 =  0 : 0b0.00000000.00000000000000000000000
   0 / -1 = -0 : 0b1.00000000.00000000000000000000000
  -0 /  1 = -0 : 0b1.00000000.00000000000000000000000
  -0 / -1 =  0 : 0b0.00000000.00000000000000000000000
 */


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
#define REGRESSION_LEVEL_4 0
#endif

int main()
try {
	using namespace sw::universal;

	// cfloat encoding configuration for the test
	constexpr bool hasSubnormals   = true;
	constexpr bool hasSupernormals = true;
	constexpr bool isSaturating    = false;

	std::string test_suite         = "classic cfloat division validation with subnormals, normals, and supernormals";
	std::string test_tag           = "cfloat_ttf division";
	bool reportTestCases           = false;
	int nrOfFailedTestCases        = 0;

	std::cout << test_suite << '\n';

	// shorthand alias types
	using c16  = cfloat< 16,  5, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;
	using c32  = cfloat< 32,  8, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;
	using c48  = cfloat< 48,  8, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;
	using c64  = cfloat< 64, 11, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;
	using c80  = cfloat< 80, 11, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;
	using c96  = cfloat< 96, 15, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;
	using c128 = cfloat<128, 15, uint8_t, hasSubnormals, hasSupernormals, isSaturating>;

	// driving the intensity of the randomized arithmetic tests
	size_t nrRandoms = 0;

#if MANUAL_TESTING

//	ReportIeee754InfinityArithmetic();
//	ReportIeee754NotANumberArithmetic();
//	ReportIeee754SpecialCases();

//	TestCase< cfloat<4, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(TestCaseOperator::DIV, 1.0f, 1.0f);
	TestCase< cfloat<5, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(TestCaseOperator::DIV, 1.5f, 5.0f);
//	TestCase< cfloat<6, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(TestCaseOperator::DIV, 1.0f, -1.0f);
//	TestCase< cfloat<6, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(TestCaseOperator::DIV, 1.625f, -1.625f);

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision<cfloat<4, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<4,1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision<cfloat<4, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<4,2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision<cfloat<5, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<5,1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision<cfloat<5, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(true), "cfloat<5,2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision<cfloat<6, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<6,1,uint8_t,t,t,f>", "division");
//	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision<cfloat<6, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<6,2,uint8_t,t,t,f>", "division");

	/*
	 still some rounding errors:
	 FAIL -6.2059583144194067535e+31 / -0.00026169454213231801987 != 2.3714510221239590117e+35 golden reference is 2.3714512201943652974e+35
	 result 0b0.11110100.01101101011000010100000
	 vs ref 0b0.11110100.01101101011000010100001
	0b1.11101000.10000111101001101010101 / 0b1.01110011.00010010011010000001100
	FAIL -1.3358241091374718421e-15 / 1.2792965249869537551e-17 != -104.41864013671875  golden reference is -104.41864776611328125
	 result 0b1.10000101.10100001101011001011000
	 vs ref 0b1.10000101.10100001101011001011001
	0b1.01001101.10000001000001100110110 / 0b0.01000110.11010111111110100010010
	class sw::universal::cfloat<32,8,unsigned char,1,1,0>        division FAIL 2 failed test cases
	class sw::universal::cfloat<48,8,unsigned char,1,1,0>        division PASS
	FAIL -1.1744315954211186612e-161 / -4.4173639222185649975e-170 != 265867068.25623622537 golden reference is 265867068.25623625517
	 result 0b0.10000011010.1111101100011001111001111000100000110011000101100101
	 vs ref 0b0.10000011010.1111101100011001111001111000100000110011000101100110
	0b1.00111101000.0101001000100111100101111000111011100111000001010001 / 0b1.00111001100.0101010101101011110111110001001100110100101110110100
	class sw::universal::cfloat<64,11,unsigned char,1,1,0>       division FAIL 1 failed test cases
	*/
	reportTestCases = true;
	nrRandoms = 5;
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c16  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c16).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c32  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c32).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c48  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c48).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c64  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c64).name(), "division");
	nrRandoms = 0; // TBD > double precision requires a vector of 64bit words to construct the random bits
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c80  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c80).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c96  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c96).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c128 >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c128).name(), "division");

	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return EXIT_SUCCESS; // ignore failures
#else

#if REGRESSION_LEVEL_1
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<3, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 3, 1,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<4, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 4, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<4, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 4, 2,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<5, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 5, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<5, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 5, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<5, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 5, 3,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<6, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 6, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<6, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 6, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<6, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 6, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<6, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 6, 4,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<7, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 7, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<7, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 7, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<7, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 7, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<7, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 7, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<7, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 7, 5,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<8, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 8, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<8, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 8, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<8, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 8, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<8, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 8, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<8, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 8, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<8, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 8, 6,uint8_t,t,t,f>", "division");

	nrRandoms = 0;
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c16  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c16).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c32  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c32).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c48  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c48).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c64  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c64).name(), "division");
	nrRandoms = 0; // TBD > double precision requires a vector of 64bit words to construct the random bits
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c80  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c80).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c96  >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c96).name(), "division");
	nrOfFailedTestCases += ReportTestResult(VerifyBinaryOperatorThroughRandoms< c128 >(reportTestCases, OPCODE_DIV, nrRandoms), typeid(c128).name(), "division");

#endif

#if REGRESSION_LEVEL_2
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<9, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat< 9, 7,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<10, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<10, 8,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 8,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<11, 9, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<11, 9,uint8_t,t,t,f>", "division");
#endif

#if REGRESSION_LEVEL_3
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 1, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 1,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 2, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 2,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 8,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12, 9, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12, 9,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<12,10, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<12,10,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 8,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 9, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13, 9,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 10, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13,10,uint8_t,t,t,f>", "division");
#endif

#if REGRESSION_LEVEL_4
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<13, 11, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<13,11,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 8,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 9, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14, 9,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 10, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14,10,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<14, 11, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<14,11,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 8,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 9, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15, 9,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 10, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15,10,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<15, 11, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<15,11,uint8_t,t,t,f>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 3, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 3,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 4, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 4,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 5, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 5,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 6, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 6,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 7, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 7,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 8, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 8,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 9, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16, 9,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 10, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16,10,uint8_t,t,t,f>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyCfloatDivision< cfloat<16, 11, uint8_t, hasSubnormals, hasSupernormals, isSaturating> >(reportTestCases), "cfloat<16,11,uint8_t,t,t,f>", "division");
#endif

	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
#endif  // MANUAL_TESTING
}
catch (char const* msg) {
	std::cerr << "Caught ad-hoc exception: " << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::universal_arithmetic_exception& err) {
	std::cerr << "Caught unexpected universal arithmetic exception : " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::universal_internal_exception& err) {
	std::cerr << "Caught unexpected universal internal exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Caught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
