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

#ifndef UNIT
#define INV(a) (ONE / (a))
#else
#define INV(a) (ONE)
#endif

int CNAME(BLASLONG m, BLASLONG n, FLOAT *a, BLASLONG lda, BLASLONG offset, FLOAT *b){

  BLASLONG i, ii, j, jj;

  FLOAT data01, data02, data03, data04, data05, data06;
  FLOAT data09, data10, data11, data12, data13, data14;
  FLOAT data17, data18, data19, data20, data21, data22;
  FLOAT data25, data26, data27, data28, data29, data30;
  FLOAT data33, data34, data35, data36, data37, data38;
  FLOAT data41, data42, data43, data44, data45, data46;

  FLOAT *a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8;

  jj = offset;

  BLASLONG mmod6, nmod6;
  mmod6 = m - (m/6)*6 ;
  nmod6 = n - (n/6)*6 ;

  // j = (n >> 3);
  j = (n / 6);
  while (j > 0){

    a1 = a + 0 * lda;
    a2 = a + 1 * lda;
    a3 = a + 2 * lda;
    a4 = a + 3 * lda;
    a5 = a + 4 * lda;
    a6 = a + 5 * lda;
    // a7 = a + 6 * lda;
    // a8 = a + 7 * lda;

    ii = 0;

    // i = (m >> 3);
    i = (m / 6);
    while (i > 0) {

      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif

	data09 = *(a2 + 0);
#ifndef UNIT
	data10 = *(a2 + 1);
#endif

	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
#ifndef UNIT
	data19 = *(a3 + 2);
#endif

	data25 = *(a4 + 0);
	data26 = *(a4 + 1);
	data27 = *(a4 + 2);
#ifndef UNIT
	data28 = *(a4 + 3);
#endif

	data33 = *(a5 + 0);
	data34 = *(a5 + 1);
	data35 = *(a5 + 2);
	data36 = *(a5 + 3);
#ifndef UNIT
	data37 = *(a5 + 4);
#endif

	data41 = *(a6 + 0);
	data42 = *(a6 + 1);
	data43 = *(a6 + 2);
	data44 = *(a6 + 3);
	data45 = *(a6 + 4);
#ifndef UNIT
	data46 = *(a6 + 5);
#endif

// 	data49 = *(a7 + 0);
// 	data50 = *(a7 + 1);
// 	data51 = *(a7 + 2);
// 	data52 = *(a7 + 3);
// 	data53 = *(a7 + 4);
// 	data54 = *(a7 + 5);
// #ifndef UNIT
// 	data55 = *(a7 + 6);
// #endif
//
// 	data57 = *(a8 + 0);
// 	data58 = *(a8 + 1);
// 	data59 = *(a8 + 2);
// 	data60 = *(a8 + 3);
// 	data61 = *(a8 + 4);
// 	data62 = *(a8 + 5);
// 	data63 = *(a8 + 6);
// #ifndef UNIT
// 	data64 = *(a8 + 7);
// #endif

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;

	*(b +  7) = INV(data10);
	*(b + 8) = data18;
	*(b + 9) = data26;
	*(b + 10) = data34;
	*(b + 11) = data42;
	// *(b + 14) = data50;
	// *(b + 15) = data58;

	*(b + 14) = INV(data19);
	*(b + 15) = data27;
	*(b + 16) = data35;
	*(b + 17) = data43;
	// *(b + 22) = data51;
	// *(b + 23) = data59;

	*(b + 21) = INV(data28);
	*(b + 22) = data36;
	*(b + 23) = data44;
	// *(b + 30) = data52;
	// *(b + 31) = data60;

	*(b + 28) = INV(data37);
	*(b + 29) = data45;
	// *(b + 38) = data53;
	// *(b + 39) = data61;

	*(b + 35) = INV(data46);
	// *(b + 46) = data54;
	// *(b + 47) = data62;

	// *(b + 54) = INV(data55);
	// *(b + 55) = data63;

	// *(b + 63) = INV(data64);
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	data02 = *(a1 + 1);
	data03 = *(a1 + 2);
	data04 = *(a1 + 3);
	data05 = *(a1 + 4);
	data06 = *(a1 + 5);
	// data07 = *(a1 + 6);
	// data08 = *(a1 + 7);

	data09 = *(a2 + 0);
	data10 = *(a2 + 1);
	data11 = *(a2 + 2);
	data12 = *(a2 + 3);
	data13 = *(a2 + 4);
	data14 = *(a2 + 5);
	// data15 = *(a2 + 6);
	// data16 = *(a2 + 7);

	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
	data19 = *(a3 + 2);
	data20 = *(a3 + 3);
	data21 = *(a3 + 4);
	data22 = *(a3 + 5);
	// data23 = *(a3 + 6);
	// data24 = *(a3 + 7);

	data25 = *(a4 + 0);
	data26 = *(a4 + 1);
	data27 = *(a4 + 2);
	data28 = *(a4 + 3);
	data29 = *(a4 + 4);
	data30 = *(a4 + 5);
	// data31 = *(a4 + 6);
	// data32 = *(a4 + 7);

	data33 = *(a5 + 0);
	data34 = *(a5 + 1);
	data35 = *(a5 + 2);
	data36 = *(a5 + 3);
	data37 = *(a5 + 4);
	data38 = *(a5 + 5);
	// data39 = *(a5 + 6);
	// data40 = *(a5 + 7);

	data41 = *(a6 + 0);
	data42 = *(a6 + 1);
	data43 = *(a6 + 2);
	data44 = *(a6 + 3);
	data45 = *(a6 + 4);
	data46 = *(a6 + 5);
	// data47 = *(a6 + 6);
	// data48 = *(a6 + 7);

	// data49 = *(a7 + 0);
	// data50 = *(a7 + 1);
	// data51 = *(a7 + 2);
	// data52 = *(a7 + 3);
	// data53 = *(a7 + 4);
	// data54 = *(a7 + 5);
	// data55 = *(a7 + 6);
	// data56 = *(a7 + 7);

	// data57 = *(a8 + 0);
	// data58 = *(a8 + 1);
	// data59 = *(a8 + 2);
	// data60 = *(a8 + 3);
	// data61 = *(a8 + 4);
	// data62 = *(a8 + 5);
	// data63 = *(a8 + 6);
	// data64 = *(a8 + 7);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;

	*(b +  6) = data02;
	*(b +  7) = data10;
	*(b + 8) = data18;
	*(b + 9) = data26;
	*(b + 10) = data34;
	*(b + 11) = data42;
	// *(b + 14) = data50;
	// *(b + 15) = data58;

	*(b + 12) = data03;
	*(b + 13) = data11;
	*(b + 14) = data19;
	*(b + 15) = data27;
	*(b + 16) = data35;
	*(b + 17) = data43;
	// *(b + 22) = data51;
	// *(b + 23) = data59;

	*(b + 18) = data04;
	*(b + 19) = data12;
	*(b + 20) = data20;
	*(b + 21) = data28;
	*(b + 22) = data36;
	*(b + 23) = data44;
	// *(b + 30) = data52;
	// *(b + 31) = data60;

	*(b + 24) = data05;
	*(b + 25) = data13;
	*(b + 26) = data21;
	*(b + 27) = data29;
	*(b + 28) = data37;
	*(b + 29) = data45;
	// *(b + 38) = data53;
	// *(b + 39) = data61;

	*(b + 30) = data06;
	*(b + 31) = data14;
	*(b + 32) = data22;
	*(b + 33) = data30;
	*(b + 34) = data38;
	*(b + 35) = data46;
	// *(b + 46) = data54;
	// *(b + 47) = data62;

	// *(b + 48) = data07;
	// *(b + 49) = data15;
	// *(b + 50) = data23;
	// *(b + 51) = data31;
	// *(b + 52) = data39;
	// *(b + 53) = data47;
	// *(b + 54) = data55;
	// *(b + 55) = data63;

	// *(b + 56) = data08;
	// *(b + 57) = data16;
	// *(b + 58) = data24;
	// *(b + 59) = data32;
	// *(b + 60) = data40;
	// *(b + 61) = data48;
	// *(b + 62) = data56;
	// *(b + 63) = data64;
      }

      a1 += 6;
      a2 += 6;
      a3 += 6;
      a4 += 6;
      a5 += 6;
      a6 += 6;
      // a7 += 6;
      // a8 += 6;
      b += 36;

      i  --;
      ii += 6;
    }

    if (mmod6 & 4) {
      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif

	data09 = *(a2 + 0);
#ifndef UNIT
	data10 = *(a2 + 1);
#endif

	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
#ifndef UNIT
	data19 = *(a3 + 2);
#endif

	data25 = *(a4 + 0);
	data26 = *(a4 + 1);
	data27 = *(a4 + 2);
#ifndef UNIT
	data28 = *(a4 + 3);
#endif

	data33 = *(a5 + 0);
	data34 = *(a5 + 1);
	data35 = *(a5 + 2);
	data36 = *(a5 + 3);

	data41 = *(a6 + 0);
	data42 = *(a6 + 1);
	data43 = *(a6 + 2);
	data44 = *(a6 + 3);

	// data49 = *(a7 + 0);
	// data50 = *(a7 + 1);
	// data51 = *(a7 + 2);
	// data52 = *(a7 + 3);

	// data57 = *(a8 + 0);
	// data58 = *(a8 + 1);
	// data59 = *(a8 + 2);
	// data60 = *(a8 + 3);

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;

	*(b +  7) = INV(data10);
	*(b + 8) = data18;
	*(b + 9) = data26;
	*(b + 10) = data34;
	*(b + 11) = data42;
	// *(b + 14) = data50;
	// *(b + 15) = data58;

	*(b + 14) = INV(data19);
	*(b + 15) = data27;
	*(b + 16) = data35;
	*(b + 17) = data43;
	// *(b + 22) = data51;
	// *(b + 23) = data59;

	*(b + 21) = INV(data28);
	*(b + 22) = data36;
	*(b + 23) = data44;
	// *(b + 30) = data52;
	// *(b + 31) = data60;

      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	data02 = *(a1 + 1);
	data03 = *(a1 + 2);
	data04 = *(a1 + 3);
	data09 = *(a2 + 0);
	data10 = *(a2 + 1);
	data11 = *(a2 + 2);
	data12 = *(a2 + 3);

	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
	data19 = *(a3 + 2);
	data20 = *(a3 + 3);
	data25 = *(a4 + 0);
	data26 = *(a4 + 1);
	data27 = *(a4 + 2);
	data28 = *(a4 + 3);

	data33 = *(a5 + 0);
	data34 = *(a5 + 1);
	data35 = *(a5 + 2);
	data36 = *(a5 + 3);
	data41 = *(a6 + 0);
	data42 = *(a6 + 1);
	data43 = *(a6 + 2);
	data44 = *(a6 + 3);

	// data49 = *(a7 + 0);
	// data50 = *(a7 + 1);
	// data51 = *(a7 + 2);
	// data52 = *(a7 + 3);
	// data57 = *(a8 + 0);
	// data58 = *(a8 + 1);
	// data59 = *(a8 + 2);
	// data60 = *(a8 + 3);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;

	*(b +  6) = data02;
	*(b +  7) = data10;
	*(b + 8) = data18;
	*(b + 9) = data26;
	*(b + 10) = data34;
	*(b + 11) = data42;
	// *(b + 14) = data50;
	// *(b + 15) = data58;

	*(b + 12) = data03;
	*(b + 13) = data11;
	*(b + 14) = data19;
	*(b + 15) = data27;
	*(b + 16) = data35;
	*(b + 17) = data43;
	// *(b + 22) = data51;
	// *(b + 23) = data59;

	*(b + 18) = data04;
	*(b + 19) = data12;
	*(b + 20) = data20;
	*(b + 21) = data28;
	*(b + 22) = data36;
	*(b + 23) = data44;
	// *(b + 30) = data52;
	// *(b + 31) = data60;
      }

      a1 += 4;
      a2 += 4;
      a3 += 4;
      a4 += 4;
      a5 += 4;
      a6 += 4;
      // a7 += 4;
      // a8 += 4;
      b += 24;
      ii += 4;
    }

    if (mmod6 & 2) {
      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif
	data09 = *(a2 + 0);
#ifndef UNIT
	data10 = *(a2 + 1);
#endif

	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
	data25 = *(a4 + 0);
	data26 = *(a4 + 1);

	data33 = *(a5 + 0);
	data34 = *(a5 + 1);
	data41 = *(a6 + 0);
	data42 = *(a6 + 1);

	// data49 = *(a7 + 0);
	// data50 = *(a7 + 1);
	// data57 = *(a8 + 0);
	// data58 = *(a8 + 1);

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;

	*(b +  7) = INV(data10);
	*(b + 8) = data18;
	*(b + 9) = data26;
	*(b + 10) = data34;
	*(b + 11) = data42;
	// *(b + 14) = data50;
	// *(b + 15) = data58;
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	data02 = *(a1 + 1);
	data09 = *(a2 + 0);
	data10 = *(a2 + 1);
	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
	data25 = *(a4 + 0);
	data26 = *(a4 + 1);

	data33 = *(a5 + 0);
	data34 = *(a5 + 1);
	data41 = *(a6 + 0);
	data42 = *(a6 + 1);
	// data49 = *(a7 + 0);
	// data50 = *(a7 + 1);
	// data57 = *(a8 + 0);
	// data58 = *(a8 + 1);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;

	*(b +  6) = data02;
	*(b +  7) = data10;
	*(b + 8) = data18;
	*(b + 9) = data26;
	*(b + 10) = data34;
	*(b + 11) = data42;
	// *(b + 14) = data50;
	// *(b + 15) = data58;
      }

      a1 += 2;
      a2 += 2;
      a3 += 2;
      a4 += 2;
      a5 += 2;
      a6 += 2;
      a7 += 2;
      a8 += 2;
      b += 12;
      ii += 2;
    }

    if (mmod6 & 1) {
      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif
	data09 = *(a2 + 0);
	data17 = *(a3 + 0);
	data25 = *(a4 + 0);
	data33 = *(a5 + 0);
	data41 = *(a6 + 0);
	// data49 = *(a7 + 0);
	// data57 = *(a8 + 0);

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	// data02 = *(a1 + 1);
	data09 = *(a2 + 0);
	// data10 = *(a2 + 1);
	data17 = *(a3 + 0);
	// data18 = *(a3 + 1);
	data25 = *(a4 + 0);
	// data26 = *(a4 + 1);

	// // data33 = *(a5 + 0);
	// data34 = *(a5 + 1);
	// // data41 = *(a6 + 0);
	// data42 = *(a6 + 1);
	// data49 = *(a7 + 0);
	// data50 = *(a7 + 1);
	// data57 = *(a8 + 0);
	// data58 = *(a8 + 1);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data33;
	*(b +  5) = data41;
	// *(b +  6) = data49;
	// *(b +  7) = data57;
      }
      b += 6;
      // ii += 1;
    }

    a +=  6 * lda;
    jj += 6;
    j  --;
  }


  if (nmod6 & 4) {
    a1 = a + 0 * lda;
    a2 = a + 1 * lda;
    a3 = a + 2 * lda;
    a4 = a + 3 * lda;

    ii = 0;

    i = (m >> 1);
    while (i > 0) {

      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif

	data09 = *(a2 + 0);
#ifndef UNIT
	data10 = *(a2 + 1);
#endif

	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
#ifndef UNIT
	data19 = *(a3 + 2);
#endif

	data25 = *(a4 + 0);
	data26 = *(a4 + 1);
	data27 = *(a4 + 2);
#ifndef UNIT
	data28 = *(a4 + 3);
#endif

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;

	*(b +  5) = INV(data10);
	*(b +  6) = data18;
	*(b +  7) = data26;

	*(b + 10) = INV(data19);
	*(b + 11) = data27;

	*(b + 15) = INV(data28);

      a1 += 4;
      a2 += 4;
      a3 += 4;
      a4 += 4;
      b += 16;

      i  -= 2;
      ii += 4;
      }

     else if (ii < jj) {
	data01 = *(a1 + 0);
	data02 = *(a1 + 1);
	data09 = *(a2 + 0);
	data10 = *(a2 + 1);
	data17 = *(a3 + 0);
	data18 = *(a3 + 1);
	data25 = *(a4 + 0);
	data26 = *(a4 + 1);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
	*(b +  4) = data02;
	*(b +  5) = data10;
	*(b +  6) = data18;
	*(b +  7) = data26;

      a1 += 2;
      a2 += 2;
      a3 += 2;
      a4 += 2;
      b +=  8;

      i -- ;
      ii += 2;
      }

    else{

      a1 += 2;
      a2 += 2;
      a3 += 2;
      a4 += 2;
      b +=  8;

      i -- ;
      ii += 2;
    }
    }

    if (m & 1) {
      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif
	data09 = *(a2 + 0);
	data17 = *(a3 + 0);
	data25 = *(a4 + 0);

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	data09 = *(a2 + 0);
	data17 = *(a3 + 0);
	data25 = *(a4 + 0);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data17;
	*(b +  3) = data25;
      }
      b += 4;
      // ii += 1;
    }

    a +=  4 * lda;
    jj += 4;
  }

  if (nmod6 & 2) {
    a1 = a + 0 * lda;
    a2 = a + 1 * lda;

    ii = 0;

    i = (m >> 1);
    while (i > 0) {

      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif

	data09 = *(a2 + 0);
#ifndef UNIT
	data10 = *(a2 + 1);
#endif

	*(b +  0) = INV(data01);
	*(b +  1) = data09;

	*(b +  3) = INV(data10);
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	data02 = *(a1 + 1);
	data09 = *(a2 + 0);
	data10 = *(a2 + 1);

	*(b +  0) = data01;
	*(b +  1) = data09;
	*(b +  2) = data02;
	*(b +  3) = data10;
      }

      a1 += 2;
      a2 += 2;
      b +=  4;

      i  --;
      ii += 2;
    }

    if (m & 1) {
      if (ii == jj) {

#ifndef UNIT
	data01 = *(a1 + 0);
#endif
	data09 = *(a2 + 0);

	*(b +  0) = INV(data01);
	*(b +  1) = data09;
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	data09 = *(a2 + 0);

	*(b +  0) = data01;
	*(b +  1) = data09;
      }
      b += 2;
      // ii += 1;
    }

    a +=  2 * lda;
    jj += 2;
  }

  if (nmod6 & 1) {
    a1 = a + 0 * lda;

    ii = 0;

    i = m;
    while (i > 0) {

      if (ii == jj) {
#ifndef UNIT
	data01 = *(a1 + 0);
#endif
	*(b +  0) = INV(data01);
      }

      if (ii < jj) {
	data01 = *(a1 + 0);
	*(b +  0) = data01;
      }

      a1 += 1;
      b +=  1;
      i  --;
      ii ++;
    }
  }

  return 0;
}
