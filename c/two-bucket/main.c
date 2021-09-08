/* Standalone tests.
 * See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#include "two_bucket.h"

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
        start  = atoi(av[arg+3]);
        printf("b1=%d, b2=%d, goal=%d, start=%d\n", b1, b2, goal, start);
        res = measure(b1, b2, goal, start);
        printf("   pos=%d count=%d goal=%d liters=%d\n",
               res.possible, res.move_count, res.goal_bucket,
               ##res.other_bucket_liters);
    }
}
#endif
