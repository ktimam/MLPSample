/*******************************************************************************
Copyright (c) 2023, The OpenBLAS Project
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.
3. Neither the name of the OpenBLAS project nor the names of
its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE OPENBLAS PROJECT OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#define ASSEMBLER

#include "common.h"
#include "loongarch64_asm.S"

/* Function parameters */
#define M      $r4    // param 1: m
#define N      $r5    // param 2: n
#define SRC    $r6    // param 3: src
#define LDA    $r7    // param 4: lda
#define DST    $r8    // param 5: dst

#define I      $r9
#define J      $r10
#define S1     $r12
#define S2     $r13
#define S3     $r14
#define S4     $r15
#define S5     $r16
#define S6     $r17
#define S7     $r18
#define S8     $r19
#define TD     $r20
#define TS     $r21
#define TL     $r7
#define T0     $r6
#define ZERO   $r0

#define F0     $f0
#define F1     $f1
#define F2     $f2
#define F3     $f3
#define F4     $f4
#define F5     $f5
#define F6     $f6
#define F7     $f7
/* LSX vectors */
#define U0     $vr0
#define U1     $vr1
#define U2     $vr2
#define U3     $vr3
#define U4     $vr4
#define U5     $vr5
#define U6     $vr6
#define U7     $vr7
#define D0     $vr8
#define D1     $vr9
#define D2     $vr10
#define D3     $vr11
#define D4     $vr12
#define D5     $vr13
#define D6     $vr14
#define D7     $vr15

    PROLOGUE
    push_if_used 0, 0
    move       TD,   DST
    move       TS,   SRC
    slli.d     TL,   LDA,  0x03
    slli.d     T0,   TL,   0x01
    srai.d     J,    N,    0x03
    beq        J,    ZERO, .L_N4
.L_J1:
    move       S1,   TS
    add.d      S2,   TS,   TL
    srai.d     I,    M,    0x03
    add.d      S3,   S2,   TL
    addi.d     J,    J,    -1
    add.d      S4,   S3,   TL
    add.d      S5,   S3,   T0
    add.d      S6,   S4,   T0
    add.d      S7,   S5,   T0
    add.d      S8,   S6,   T0
    add.d      TS,   S7,   T0
    beq        I,    ZERO, .L_I7
.L_I1:
    GLD v, , U0, S1, 0x00, U1, S2, 0x00, U2, S3, 0x00, U3, S4, 0x00, \
             U4, S5, 0x00, U5, S6, 0x00, U6, S7, 0x00, U7, S8, 0x00
    GINTERLACE v, d, D0, D4, U1, U0
    GINTERLACE v, d, D1, D5, U3, U2
    GINTERLACE v, d, D2, D6, U5, U4
    GINTERLACE v, d, D3, D7, U7, U6
    GST v, , D0, TD, 0x00, D1, TD, 0x10, D2, TD, 0x20, D3, TD, 0x30, \
             D4, TD, 0x40, D5, TD, 0x50, D6, TD, 0x60, D7, TD, 0x70
    addi.d    TD,    TD,   0x80
    GLD v, , U0, S1, 0x10, U1, S2, 0x10, U2, S3, 0x10, U3, S4, 0x10, \
             U4, S5, 0x10, U5, S6, 0x10, U6, S7, 0x10, U7, S8, 0x10
    GINTERLACE v, d, D0, D4, U1, U0
    GINTERLACE v, d, D1, D5, U3, U2
    GINTERLACE v, d, D2, D6, U5, U4
    GINTERLACE v, d, D3, D7, U7, U6
    GST v, , D0, TD, 0x00, D1, TD, 0x10, D2, TD, 0x20, D3, TD, 0x30, \
             D4, TD, 0x40, D5, TD, 0x50, D6, TD, 0x60, D7, TD, 0x70
    addi.d    TD,    TD,   0x80
    GLD v, , U0, S1, 0x20, U1, S2, 0x20, U2, S3, 0x20, U3, S4, 0x20, \
             U4, S5, 0x20, U5, S6, 0x20, U6, S7, 0x20, U7, S8, 0x20
    GINTERLACE v, d, D0, D4, U1, U0
    GINTERLACE v, d, D1, D5, U3, U2
    GINTERLACE v, d, D2, D6, U5, U4
    GINTERLACE v, d, D3, D7, U7, U6
    GST v, , D0, TD, 0x00, D1, TD, 0x10, D2, TD, 0x20, D3, TD, 0x30, \
             D4, TD, 0x40, D5, TD, 0x50, D6, TD, 0x60, D7, TD, 0x70
    addi.d    TD,    TD,   0x80
    GLD v, , U0, S1, 0x30, U1, S2, 0x30, U2, S3, 0x30, U3, S4, 0x30, \
             U4, S5, 0x30, U5, S6, 0x30, U6, S7, 0x30, U7, S8, 0x30
    GINTERLACE v, d, D0, D4, U1, U0
    GINTERLACE v, d, D1, D5, U3, U2
    GINTERLACE v, d, D2, D6, U5, U4
    GINTERLACE v, d, D3, D7, U7, U6
    GST v, , D0, TD, 0x00, D1, TD, 0x10, D2, TD, 0x20, D3, TD, 0x30, \
             D4, TD, 0x40, D5, TD, 0x50, D6, TD, 0x60, D7, TD, 0x70
    addi.d    TD,    TD,   0x80

    addi.d     S1,   S1,   0x40
    addi.d     S2,   S2,   0x40
    addi.d     S3,   S3,   0x40
    addi.d     S4,   S4,   0x40
    addi.d     S5,   S5,   0x40
    addi.d     S6,   S6,   0x40
    addi.d     S7,   S7,   0x40
    addi.d     S8,   S8,   0x40

    addi.d     I,    I,    -1
    blt        ZERO, I,    .L_I1
