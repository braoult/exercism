#include "two_bucket.h"
#include <stdio.h>
#include <stdlib.h>

/* We will choose to use a board of (X,Y) squares, with the sizes of the 2
 * buckets, where we move the current point at each step.
 * Current square (x,y) is enough to describe the status of the
 * 2 buckets: b1 has x liters, b2 has y liters.
 * At square (x, y), a maximum of 6 moves are possible :
 *    - (0, y)          = empty b1
 *    - (X, y)          = fill b1
 *    - (x, 0)          = empty be
 *    - (x, Y)          = fill b2
 *    - (x - d, y + d)  = b1 -> b2, with d = min(Y-y, x)
 *    - (x + d, y - d)  = b2 -> b1, with d = min(X-x, y)
 * The board keeps tracks of visited squares. We cannot pass twice the
 * same one.
 * We will use BFS algorithm from initial square, which is (0, Y) or (X, 0).
 * We stop when x or y are equal to goal, or when no moves are possible.
 *
 */

/* The board contains a positive integer for its current move, otherwise the
 * following values
 */
#define AVAILABLE         0
#define FORBIDDEN         (-1)
#define GOAL              (-2)
//#define CURRENT           (-4)

#define SQUARE(x, y, X)   ((y) * (X) + (x))
#define COL(p, X)         ((p) % (X))
#define ROW(p, X)         ((p) / (X))

/* danger zone !! - this macro is BAD™ in general, dangerous double
 * evaluation, but ok here. OK, I promise, only here ;-)
 * If unsure why this is very bad™, let me a comment on exercism.
 */
#define MAX(x, y)         ((x) >= (y)? (x): (y))
#define MIN(x, y)         ((x) <= (y)? (x): (y))

static void board_print(int *board, int x, int y)
{
    printf("board(%d, %d)\n", x, y);
    for (int row = y-1; row >= 0; --row) {
        printf("%03d  ", row);
        for (int col = 0; col < x; ++col) {
            //printf("C: i=%d j=%d cell %d\n", i, j, i*x+j);
            //printf(" %d ", board[i*x+j]);
            printf(" %2d ", board[SQUARE(col, row, x)]);
            //printf("row=%d col=%d x=%d square=%d\n", row, col, x, SQUARE(col, row, x));
        }
        putchar('\n');
    }
    putchar('\n');
}

static inline void board_init(int x, int y, int goal, int *board)
{
    int i;

    printf("board_init(%d, %d, goal=%d)\n", x, y, goal);
    //board_print(board, x, y);
    for (i=0; i < x*y; ++i) {
        //printf("setting square %d (%d, %d)\n", i, COL(i, x), ROW(i, x));
        *(board+i) = AVAILABLE;
    }
    board_print(board, x, y);
    /* set target on goal row */
    if (x >= goal) {
        for (i = 0; i < y; ++i) {
            printf("A: x=%d i=%d goal=%d setting %d\n", x, i, goal, SQUARE(goal, i, x));
            board[SQUARE(goal, i, x)] = GOAL;
            //board_print(board, x, y);
        }
    }
    /* set target on goal col */
    board_print(board, x, y);
    if (y >= goal) {
        for (i = 0; i < x; ++i) {
            printf("B: x=%d i=%d goal=%d setting %d\n", x, i, goal, SQUARE(i, goal, x));
            board[SQUARE(i, goal, x)] = GOAL;
        }
        board_print(board, x, y);
    }
}

struct stack {
    int first;
    int last;
    int stack[];
};

static inline void push(struct stack *s, int v)
{
    printf("pushing v=%d\n", v);
    //if (s->stack[s->last] == AVAILABLE)
        s->stack[s->last++] = v;
}

static inline int pop(struct stack *s)
{
    int res;
    printf("pop: first=%d last=%d val=%d\n", s->first, s->last, s->stack[s->first]);
    res = s->first < s->last ? s->stack[s->first++] : -1;
    printf("popping v=%d\n", res);
    return res;
}

static int move_maybe(int *board, struct stack *stack, int col, int row, int level ,int X, char *text)
{
    printf("trying to [%s] on (%d, %d) - level=%d curval=%d : ",
           text, col, row, level, board[SQUARE(col, row, X)]);
    if (board[SQUARE(col, row, X)] == AVAILABLE) {
        printf("OK\n");

        board[SQUARE(col, row, X)] = level;
        push (stack, SQUARE(col, row, X));
    } else if (board[SQUARE(col, row, X)] == GOAL) {
        printf("**************** GOAL\n");
        return 1;
    } else {
        printf("Impossible\n");
    }
    return 0;
}

