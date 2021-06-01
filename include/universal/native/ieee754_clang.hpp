#pragma once
// ieee754_clang.hpp: clang-specific manipulation functions for IEEE-754 native types
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

#if defined(__clang__)
/* Clang/LLVM. ---------------------------------------------- */

namespace sw::universal {

// IEEE-754 specializations for Clang
//
template<>
class ieee754_parameter<float> {
public:
	static constexpr uint64_t smask    = 0x8000'0000ull;
	static constexpr int      ebits    = 8;
	static constexpr int      bias     = 127;
	static constexpr uint64_t emask    = 0x7F80'0000ull;
	static constexpr uint64_t eallset  = 0xFFull;
	static constexpr int      fbits    = 23;
	static constexpr uint64_t hmask    = 0x0080'0000ull;
	static constexpr uint64_t fmask    = 0x007F'FFFFull;
	static constexpr uint64_t hfmask   = 0x00FF'FFFFull;
	static constexpr uint64_t fmsb     = 0x0040'0000ull;
	static constexpr uint64_t qnanmask = 0x7FC0'0001ull;
	static constexpr uint64_t snanmask = 0x7FC0'0000ull;
};

template<>
class ieee754_parameter<double> {
public:
	static constexpr uint64_t smask    = 0x8000'0000'0000'0000ull;
	static constexpr int      ebits    = 11;
	static constexpr int      bias     = 1023;
	static constexpr uint64_t emask    = 0x7FF0'0000'0000'0000ull;
	static constexpr uint64_t eallset  = 0x7FF;
	static constexpr int      fbits    = 52;
	static constexpr uint64_t hmask    = 0x0010'0000'0000'0000ull;
	static constexpr uint64_t fmask    = 0x000F'FFFF'FFFF'FFFFull;
	static constexpr uint64_t hfmask   = 0x001F'FFFF'FFFF'FFFFull;
	static constexpr uint64_t fmsb     = 0x0008'0000'0000'0000ull;
	static constexpr uint64_t qnanmask = 0x7FF8'0000'0000'0001ull;
	static constexpr uint64_t snanmask = 0x7FF8'0000'0000'0000ull;
};

// CLang long double = 80 bit extended precision
// 
// IEEE-754 parameter constexpressions for long double
template<>
class ieee754_parameter<long double> {
public:
	static constexpr uint64_t smask    = 0x0000'0000'0000'8000ull; // mask for the top half
	static constexpr int      ebits    = 15;
	static constexpr int      bias     = 16383;
	static constexpr uint64_t emask    = 0x0000'0000'0000'7FFFull; // mask for the top half
	static constexpr uint64_t eallset  = 0x7FFF;
	static constexpr int      fbits    = 64;
	static constexpr uint64_t hmask    = 0x8000'0000'0000'0000ull; // mask for the bottom half
	static constexpr uint64_t fmask    = 0x7FFF'FFFF'FFFF'FFFFull; // mask for the bottom half
	static constexpr uint64_t hfmask   = 0xFFFF'FFFF'FFFF'FFFFull; // mask for the bottom half
	static constexpr uint64_t fmsb     = 0x8000'0000'0000'0000ull;
	static constexpr uint64_t qnanmask = 0x7FF8'0000'0000'0001ull;
	static constexpr uint64_t snanmask = 0x7FF8'0000'0000'0000ull;
};

////////////////////////////////////////////////////////////////////////
// numerical helpers

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// compiler specific long double IEEE floating point

union long_double_decoder {
	long_double_decoder() : ld{0.0l} {}
	long_double_decoder(long double _ld) : ld{_ld} {}
	long double ld;
	struct {
		uint64_t fraction : 63;
		uint64_t bit63 : 1;
		uint64_t exponent : 15;
		uint64_t sign : 1;
	} parts;
};

inline void extractFields(long double value, bool& s, uint64_t& rawExponentBits, uint64_t& rawFractionBits) {
	long_double_decoder decoder;
	decoder.ld = value;
	s = decoder.parts.sign == 1 ? true : false;
	rawExponentBits = decoder.parts.exponent;
	rawFractionBits = decoder.parts.fraction;
}

// generate a binary string for a native double precision IEEE floating point
inline std::string to_hex(const long double& number) {
	std::stringstream ss;
	long_double_decoder decoder;
	decoder.ld = number;
	ss << (decoder.parts.sign ? '1' : '0') << '.' << std::hex << int(decoder.parts.exponent) << '.' << decoder.parts.fraction;
	return ss.str();
}

// generate a binary string for a native double precision IEEE floating point
inline std::string to_binary(const long double& number, bool bNibbleMarker = false) {
	std::stringstream ss;
	long_double_decoder decoder;
	decoder.ld = number;

	// print sign bit
	ss << (decoder.parts.sign ? '1' : '0') << '.';

	// print exponent bits
	{
		uint64_t mask = 0x4000;
		for (int i = 14; i >= 0; --i) {
			ss << ((decoder.parts.exponent & mask) ? '1' : '0');
			if (bNibbleMarker && i != 0 && (i % 4) == 0) ss << '\'';
			mask >>= 1;
		}
	}

	ss << '.';

	// print fraction bits
	uint64_t mask = (uint64_t(1) << 62);
	for (int i = 62; i >= 0; --i) {
		ss << ((decoder.parts.fraction & mask) ? '1' : '0');
		if (bNibbleMarker && i != 0 && (i % 4) == 0) ss << '\'';
		mask >>= 1;
	}

	return ss.str();
}

// return in triple form (+, scale, fraction)
inline std::string to_triple(const long double& number) {
	std::stringstream ss;
	long_double_decoder decoder;
	decoder.ld = number;

	// print sign bit
	ss << '(' << (decoder.parts.sign ? '-' : '+') << ',';

	// exponent 
	// the exponent value used in the arithmetic is the exponent shifted by a bias 
	// for the IEEE 754 binary32 case, an exponent value of 127 represents the actual zero 
	// (i.e. for 2^(e ¿ 127) to be one, e must be 127). 
	// Exponents range from ¿126 to +127 because exponents of ¿127 (all 0s) and +128 (all 1s) are reserved for special numbers.
	if (decoder.parts.exponent == 0) {
		ss << "exp=0,";
	}
	else if (decoder.parts.exponent == 0xFF) {
		ss << "exp=1, ";
	}
	int scale = int(decoder.parts.exponent) - 16383;
	ss << scale << ',';

	// print fraction bits
	ss << (decoder.parts.bit63 ? '1' : '0');
	uint64_t mask = (uint64_t(1) << 62);
	for (int i = 62; i >= 0; --i) {
		ss << ((decoder.parts.fraction & mask) ? '1' : '0');
		mask >>= 1;
	}

	ss << ')';
	return ss.str();
}

// generate a color coded binary string for a native double precision IEEE floating point
inline std::string color_print(const long double& number) {
	std::stringstream ss;
	long_double_decoder decoder;
	decoder.ld = number;

	Color red(ColorCode::FG_RED);
	Color yellow(ColorCode::FG_YELLOW);
	Color blue(ColorCode::FG_BLUE);
	Color magenta(ColorCode::FG_MAGENTA);
	Color cyan(ColorCode::FG_CYAN);
	Color white(ColorCode::FG_WHITE);
	Color def(ColorCode::FG_DEFAULT);

	// print sign bit
	ss << red << (decoder.parts.sign ? '1' : '0') << '.';

	// print exponent bits
	{
		uint64_t mask = 0x8000;
		for (int i = 15; i >= 0; --i) {
			ss << cyan << ((decoder.parts.exponent & mask) ? '1' : '0');
			if (i > 0 && i % 4 == 0) ss << cyan << '\'';
			mask >>= 1;
		}
	}

	ss << '.';

	// print fraction bits
	ss << magenta << (decoder.parts.bit63 ? '1' : '0');
	uint64_t mask = (uint64_t(1) << 62);
	for (int i = 62; i >= 0; --i) {
		ss << magenta << ((decoder.parts.fraction & mask) ? '1' : '0');
		if (i > 0 && i % 4 == 0) ss << magenta << '\'';
		mask >>= 1;
	}

	ss << def;
	return ss.str();
}

// floating point component extractions
inline void extract_fp_components(float fp, bool& _sign, int& _exponent, float& _fr, unsigned int& _fraction) {
	static_assert(sizeof(float) == 4, "This function only works when float is 32 bit.");
	_sign = fp < 0.0 ? true : false;
	_fr = frexpf(fp, &_exponent);
	_fraction = uint32_t(0x007FFFFFul) & reinterpret_cast<uint32_t&>(_fr);
}
inline void extract_fp_components(double fp, bool& _sign, int& _exponent, double& _fr, unsigned long long& _fraction) {
	static_assert(sizeof(double) == 8, "This function only works when double is 64 bit.");
	_sign = fp < 0.0 ? true : false;
	_fr = frexp(fp, &_exponent);
	_fraction = uint64_t(0x000FFFFFFFFFFFFFull) & reinterpret_cast<uint64_t&>(_fr);
}

#ifdef CPLUSPLUS_17
inline void extract_fp_components(long double fp, bool& _sign, int& _exponent, long double& _fr, unsigned long long& _fraction) {
	static_assert(std::numeric_limits<long double>::digits <= 64, "This function only works when long double significant is <= 64 bit.");
	if constexpr (sizeof(long double) == 8) { // it is just a double
		_sign = fp < 0.0 ? true : false;
		_fr = frexp(double(fp), &_exponent);
		_fraction = uint64_t(0x000FFFFFFFFFFFFFull) & reinterpret_cast<uint64_t&>(_fr);
	}
	else if constexpr (sizeof(long double) == 16 && std::numeric_limits<long double>::digits <= 64) {
		_sign = fp < 0.0 ? true : false;
		_fr = frexpl(fp, &_exponent);
		_fraction = uint64_t(0x7FFFFFFFFFFFFFFFull) & reinterpret_cast<uint64_t&>(_fr); // 80bit extended format only has 63bits of fraction
	}
}
#else
inline void extract_fp_components(long double fp, bool& _sign, int& _exponent, long double& _fr, unsigned long long& _fraction) {
	static_assert(std::numeric_limits<long double>::digits <= 64, "This function only works when long double significant is <= 64 bit.");
	if (sizeof(long double) == 8) { // it is just a double
		_sign = fp < 0.0 ? true : false;
		_fr = frexp(double(fp), &_exponent);
		_fraction = uint64_t(0x000FFFFFFFFFFFFFull) & reinterpret_cast<uint64_t&>(_fr);
	}
	else if (sizeof(long double) == 16 && std::numeric_limits<long double>::digits <= 64) {
		_sign = fp < 0.0 ? true : false;
		_fr = frexpl(fp, &_exponent);
		_fraction = uint64_t(0x7FFFFFFFFFFFFFFFull) & reinterpret_cast<uint64_t&>(_fr); // 80bit extended format only has 63bits of fraction
	}
}
#endif


} // namespace sw::universal

#endif // CLANG/LLVM

