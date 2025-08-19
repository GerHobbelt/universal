#pragma once
// ereal_fwd.hpp :  forward declarations of ereal 
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
// SPDX-License-Identifier: MIT
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw { namespace universal {

// core ereal types
template<unsigned maxLimbs> class ereal;
template<unsigned maxLimbs> ereal<maxLimbs> abs(const ereal<maxLimbs>&);
template<unsigned maxLimbs> ereal<maxLimbs> fabs(const ereal<maxLimbs>&);

}} // namespace sw::universal

