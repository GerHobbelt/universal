#pragma once
// fractional.hpp: fractional functions for logarithmic floating-point
//
// Copyright (C) 2017-2022 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw { namespace universal {

template<size_t nbits, size_t rbits, ArithmeticBehavior behavior, typename bt>
lns<nbits, rbits, behavior, bt> lnsmod(lns<nbits, rbits, behavior, bt> x, lns<nbits, rbits, behavior, bt> y) {
	using Real = lns<nbits, rbits, behavior, bt>;
	if (y.iszero() || x.isinf() || x.isnan() || y.isnan()) {
		Real nan;
		nan.setnan();  // quiet NaN
		return nan;
	}
	if (y.isinf() || x.iszero()) {
		return x;
	}

	y.setsign(false); // equivalent but faster than y = abs(y);
	int yexp;
	frexp(y, &yexp);  // ignore the fraction that comes back
	Real r = x;
	if (x < 0) r = -x;
	Real d = r / y;
	if (d.isinf()) return x;
	Real n = trunc(d);
	r = r - n * y;
	if (x < 0) r = -r;

	return r;
}

// fmod retuns x - n*y where n = x/y with the fractional part truncated
template<size_t nbits, size_t rbits, ArithmeticBehavior behavior, typename bt>
lns<nbits, rbits, behavior, bt> fmod(lns<nbits, rbits, behavior, bt> x, lns<nbits, rbits, behavior, bt> y) {
	return lnsmod(x, y);
}

// shim to stdlib
template<size_t nbits, size_t rbits, ArithmeticBehavior behavior, typename bt>
lns<nbits, rbits, behavior, bt> remainder(lns<nbits, rbits, behavior, bt> x, lns<nbits, rbits, behavior, bt> y) {
	return lns<nbits, rbits, behavior, bt>(std::remainder(double(x), double(y)));
}

// TODO: validate the rounding of these conversion, versus a method that manipulates the fraction bits directly

// frac returns the fraction of a lns value that is > 1
template<size_t nbits, size_t rbits, ArithmeticBehavior behavior, typename bt>
lns<nbits, rbits, behavior, bt> frac(lns<nbits, rbits, behavior, bt> x) {
	using Real = lns<nbits, rbits, behavior, bt>;
	long long intValue = (long long)(x);
	return abs(x-Real(intValue));  // with the logic that fractions are unsigned quantities
}


}} // namespace sw::universal