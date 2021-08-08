#include "resistor_color_trio.h"

#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

static const unsigned p10[] = {
    1e0, 1e1, 1e2, 1e3, 1e4,
    1e5, 1e6, 1e7, 1e8, 1e9,
};
static const unsigned unit[] = {
    p10[9], p10[6], p10[3], p10[0]
};

#define S(a) ((int)(sizeof(a)/sizeof(*a)))
#define RB_OK(b) ((b)>=BLACK && (b)<=WHITE)

static resistor_value_t ui2val(unsigned value)
{
    resistor_value_t res={0, OHMS};
    int i;

    for (i=0; i<S(unit); ++i) {
        if (!(value%unit[i])) {
            res.value=value/unit[i];
            res.unit=i;
            break;
        }
    }
    return res;
}

resistor_value_t color_code(resistor_band_t *colors)
{
    resistor_band_t c1=*colors, c2=*(colors+1), c3=*(colors+2);
    resistor_value_t res={RB_ERR, UN_ERR};

    if (RB_OK(c1) && RB_OK(c2) && RB_OK(c3))
        res=ui2val((c1*10+c2) * p10[c3]);
    return res;
}

/* See GNUmakefile below for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    resistor_band_t i[3];
    resistor_value_t res;

    for (; arg<ac-2; arg+=3) {
        *i=atoi(av[arg]);
        *(i+1)=atoi(av[arg+1]);
        *(i+2)=atoi(av[arg+2]);
        res=color_code(i);
        printf("color(%d, %d, %d)=%d, %d\n", i[0], i[1], i[2], res.value, res.unit);
    }
}
#endif
