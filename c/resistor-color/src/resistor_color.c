#include "resistor_color.h"

/* V1: initial version
 * V2: add error code in enum
 */
static resistor_band_t mapping[]={
    BLACK,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE,
    ERROR
};

resistor_band_t color_code(resistor_band_t color)
{
    return color>=BLACK && color<=WHITE? color: ERROR;
}

resistor_band_t *colors()
{
    return mapping;
}

#ifdef UNIT_TEST
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int arg=1, n;

    for (; arg<ac; ++arg) {
        n=atoi(av[arg]);
        printf("color(%d)=%d\n", n, color_code(n));
    }

}
#endif
