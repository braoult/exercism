#include "complex_numbers.h"

#ifdef USE_COMPLEX_FUNCTIONS

complex_t c_add(complex_t a, complex_t b)
{
    return (complex_t) {
        .real = a.real+b.real,
        .imag = a.imag+b.imag
    };
}

complex_t c_sub(complex_t a, complex_t b)
{
    return (complex_t) {
        .real = a.real-b.real,
        .imag = a.imag-b.imag
    };
}

complex_t c_mul(complex_t a, complex_t b)
{
    return (complex_t) {
        .real = a.real*b.real - a.imag*b.imag,
        .imag = a.imag*b.real + a.real*b.imag,
    };
}

complex_t c_div(complex_t a, complex_t b)
{
    double d = b.real*b.real + b.imag*b.imag;
    return (complex_t) {
        .real = (a.real*b.real + a.imag*b.imag)/d,
        .imag = (a.imag*b.real - a.real*b.imag)/d
    };
}

double c_abs(complex_t x)
{
    return sqrt(x.real*x.real + x.imag*x.imag);
}

complex_t c_conjugate(complex_t x)
{
    return (complex_t) {
        .real = x.real,
        .imag = -x.imag
    };
}

double c_real(complex_t x)
{
    return x.real;
}

double c_imag(complex_t x)
{
    return x.imag;
}

complex_t c_exp(complex_t x)
{
    return (complex_t) {
        .real = exp(x.real)*cos(x.imag),
        .imag = exp(x.real)*sin(x.imag)
    };
}

#endif

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int arg=1;
    complex_t c1, c2, c3;

    for (; arg<ac-3; ++arg, ++arg) {
        c1.real=atof(av[arg]);
        c1.imag=atof(av[arg+1]);

        c2.real=atof(av[arg+2]);
        c2.imag=atof(av[arg+3]);
        c3 = c_add(c1, c2);
        printf("(%f + %fi) + (%f + %fi) = (%f + %fi)\n",
               c1.real, c1.imag,
               c2.real, c2.imag,
               c3.real, c3.imag);
    }
}
#endif
