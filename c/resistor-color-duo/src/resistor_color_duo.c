#include "resistor_color_duo.h"
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

resistor_band_t color_code(resistor_band_t colors[static 2])
{
    resistor_band_t c1=*colors, c2=*(colors+1);
    return c1>=BLACK && c1<=WHITE && c2>=BLACK && c2<=WHITE? c1*10+c2: ERROR;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    resistor_band_t i[2];

    for (; arg<ac-1; ++arg, ++arg) {
        *i=atoi(av[arg]);
        *(i+1)=atoi(av[arg+1]);
        printf("color(%d, %d)=%d\n", *i, *(i+1), color_code(i));
    }
}
#endif