.L_I7:
    andi      I,     M,    0x07
    beq       I,     ZERO, .L_I0
.L_II1: /* I-- */
    fld.d     F0,    S1,  0x00
    fld.d     F1,    S2,  0x00
    fld.d     F2,    S3,  0x00
    fld.d     F3,    S4,  0x00
    fld.d     F4,    S5,  0x00
    fld.d     F5,    S6,  0x00
    fld.d     F6,    S7,  0x00
    fld.d     F7,    S8,  0x00

    fst.d     F0,    TD,  0x00
    addi.d    S1,    S1,  0x08
    fst.d     F1,    TD,  0x08
    addi.d    S2,    S2,  0x08
    fst.d     F2,    TD,  0x10
    addi.d    S3,    S3,  0x08
    fst.d     F3,    TD,  0x18
    addi.d    S4,    S4,  0x08
    fst.d     F4,    TD,  0x20
    addi.d    S5,    S5,  0x08
    fst.d     F5,    TD,  0x28
    addi.d    S6,    S6,  0x08
    fst.d     F6,    TD,  0x30
    addi.d    S7,    S7,  0x08
    fst.d     F7,    TD,  0x38
    addi.d    S8,    S8,  0x08
    addi.d    TD,    TD,  0x40

    addi.d    I,     I,   -1
    blt       ZERO,  I,   .L_II1
.L_I0:
    blt       ZERO,  J,   .L_J1
.L_N4:
    andi      J,     N,   0x04
    beq       ZERO,  J,   .L_N2

    move       S1,   TS
    add.d      S2,   TS,   TL
    srai.d     I,    M,    0x02
    add.d      S3,   S2,   TL
    add.d      S4,   S2,   T0
    add.d      TS,   S3,   T0
    beq        I,    ZERO, .L_I3
.L_4I1: /* I-- */
    GLD v, , U0, S1, 0x00, U1, S2, 0x00, U2, S3, 0x00, U3, S4, 0x00
    GINTERLACE v, d, D0, D2, U1, U0
    GINTERLACE v, d, D1, D3, U3, U2
    GST v, , D0, TD, 0x00, D1, TD, 0x10, D2, TD, 0x20, D3, TD, 0x30
    addi.d     TD,   TD,   0x40

    GLD v, , U0, S1, 0x10, U1, S2, 0x10, U2, S3, 0x10, U3, S4, 0x10
    GINTERLACE v, d, D0, D2, U1, U0
    GINTERLACE v, d, D1, D3, U3, U2
    GST v, , D0, TD, 0x00, D1, TD, 0x10, D2, TD, 0x20, D3, TD, 0x30

    addi.d     S1,   S1,   0x20
    addi.d     S2,   S2,   0x20
    addi.d     S3,   S3,   0x20
    addi.d     S4,   S4,   0x20
    addi.d     TD,   TD,   0x40

    addi.d     I,    I,    -1
    blt        ZERO, I,    .L_4I1
.L_I3:
    andi      I,     M,    0x03
    beq       I,     ZERO, .L_N2
.L_4II1:
    fld.d     F0,    S1,  0x00
    fld.d     F1,    S2,  0x00
    fld.d     F2,    S3,  0x00
    fld.d     F3,    S4,  0x00

    fst.d     F0,    TD,  0x00
    addi.d    S1,    S1,  0x08
    fst.d     F1,    TD,  0x08
    addi.d    S2,    S2,  0x08
    fst.d     F2,    TD,  0x10
    addi.d    S3,    S3,  0x08
    fst.d     F3,    TD,  0x18
    addi.d    S4,    S4,  0x08

    addi.d    TD,    TD,  0x20
    addi.d    I,     I,   -1
    blt       ZERO,  I,   .L_4II1
.L_N2:
    andi      J,     N,   0x02
    beq       ZERO,  J,   .L_N1

    move       S1,   TS
    add.d      S2,   TS,   TL
    srai.d     I,    M,    0x01
    add.d      TS,   S2,   TL
    beq        I,    ZERO, .L_NI1
.L_2I1: /* I-- */
    GLD v, , U0, S1, 0x00, U1, S2, 0x00
    GINTERLACE v, d, D0, D1, U1, U0
    GST v, , D0, TD, 0x00, D1, TD, 0x10

    addi.d     S1,   S1,   0x10
    addi.d     S2,   S2,   0x10
    addi.d     TD,   TD,   0x20

    addi.d     I,    I,    -1
    blt        ZERO, I,    .L_2I1
.L_NI1:
    andi      I,     M,    0x01
    beq       I,     ZERO, .L_N1

    fld.d     F0,    S1,  0x00
    fld.d     F1,    S2,  0x00

    fst.d     F0,    TD,  0x00
    addi.d    S1,    S1,  0x08
    fst.d     F1,    TD,  0x08
    addi.d    S2,    S2,  0x08
    addi.d    TD,    TD,  0x10
.L_N1:
    andi      J,     N,   0x01
    beq       ZERO,  J,   .L_N0
    move      S1,    TS
    beq       ZERO,  M,   .L_N0
.L_M1:
    fld.d     F0,    S1,  0x00
    addi.d    S1,    S1,  0x08
    fst.d     F0,    TD,  0x00
    addi.d    TD,    TD,  0x08
    addi.d    M,     M,   -1
    blt       ZERO,  M,   .L_M1
.L_N0:
    pop_if_used 0, 0
    jirl       $r0,  $r1,  0x00
    EPILOGUE
