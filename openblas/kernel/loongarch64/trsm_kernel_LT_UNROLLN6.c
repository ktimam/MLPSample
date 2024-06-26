/*********************************************************************/
/* Copyright 2009, 2010 The University of Texas at Austin.           */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE IS PROVIDED  BY THE  UNIVERSITY OF  TEXAS AT    */
/*    AUSTIN  ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,    */
/*    INCLUDING, BUT  NOT LIMITED  TO, THE IMPLIED  WARRANTIES OF    */
/*    MERCHANTABILITY  AND FITNESS FOR  A PARTICULAR  PURPOSE ARE    */
/*    DISCLAIMED.  IN  NO EVENT SHALL THE UNIVERSITY  OF TEXAS AT    */
/*    AUSTIN OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL,  SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES    */
/*    (INCLUDING, BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE    */
/*    GOODS  OR  SERVICES; LOSS  OF  USE,  DATA,  OR PROFITS;  OR    */
/*    BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON ANY THEORY OF    */
/*    LIABILITY, WHETHER  IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*    (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT    */
/*    OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF ADVISED  OF  THE    */
/*    POSSIBILITY OF SUCH DAMAGE.                                    */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of The University of Texas at Austin.                 */
/*********************************************************************/

#include "common.h"

static FLOAT dm1 = -1.;

#ifdef CONJ
#define GEMM_KERNEL   GEMM_KERNEL_L
#else
#define GEMM_KERNEL   GEMM_KERNEL_N
#endif

#if GEMM_DEFAULT_UNROLL_M == 1
#define GEMM_UNROLL_M_SHIFT 0
#endif

#if GEMM_DEFAULT_UNROLL_M == 2
#define GEMM_UNROLL_M_SHIFT 1
#endif

#if GEMM_DEFAULT_UNROLL_M == 4
#define GEMM_UNROLL_M_SHIFT 2
#endif

#if GEMM_DEFAULT_UNROLL_M == 6
#define GEMM_UNROLL_M_SHIFT 2
#endif

#if GEMM_DEFAULT_UNROLL_M == 8
#define GEMM_UNROLL_M_SHIFT 3
#endif

#if GEMM_DEFAULT_UNROLL_M == 16
#define GEMM_UNROLL_M_SHIFT 4
#endif

#if GEMM_DEFAULT_UNROLL_N == 1
#define GEMM_UNROLL_N_SHIFT 0
#endif

#if GEMM_DEFAULT_UNROLL_N == 2
#define GEMM_UNROLL_N_SHIFT 1
#endif

#if GEMM_DEFAULT_UNROLL_N == 4
#define GEMM_UNROLL_N_SHIFT 2
#endif

#if GEMM_DEFAULT_UNROLL_N == 8
#define GEMM_UNROLL_N_SHIFT 3
#endif

#if GEMM_DEFAULT_UNROLL_N == 16
#define GEMM_UNROLL_N_SHIFT 4
#endif

#ifndef COMPLEX

static inline void solve(BLASLONG m, BLASLONG n, FLOAT *a, FLOAT *b, FLOAT *c, BLASLONG ldc) {

  FLOAT aa, bb;

  int i, j, k;

  for (i = 0; i < m; i++) {

    aa = *(a + i);

    for (j = 0; j < n; j ++) {
      bb = *(c + i + j * ldc);
      bb *= aa;
      *b             = bb;
      *(c + i + j * ldc) = bb;
      b ++;

      for (k = i + 1; k < m; k ++){
	*(c + k + j * ldc) -= bb * *(a + k);
      }

    }
    a += m;
  }
}

#else

static inline void solve(BLASLONG m, BLASLONG n, FLOAT *a, FLOAT *b, FLOAT *c, BLASLONG ldc) {

  FLOAT aa1, aa2;
  FLOAT bb1, bb2;
  FLOAT cc1, cc2;

  int i, j, k;

  ldc *= 2;

  for (i = 0; i < m; i++) {

    aa1 = *(a + i * 2 + 0);
    aa2 = *(a + i * 2 + 1);

    for (j = 0; j < n; j ++) {
      bb1 = *(c + i * 2 + 0 + j * ldc);
      bb2 = *(c + i * 2 + 1 + j * ldc);

#ifndef CONJ
      cc1 = aa1 * bb1 - aa2 * bb2;
      cc2 = aa1 * bb2 + aa2 * bb1;
#else
      cc1 = aa1 * bb1 + aa2 * bb2;
      cc2 = aa1 * bb2 - aa2 * bb1;
#endif

      *(b + 0) = cc1;
      *(b + 1) = cc2;
      *(c + i * 2 + 0 + j * ldc) = cc1;
      *(c + i * 2 + 1 + j * ldc) = cc2;
      b += 2;

      for (k = i + 1; k < m; k ++){
#ifndef CONJ
	*(c + k * 2 + 0 + j * ldc) -= cc1 * *(a + k * 2 + 0) - cc2 * *(a + k * 2 + 1);
	*(c + k * 2 + 1 + j * ldc) -= cc1 * *(a + k * 2 + 1) + cc2 * *(a + k * 2 + 0);
#else
	*(c + k * 2 + 0 + j * ldc) -= cc1 * *(a + k * 2 + 0) + cc2 * *(a + k * 2 + 1);
	*(c + k * 2 + 1 + j * ldc) -= -cc1 * *(a + k * 2 + 1) + cc2 * *(a + k * 2 + 0);
#endif
      }

    }
    a += m * 2;
  }
}

