#pragma once
// efloat_fwd.hpp: forward definitions of the adaptive precision efloat type
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
// SPDX-License-Identifier: MIT
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw { namespace universal {

// forward references
template<unsigned nlimbs> class efloat;
template<unsigned nlimbs> bool parse(const std::string& number, efloat<nlimbs>& v);

}}  // namespace sw::universal
