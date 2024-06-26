/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <backend.hpp>
#include <common/ArrayInfo.hpp>
#include <common/err_common.hpp>
#include <handle.hpp>
#include <qr.hpp>
#include <af/array.h>
#include <af/defines.h>
#include <af/lapack.h>

using af::dim4;
using detail::Array;
//using detail::cdouble;
using detail::cfloat;
using detail::createEmptyArray;
using std::swap;

template<typename T>
static inline void qr(af_array *q, af_array *r, af_array *tau,
                      const af_array in) {
    Array<T> qArray = createEmptyArray<T>(dim4());
    Array<T> rArray = createEmptyArray<T>(dim4());
    Array<T> tArray = createEmptyArray<T>(dim4());

    qr<T>(qArray, rArray, tArray, getArray<T>(in));

    *q   = getHandle(qArray);
    *r   = getHandle(rArray);
    *tau = getHandle(tArray);
}

template<typename T>
static inline af_array qr_inplace(af_array in) {
    return getHandle(qr_inplace<T>(getArray<T>(in)));
}

af_err af_qr(af_array *q, af_array *r, af_array *tau, const af_array in) {
    /*try*/ {
        const ArrayInfo &i_info = getInfo(in);

        if (i_info.ndims() > 2) {
            AF_ERROR("qr can not be used in batch mode", AF_ERR_BATCH);
        }

        af_dtype type = i_info.getType();

        if (i_info.ndims() == 0) {
            AF_CHECK(af_create_handle(q, 0, nullptr, type));
            AF_CHECK(af_create_handle(r, 0, nullptr, type));
            AF_CHECK(af_create_handle(tau, 0, nullptr, type));
            return AF_SUCCESS;
        }

        ARG_ASSERT(0, q != nullptr);
        ARG_ASSERT(1, r != nullptr);
        ARG_ASSERT(2, tau != nullptr);
        ARG_ASSERT(3, i_info.isFloating());  // Only floating and complex types

        switch (type) {
            case f32: qr<float>(q, r, tau, in); break;
            //case f64: qr<float>(q, r, tau, in); break;
            case c32: qr<cfloat>(q, r, tau, in); break;
            //case c64: qr<cdouble>(q, r, tau, in); break;
            default: TYPE_ERROR(1, type);
        }
    }
    CATCHALL;

    return AF_SUCCESS;
}

af_err af_qr_inplace(af_array *tau, af_array in) {
    /*try*/ {
        const ArrayInfo &i_info = getInfo(in);

        if (i_info.ndims() > 2) {
            AF_ERROR("qr can not be used in batch mode", AF_ERR_BATCH);
        }

        af_dtype type = i_info.getType();

        ARG_ASSERT(1, i_info.isFloating());  // Only floating and complex types
        ARG_ASSERT(0, tau != nullptr);

        if (i_info.ndims() == 0) {
            return af_create_handle(tau, 0, nullptr, type);
        }

        af_array out;
        switch (type) {
            case f32: out = qr_inplace<float>(in); break;
            //case f64: out = qr_inplace<float>(in); break;
            case c32: out = qr_inplace<cfloat>(in); break;
            //case c64: out = qr_inplace<cdouble>(in); break;
            default: TYPE_ERROR(1, type);
        }
        swap(*tau, out);
    }
    CATCHALL;

    return AF_SUCCESS;
}
