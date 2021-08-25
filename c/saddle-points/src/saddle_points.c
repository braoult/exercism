#include <stdbool.h>

#include "saddle_points.h"

#define POOL_SIZE 10
#define MAX_STACK 1024

static saddle_point_t stack[MAX_STACK];
static int stack_pos;

static int push_maybe(uint8_t max, uint8_t val, uint8_t r, uint8_t c)
{
    if (val > max) {                              /* new max value */
        max = val;
        stack_pos = 0;
    }
    if (val == max) {
        if (stack_pos == MAX_STACK)               /* stack overflow */
            return -1;
        stack[stack_pos] = (saddle_point_t) {r, c};
        stack_pos++;
    }
    return max;
}

static saddle_point_t *pop()
{
    if (!stack_pos)
        return NULL;
    stack_pos--;
    return &stack[stack_pos];
}

static saddle_points_t *new_saddle_points()
{
    saddle_points_t *t = malloc(sizeof(saddle_points_t));
    if (t) {
        t->count  = 0;
        t->pool   = 0;
        t->points = NULL;
    }
    return t;
}

static saddle_points_t *add_point(saddle_points_t *saddle, const uint8_t r,
                                  const uint8_t c)
{
    /* we may directly call add_point() without new_saddle_points().
     * Not used here, but could be useful if triplets_with_sum() should
     * return NULL when no solution found, instead of empty set.
     */
    if (! (saddle || (saddle = new_saddle_points())))
        return NULL;

    if (saddle->count == saddle->pool) {
        saddle->pool += POOL_SIZE;
        if (!(saddle->points = realloc(saddle->points, sizeof(saddle) +
                                  saddle->pool * sizeof(saddle_point_t)))) {
            free(saddle);
            return NULL;
        }
    }
    saddle->points[saddle->count++] = (saddle_point_t) {r, c};
    return saddle;
}

saddle_points_t *saddle_points(uint8_t ro, uint8_t co, uint8_t m[ro][co])
{
    saddle_points_t *saddle;
    saddle_point_t *possible;

    if (!(saddle = new_saddle_points()))
        return NULL;
    /* find largest value in each row */
    for (int16_t row = 0; row < ro; ++row) {
        int max = 0;
        for (int16_t col = 0; col < co; ++col) {
            /* partial result (stack overflow) */
            if ((max = push_maybe(max, m[row][col], row, col)) < 0)
                return saddle;
        }
        /* we have now the largest row values on stack, we check if they are
         * saddle points (= lowest in their columns)
         */
        while ((possible = pop())) {
            for (int r1 = 0; r1 < ro; ++r1) {
                if (m[possible->row][possible->column] > m[r1][possible->column])
                    goto not_saddle;
            }
            saddle = add_point(saddle, possible->row+1, possible->column+1);
        not_saddle: ;
        }
    }
    return saddle;
}

void free_saddle_points(saddle_points_t *s)
{
    free(s->points);
    free(s);
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
#include <stdio.h>

int main(int ac, char **av)
{
    int arg;
    uint8_t row, col;
    saddle_points_t *s;

    if (ac > 3) {
        row=atoi(av[1]);
        col=atoi(av[2]);
        arg=3;
        if ((ac-3) == row*col) {
            uint8_t array[row][col];
            uint8_t *p=(uint8_t *)array;
            printf("row=%d col=%d ac=%d arg=%d\n", row, col, ac, arg);
            while (arg<ac)
                *p++=atoi(av[arg++]);

            for (int r=0; r<row; ++r) {
                for (int c=0; c<col; ++c) {
                    printf("%d ", array[r][c]);
                }
                printf("\n");
            }
            s = saddle_points(row, col, array);
            printf("saddles: %lu\n", s->count);
            for (unsigned i=0; i<s->count; ++i) {
                printf("%u: (%u, %u)\n", i, s->points[i].column,
                       s->points[i].row);

            }
        }
    }
}
#endif
