/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/
#include <af/constants.h>
#include <limits>

namespace af {
const double NaN = std::numeric_limits<float>::quiet_NaN();
const double Inf = std::numeric_limits<float>::infinity();
const double Pi  = 3.1415926535897932384626433832795028841971693993751;
}  // namespace af
