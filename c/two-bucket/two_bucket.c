#include "two_bucket.h"
#include <stdio.h>
#include <stdlib.h>

/* We will choose to use a board of (X,Y) squares, with the sizes of the 2
 * buckets (in fact +1, as buckets can have values 0...max), where we move
 * the current point at each step.
 * Current square (x,y) is enough to describe the status of the
 * 2 buckets: b1 has x liters, b2 has y liters.
 * At square (x, y), a maximum of 6 moves are possible :
 *    - (0, y)          = empty b1
 *    - (X, y)          = fill b1
 *    - (x, 0)          = empty b2
 *    - (x, Y)          = fill b2
 *    - (x - d, y + d)  = b1 -> b2, with d = min(Y-y, x)
 *    - (x + d, y - d)  = b2 -> b1, with d = min(X-x, y)
 * The board keeps tracks of visited squares: We cannot pass twice the
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

/* from (col, row) to real array position (square), and vice-et-versa.
 * X is column size.
 */
#define SQUARE(col, row, board)  ((row) * (board->X) + (col))
#define COL(square, board)       ((square) % (board->X))
#define ROW(square, board)       ((square) / (board->X))

/* danger zone !! - this macro is BAD™ in general, dangerous double
 * evaluation, but ok here.
 * What did you ask ? Oh, yes, of course, I never use this macro, this is
 * the first and last time ;-)
 * If unsure why this is very bad™, let me a comment on exercism.
 */
#define MIN(x, y)         ((x) <= (y)? (x): (y))

/* a queue for moves (BFS). I use a stupid max value, a linked list would
 * be much better, would the buckets sizes being extremely huge.
 */
struct stack {
    int first;
    int last;
    int s[];
};

/* our board: Warning, X/Y are from 0 to size, not C array size.
 * Example, if cols=2 and rows
 */
struct board {
    int X;
    int Y;
    int board[];
};

static void board_print(struct board *board)
{
    int x=board->X, y=board->Y;
    printf("board(%d, %d)\n", x, y);
    for (int row = y-1; row >= 0; --row) {
        printf("%03d  ", row);
        for (int col = 0; col < x; ++col) {
            //printf("C: i=%d j=%d cell %d\n", i, j, i*x+j);
            //printf(" %d ", board[i*x+j]);
            printf(" %2d ", board->board[SQUARE(col, row, board)]);
            //printf("row=%d col=%d x=%d square=%d\n", row, col, x, SQUARE(col, row, x));
        }
        putchar('\n');
    }
    putchar('\n');
}

static inline void board_init(struct board *board, int goal)
{
    int i, x=board->X, y=board->Y;

    printf("board_init(%d, %d, goal=%d)\n", x, y, goal);
    //board_print(board, x, y);
    for (i=0; i < x*y; ++i) {
        printf("setting square %d (%d, %d)\n", i, COL(i, board), ROW(i, board));
        *(board->board+i) = AVAILABLE;
    }
    board_print(board);
    /* set target on goal row */
    if (x > goal) {
        for (i = 0; i < y; ++i) {
            printf("A: x=%d i=%d goal=%d setting %d\n", x, i, goal, SQUARE(goal, i, board));
            board->board[SQUARE(goal, i, board)] = GOAL;
            //board_print(board, x, y);
        }
    }
    /* set target on goal col */
    board_print(board);
    if (y > goal) {
        for (i = 0; i < x; ++i) {
            printf("B: x=%d i=%d goal=%d setting %d\n", x, i, goal, SQUARE(i, goal, board));
            board->board[SQUARE(i, goal, board)] = GOAL;
        }
        board_print(board);
    }
}

static inline void enqueue(struct stack *s, int v)
{
    printf("pushing v=%d\n", v);
    //if (s->stack[s->last] == AVAILABLE)
    s->s[s->last++] = v;
}

static inline int dequeue(struct stack *s)
{
    int res;
    printf("dequeue: first=%d last=%d val=%d\n", s->first, s->last, s->s[s->first]);
    res = s->first < s->last ? s->s[s->first++] : -1;
    printf("popping v=%d\n", res);
    return res;
}

static int move(struct board *board, struct stack *stack, int col, int row,
                      int level, char *text)
{
    printf("move to [%s] on (%d, %d) - level=%d curval=%d : ",
           text, col, row, level, board->board[SQUARE(col, row, board)]);
    board->board[SQUARE(col, row, board)] = level;
    enqueue (stack, SQUARE(col, row, board));
    return 0;
}