#endif


int CNAME(BLASLONG m, BLASLONG n, BLASLONG k, FLOAT dummy1,
#ifdef COMPLEX
	   FLOAT dummy2,
#endif
	   FLOAT *a, FLOAT *b, FLOAT *c, BLASLONG ldc, BLASLONG offset){

  FLOAT *aa, *cc;
  BLASLONG  kk;
  BLASLONG i, j, jj;

#if 0
  fprintf(stderr, "TRSM KERNEL LT : m = %3ld  n = %3ld  k = %3ld offset = %3ld\n",
	  m, n, k, offset);
#endif

  jj = 0;

  // j = (n >> GEMM_UNROLL_N_SHIFT);
  j = (n / 6);

  while (j > 0) {

    kk = offset;
    aa = a;
    cc = c;

    i = (m >> GEMM_UNROLL_M_SHIFT);

    while (i > 0) {

	if (kk > 0) {
	  GEMM_KERNEL(GEMM_UNROLL_M, GEMM_UNROLL_N, kk, dm1,
#ifdef COMPLEX
		      ZERO,
#endif
		      aa, b, cc, ldc);
	}

	solve(GEMM_UNROLL_M, GEMM_UNROLL_N,
	      aa + kk * GEMM_UNROLL_M * COMPSIZE,
	      b  + kk * GEMM_UNROLL_N * COMPSIZE,
	      cc, ldc);

      aa += GEMM_UNROLL_M * k * COMPSIZE;
      cc += GEMM_UNROLL_M     * COMPSIZE;
      kk += GEMM_UNROLL_M;
      i --;
    }

    if (m & (GEMM_UNROLL_M - 1)) {
      i = (GEMM_UNROLL_M >> 1);
      while (i > 0) {
	if (m & i) {
	    if (kk > 0) {
	      GEMM_KERNEL(i, GEMM_UNROLL_N, kk, dm1,
#ifdef COMPLEX
			  ZERO,
#endif
			  aa, b, cc, ldc);
	    }
	  solve(i, GEMM_UNROLL_N,
		aa + kk * i             * COMPSIZE,
		b  + kk * GEMM_UNROLL_N * COMPSIZE,
		cc, ldc);

	  aa += i * k * COMPSIZE;
	  cc += i     * COMPSIZE;
	  kk += i;
	}
	i >>= 1;
      }
    }

    b += GEMM_UNROLL_N * k   * COMPSIZE;
    c += GEMM_UNROLL_N * ldc * COMPSIZE;
    j --;
    jj += GEMM_UNROLL_M;
  }

  BLASLONG nmodN = n - n/6*6 ;

  // if (n & (GEMM_UNROLL_N - 1)) {
  if (nmodN) {

    // j = (GEMM_UNROLL_N >> 1);
    j = 4;

    while (j > 0) {
      if (nmodN & j) {

	kk = offset;
	aa = a;
	cc = c;

	i = (m >> GEMM_UNROLL_M_SHIFT);

	while (i > 0) {
	  if (kk > 0) {
	    GEMM_KERNEL(GEMM_UNROLL_M, j, kk, dm1,
#ifdef COMPLEX
			ZERO,
#endif
			aa,
			b,
			cc,
			ldc);
	  }

	  solve(GEMM_UNROLL_M, j,
		aa + kk * GEMM_UNROLL_M * COMPSIZE,
		b  + kk * j             * COMPSIZE, cc, ldc);

	  aa += GEMM_UNROLL_M * k * COMPSIZE;
	  cc += GEMM_UNROLL_M     * COMPSIZE;
	  kk += GEMM_UNROLL_M;
	  i --;
	}

	if (m & (GEMM_UNROLL_M - 1)) {
	  i = (GEMM_UNROLL_M >> 1);
	  while (i > 0) {
	    if (m & i) {
	      if (kk > 0) {
		GEMM_KERNEL(i, j, kk, dm1,
#ifdef COMPLEX
			    ZERO,
#endif
			    aa,
			    b,
			    cc,
			    ldc);
	      }

	      solve(i, j,
		    aa + kk * i * COMPSIZE,
		    b  + kk * j * COMPSIZE, cc, ldc);

	      aa += i * k * COMPSIZE;
	      cc += i     * COMPSIZE;
	      kk += i;
	      }
	    i >>= 1;
	  }
	}

	b += j * k   * COMPSIZE;
	c += j * ldc * COMPSIZE;
      }
      j >>= 1;
    }
  }

  return 0;
}
