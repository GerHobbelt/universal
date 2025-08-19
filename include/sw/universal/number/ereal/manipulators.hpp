#pragma once
// manipulators.hpp: definitions of helper functions for ereal type manipulation
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
// SPDX-License-Identifier: MIT
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <iomanip>
#include <typeinfo>  // for typeid()
#include <universal/number/ereal/ereal_fwd.hpp>
// pull in the color printing for shells utility
#include <universal/utility/color_print.hpp>

// This file contains functions that manipulate a cfloat type
// using cfloat number system knowledge.

namespace sw { namespace universal {

// Generate a type tag
template<unsigned nlimbs>
std::string type_tag(const ereal<nlimbs>& = {}) {
	return std::string("ereal");
}

// Generate a string representing the ereal components: sign, exponent, faction and value
template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string components(const ErealType& v) {
	std::stringstream s;
	s << (v.sign() ? "(-, " : "(+, ");
	s << v.exponent() << ", ";
	s << "tbd)";
	return s.str();
}

template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string to_triple(const ErealType& v) {
	std::stringstream s;
	s << (v.isneg() ? "(-, " : "(+, ");
	s << v.scale() << ", ";
	int e{ 0 };
	double f = frexp(double(v), &e);
	s << f;
	s << ')';
	return s.str();
}

// generate a binary string for ereal
template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string to_hex(const ErealType& v, bool nibbleMarker = false, bool hexPrefix = true) {
	constexpr char hexChar[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	};
	std::stringstream s;
	/*
	if (hexPrefix) s << "0x" << std::hex;
	int nrNibbles = int(1ull + ((nbits - 1ull) >> 2ull));
	for (int n = nrNibbles - 1; n >= 0; --n) {
		uint8_t nibble = v.nibble(unsigned(n));
		s << hexChar[nibble];
		if (nibbleMarker && n > 0 && (n % 4) == 0) s << '\'';
	}
	*/
	s << "tbd";
	return s.str();
}

// generate a ereal format ASCII hex format nbits.esxNN...NNa
template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string hex_print(const ErealType& c) {
	std::stringstream s;
	// s << nbits << '.' << es << 'x' << to_hex(c) << 'c';
	s << "tbd";
	return s.str();
}

template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string pretty_print(const ErealType& r) {
	std::stringstream s;
	s << "tbd";
	return s.str();
}

template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string info_print(const ErealType& p, int printPrecision = 17) {
	return std::string("tbd");
}

// generate a binary, color-coded representation of the ereal
template<typename ErealType,
	std::enable_if_t< is_ereal<ErealType>, bool> = true
>
inline std::string color_print(const ErealType& r, bool nibbleMarker = false) {
	std::stringstream s;
	s << "tbd";
	return s.str();
}


}} // namespace sw::universal
