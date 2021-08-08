#ifndef DARTS_H
#define DARTS_H

#include <stdbool.h>
#include <float.h>

typedef struct {
    float x, y;
} coordinate_t;

typedef struct {
    float radius;
    int score;
} score_t;

// to allow float comparisons we consider 2 floats are equal if
// their difference is below this value.
// Use: avoid the '<' & '>' which may be wrong.
#define MIN_FLOAT_EQUAL FLT_EPSILON

extern unsigned score(coordinate_t);

#ifdef TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
