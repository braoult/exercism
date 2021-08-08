#ifndef RESISTOR_COLOR_DUO_H
#define RESISTOR_COLOR_DUO_H

typedef enum {
    BLACK=0,
    BROWN,
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    BLUE,
    VIOLET,
    GREY,
    WHITE,
    ERROR=-1,
} resistor_band_t;

extern resistor_band_t color_code(resistor_band_t *);

#ifdef TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
