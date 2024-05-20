// pixar_pxr24.cpp: test suite runner for standard Pixar PXR24 format, which is equivalent to cfloat<24,8>
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
// SPDX-License-Identifier: MIT
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
#include <universal/number/cfloat/cfloat.hpp>
#include <universal/verification/test_suite_arithmetic.hpp>

int main()
try {
	using namespace sw::universal;

	// map the Pixar FP24 onto the classic cfloats
	constexpr size_t nbits = 24;
	constexpr size_t ebits = 8;
	using pxr24 = cfloat<nbits, ebits>;

	int nrOfFailedTestCases = 0;
	std::string tag = " cfloat<24,8>";

	std::cout << "Standard Pixar PXR24 format, which is equivalent to a cfloat<24,8> configuration tests\n";

	pxr24 r;
	r = 1.2345;
	std::cout << r << '\n';

	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
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
