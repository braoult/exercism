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
 * If unsure why this is very bad, leave me a comment on exercism.
 */
#define MIN(x, y)         ((x) <= (y)? (x): (y))

/* a queue for moves (BFS). I use a max X*Y array, a linked list would
 * be much better, would the buckets sizes being extremely huge.
 */
struct stack {
    int first;
    int last;
    int s[];
};

/* our game board
  */
struct board {
    int X;
    int Y;
    int board[];
};

static inline void board_init(struct board *board, int X, int Y, int goal)
{
    int i;
    board->X=X;
    board->Y=Y;
    for (i=0; i < board->X*board->Y; ++i)
        *(board->board+i) = AVAILABLE;
    /* set target on goal row */
    if (board->X > goal) {
        for (i = 0; i < board->Y; ++i)
            board->board[SQUARE(goal, i, board)] = GOAL;
    }
    /* set target on goal col */
    if (board->Y > goal) {
        for (i = 0; i < board->X; ++i)
            board->board[SQUARE(i, goal, board)] = GOAL;
    }
}

static inline void enqueue(struct stack *s, int v)
{
    s->s[s->last++] = v;
}

static inline int dequeue(struct stack *s)
{
    return s->first < s->last ? s->s[s->first++] : -1;
}

static int move(struct board *board, struct stack *stack, int col, int row,
                      int level)
{
    board->board[SQUARE(col, row, board)] = level;
    enqueue (stack, SQUARE(col, row, board));
    return 0;
}

static int move_maybe(struct board *board, struct stack *stack,
                      int col, int row, int level)
{
    switch (board->board[SQUARE(col, row, board)]) {
        case GOAL:
            return 1;
        case AVAILABLE:
            return move(board, stack, col, row, level);
        default:
            return 0;
    }
}

static bucket_result_t board_bfs(struct board *board, struct stack *stack,
                                 const int goal)
{
    int level = 0;
    int cur_square;
    int min, row, col, col1, row1;
    int X=board->X, Y=board->Y;
    bucket_result_t res = { .possible = false, .move_count = 0 };

    /* now we consume as we can... */
    while ((cur_square = dequeue(stack)) >= 0) {
        col=COL(cur_square, board);
        row=ROW(cur_square, board);
        level=board->board[cur_square];
        if (col > 0) {
            col1 = 0;
            row1 = row;
            if (move_maybe(board, stack, col1, row1, level+1))
                goto found;
        }
        if (row > 0) {
            col1 = col;
            row1 = 0;
            if (move_maybe(board, stack, col1, row1, level+1))
                goto found;
        }
        if (col < X-1) {
            col1 = X-1;
            row1 = row;
            if (move_maybe(board, stack, col1, row1, level+1))
                goto found;
        }
        if (row < Y-1) {
            col1 = col;
            row1 = Y-1;
            if (move_maybe(board, stack, col1, row1, level+1))
                goto found;
        }
        if (col > 0 && row < Y-1) {
            min = MIN(col, Y-row-1);
            col1 = col - min;
            row1 = row + min;
            if (move_maybe(board, stack, col1, row1, level+1))
                goto found;
        }
        if (row > 0 && col < X-1) {
            min = MIN(row, X-col-1);
            col1 = col + min;
            row1 = row - min;
            if (move_maybe(board, stack, col1, row1, level+1))
                goto found;
        }
    }
    goto end;                                     /* fail: no more moves */
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

    /* impossible goal */
    if (goal > b1 && goal > b2)
        return res;

    /* initial move is the solution ? */
    if ((start == BUCKET_ID_1 && goal == b1) ||
        (start == BUCKET_ID_2 && goal == b2)) {
        res.possible   = true;
        res.move_count = 1;
        res.goal_bucket = start;
        return res;
    }

    if (!(stack = malloc(sizeof(*stack) + sizeof(*stack->s)*(b1+1)*(b2+1))))
        return res;
    //int i;
    stack->first = stack->last = 0;
    if (!(board = malloc(sizeof(*board) + sizeof(*board->board)*(b1+1)*(b2+1)))) {
        free(stack);
        return res;
    }
    board_init(board, b1+1, b2+1, goal);
    /* only for exercism. better solutions could be found. Remove the next
     * 3 lines to allow a different starting bucket (possibly better solution).
     */
    board->board[SQUARE(0, 0, board)] = FORBIDDEN;
    board->board[SQUARE(0, b2, board)] = FORBIDDEN;
    board->board[SQUARE(b1, 0, board)] = FORBIDDEN;

    /* initial move */
    move(board, stack, start==BUCKET_ID_1? b1: 0, start==BUCKET_ID_2? b2: 0, 1);

    res = board_bfs(board, stack, goal);
    free(stack);
    free(board);
    return res;
}
