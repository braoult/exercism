#ifndef _COMPLEX_NUMBERS_H_
#define _COMPLEX_NUMBERS_H_
#include <math.h>

typedef struct {
   double real;
   double imag;
} complex_t;

/* default is to use macros */
#ifdef USE_COMPLEX_FUNCTIONS

complex_t c_add(complex_t a, complex_t b);
complex_t c_sub(complex_t a, complex_t b);
complex_t c_mul(complex_t a, complex_t b);
complex_t c_div(complex_t a, complex_t b);
double c_abs(complex_t x);
complex_t c_conjugate(complex_t x);
double c_real(complex_t x);
double c_imag(complex_t x);
complex_t c_exp(complex_t x);

#else

#define c_add(a,b) (complex_t) {                      \
        (a).real+(b).real,                            \
        (a).imag+(b).imag }

#define c_sub(a,b) (complex_t) {                      \
        (a).real-(b).real,                            \
        (a).imag-(b).imag }

#define c_mul(a,b) (complex_t) {                      \
        (a).real*(b).real - (a).imag*(b).imag,        \
        (a).imag*(b).real + (a).real*(b).imag }

#define c_div(a,b) (complex_t) {                      \
        ((a).real*(b).real + (a).imag*(b).imag)/      \
            ((b).real*(b).real + (b).imag*(b).imag),  \
        ((a).imag*(b).real - (a).real*(b).imag)/      \
            ((b).real*(b).real + (b).imag*(b).imag) }

#define c_exp(x) (complex_t) {                        \
        exp((x).real) * cos((x).imag),                \
        exp((x).real) * sin((x).imag) }

#define c_abs(x) { sqrt((x).real*(x).real + (x).imag*(x).imag) }

#define c_conjugate(x) (complex_t){ (x).real, -(x).imag }

#define c_real(x) (x).real

#define c_imag(x) (x).imag


#endif

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