static bucket_result_t board_bfs(int *board, struct stack *stack, int start,
                                 const int X, const int Y, const int goal)
{
    int level = 0;
    int cur_square;
    int min, row, col, col1, row1;
    bucket_result_t res = { .possible = false, .move_count = 0 };
    /* initialize 1st square used */
    printf("bfs(start=%d, X=%d, Y=%d)\n", start, X, Y);

    if (start == BUCKET_ID_1) {
        push(stack, SQUARE(X-1, 0, X));
        board[SQUARE(X-1, 0, X)] = 1;
        board[SQUARE(0, Y-1, X)] = FORBIDDEN;
    } else {
        push(stack, SQUARE(0, Y-1, X));
        board[SQUARE(0, Y-1, X)] = 1;
        board[SQUARE(X-1, 0, X)] = FORBIDDEN;
    }
    board_print(board, X, Y);
    /* now we consume as we can... */
    while ((cur_square = pop(stack)) >= 0) {
        col=COL(cur_square, X);
        row=ROW(cur_square, X);
        level=board[cur_square];
        board_print(board, X, Y);
        printf("move[pop=%d](col=%d, row=%d)=%d level=%d\n",
               cur_square, col, row, board[cur_square], level);
        switch (level) {
            case GOAL:                            /* we win */
                printf("*** SHOULD NOT BE HERE\n");
                goto found;
            case AVAILABLE:                       /* should not happen */
                goto end;
            default:
                if (col > 0) {
                    col1 = 0;
                    row1 = row;
                    if (move_maybe(board, stack, col1, row1, level+1, X, "empty b1"))
                        goto found;
                }
                if (row > 0) {
                    col1 = col;
                    row1 = 0;
                    if (move_maybe(board, stack, col1, row1, level+1, X, "empty b2"))
                        goto found;
                }
                if (col < X-1) {
                    col1 = X-1;
                    row1 = row;
                    if (move_maybe(board, stack, col1, row1, level+1, X, "fill b1"))
                        goto found;
                }
                if (row < Y-1) {
                    col1 = col;
                    row1 = Y-1;
                    if (move_maybe(board, stack, col1, row1, level+1, X, "fill b2"))
                        goto found;
                }
                if (col > 0 && row < Y-1) {
                    min = MIN(col, Y-row-1);
                    col1 = col-min;
                    row1 = row+min;
                    if (move_maybe(board, stack, col1, row1, level+1, X,
                                   "pour b1 in b2"))
                        goto found;
                }
                if (row > 0 && col < X-1) {
                    min = MIN(row, X-col-1);
                    col1 = col+min;
                    row1 = row-min;
                    if (move_maybe(board, stack, col1, row1, level+1, X,
                                   "pour b2 in b1"))
                        goto found;
                }
        }
    }
    goto end;
found:
    res.possible = true;
    res.move_count = level+1;//board[SQUARE(col1, row1, X)]+1;
    if (col1 == goal) {
        res.goal_bucket=BUCKET_ID_1;
        res.other_bucket_liters=row1;
    } else {
        res.goal_bucket=BUCKET_ID_2;
        res.other_bucket_liters=col1;
    }
end:
    printf("END: possible=%d\n", res.possible);
    printf("     move-count=%d\n", res.move_count);
    printf("     goal-bucket=%d\n", res.goal_bucket);
    printf("     other-bucket=%d\n", res.other_bucket_liters);
    return res;
}


bucket_result_t measure(const bucket_liters_t b1,
                        const bucket_liters_t b2,
                        const bucket_liters_t goal,
                        const bucket_id_t start)
{
    bucket_result_t res = {
        .possible            = false,
        .move_count          = 0,
        .other_bucket_liters = 0
    };
    int board[(b1+1)*(b2+1)];

    printf("measure(b1=%d, b2=%d, goal=%d, start=%d)\n", b1, b2, goal, start);
    if (goal > b1 && goal > b2)
        return res;
    if ((start == BUCKET_ID_1 && goal == b1) ||
        (start == BUCKET_ID_2 && goal == b2)) {
        printf("done in 1\n");
        res.possible   = true;
        res.move_count = 1;
        res.goal_bucket = start;
        return res;
    }

    struct stack *stack = malloc(sizeof(*stack) +
                                 sizeof(*stack->stack)*(b1+1)*(b1+1));
    if (!stack)
        return res;
    stack->first = 0;
    stack->last = 0;

    board_init(b1+1, b2+1, goal, board);

    res = board_bfs(board, stack, start, b1+1, b2+1, goal);
    return res;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    int b1, b2, goal, start=0;
    bucket_result_t res;;

    for (; arg<ac-2; arg+=3) {
        b1    = atoi(av[arg]);
        b2    = atoi(av[arg+1]);
        goal  = atoi(av[arg+2]);
        printf("b1=%d, b2=%d, goal=%d, start=%d\n", b1, b2, goal, start);
        res = measure(b1, b2, goal, start);
        printf("   pos=%d count=%d goal=%d liters=%d\n",
               res.possible, res.move_count, res.goal_bucket,
               res.other_bucket_liters);
    }
}
#endif
