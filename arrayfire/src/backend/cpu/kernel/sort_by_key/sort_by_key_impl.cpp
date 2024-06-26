/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <kernel/sort_by_key_impl.hpp>

// SBK_TYPES:float double int uint intl uintl short ushort char uchar

namespace arrayfire {
namespace cpu {
namespace kernel {
INSTANTIATE1(float)
//INSTANTIATE1(double)
INSTANTIATE1(int)
INSTANTIATE1(uint)
INSTANTIATE1(intl)
INSTANTIATE1(uintl)
INSTANTIATE1(short)
INSTANTIATE1(ushort)
INSTANTIATE1(char)
INSTANTIATE1(uchar)
}  // namespace kernel
}  // namespace cpu
}  // namespace arrayfire
