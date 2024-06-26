/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <Array.hpp>
#include <err_cpu.hpp>
#include <gradient.hpp>
#include <kernel/gradient.hpp>
#include <math.hpp>
#include <platform.hpp>
#include <queue.hpp>
#include <stdexcept>

namespace arrayfire {
namespace cpu {

template<typename T>
void gradient(Array<T> &grad0, Array<T> &grad1, const Array<T> &in) {
    getQueue().enqueue(kernel::gradient<T>, grad0, grad1, in);
}

#define INSTANTIATE(T)                                            \
    template void gradient<T>(Array<T> & grad0, Array<T> & grad1, \
                              const Array<T> &in);

INSTANTIATE(float)
//INSTANTIATE(double)
INSTANTIATE(cfloat)
//INSTANTIATE(cdouble)

}  // namespace cpu
}  // namespace arrayfire