static int move_maybe(struct board *board, struct stack *stack, int col, int row,
                      int level, char *text)
{
    printf("trying to [%s] on (%d, %d) - level=%d curval=%d : ",
           text, col, row, level, board->board[SQUARE(col, row, board)]);
    if (board->board[SQUARE(col, row, board)] == AVAILABLE) {
        printf("OK\n");

        move(board, stack, col, row, level, text);
        //board->board[SQUARE(col, row, board)] = level;
        //enqueue (stack, SQUARE(col, row, board));
    } else if (board->board[SQUARE(col, row, board)] == GOAL) {
        printf("**************** GOAL\n");
        return 1;
    } else {
        printf("Impossible\n");
    }
    return 0;
}

static bucket_result_t board_bfs(struct board *board, struct stack *stack, int start,
                                 const int goal)
{
    int level = 0;
    int cur_square;
    int min, row, col, col1, row1;
    int X=board->X, Y=board->Y;
    bucket_result_t res = { .possible = false, .move_count = 0 };
    /* initialize 1st square used */
    printf("bfs(start=%d, X=%d, Y=%d)\n", start, board->X, board->Y);

    /* now we consume as we can... */
    while ((cur_square = dequeue(stack)) >= 0) {
        col=COL(cur_square, board);
        row=ROW(cur_square, board);
        level=board->board[cur_square];
        board_print(board);
        printf("move[pop=%d](col=%d, row=%d)=%d level=%d\n",
               cur_square, col, row, board->board[cur_square], level);
        if (col > 0) {
            col1 = 0;
            row1 = row;
            if (move_maybe(board, stack, col1, row1, level+1, "empty b1"))
                goto found;
        }
        if (row > 0) {
            col1 = col;
            row1 = 0;
            if (move_maybe(board, stack, col1, row1, level+1, "empty b2"))
                goto found;
        }
        if (col < X-1) {
            col1 = X-1;
            row1 = row;
            if (move_maybe(board, stack, col1, row1, level+1, "fill b1"))
                goto found;
        }
        if (row < Y-1) {
            col1 = col;
            row1 = Y-1;
            if (move_maybe(board, stack, col1, row1, level+1, "fill b2"))
                goto found;
        }
        if (col > 0 && row < Y-1) {
            min = MIN(col, Y-row-1);
            col1 = col-min;
            row1 = row+min;
            if (move_maybe(board, stack, col1, row1, level+1, "pour b1 in b2"))
                goto found;
        }
        if (row > 0 && col < X-1) {
            min = MIN(row, X-col-1);
            col1 = col+min;
            row1 = row-min;
            if (move_maybe(board, stack, col1, row1, level+1, "pour b2 in b1"))
                goto found;
        }
    }
    goto end;                                     /* no more possible move */
found:
    res.possible = true;
    res.move_count = level+1;
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
    struct board *board;
    struct stack *stack;

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

    if (!(stack = malloc(sizeof(*stack) + sizeof(*stack->s)*(b1+1)*(b2+1))))
        return res;
    stack->first = 0;
    stack->last = 0;
    printf("board size: %lu int=%lu n=%d, %lu\n", sizeof(*board), sizeof(int),
           (b1+1)*(b2+1),
           sizeof(*board) + sizeof(*board->board)*(b1+1)*(b2+1));
    if (!(board = malloc(sizeof(*board) + sizeof(*board->board)*(b1+1)*(b2+1)))) {
        free(stack);
        return res;
    }
    board->X = b1+1;
    board->Y = b2+1;
    board_init(board, goal);
    /* only for exercism. better solutions could be found. Remove the next
     * 3 lines to allow a different starting bucket (possibly better solution).
     */
    board->board[SQUARE(0, 0, board)] = FORBIDDEN;
    board->board[SQUARE(0, b2, board)] = FORBIDDEN;
    board->board[SQUARE(b1, 0, board)] = FORBIDDEN;

    if (start == BUCKET_ID_1) {
        move(board, stack, b1, 0, 1, "start with b1");
        //enqueue(stack, SQUARE(b1, 0, board));
        //board->board[SQUARE(b1, 0, board)] = 1;
    } else {
        move(board, stack, 0, b2, 1, "start with b1");
        //enqueue(stack, SQUARE(0, b2, board));
        //board->board[SQUARE(0, b2, board)] = 1;
    }
    board_print(board);

    res = board_bfs(board, stack, start, goal);
    free(stack);
    free(board);
    return res;
}

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    int b1, b2, goal, start;
    bucket_result_t res;;

    for (; arg<ac-3; arg+=4) {
        b1     = atoi(av[arg]);
        b2     = atoi(av[arg+1]);
        goal   = atoi(av[arg+2]);
        start  = atoi(av[arg+2]);
        printf("b1=%d, b2=%d, goal=%d, start=%d\n", b1, b2, goal, start);
        res = measure(b1, b2, goal, start);
        printf("   pos=%d count=%d goal=%d liters=%d\n",
               res.possible, res.move_count, res.goal_bucket,
               res.other_bucket_liters);
    }
}
#endif
