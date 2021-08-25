#ifndef SADDLE_POINTS_H
#define SADDLE_POINTS_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t row;
    uint8_t column;
} saddle_point_t;

typedef struct {
    size_t count;
    size_t pool;
    saddle_point_t *points;
} saddle_points_t;

extern saddle_points_t *saddle_points(uint8_t rows, uint8_t columns,
                                      uint8_t matrix[rows][columns]);

extern void free_saddle_points(saddle_points_t *saddle_point);

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
