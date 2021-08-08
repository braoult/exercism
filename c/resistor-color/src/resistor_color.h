#ifndef RESISTOR_COLOR_H
#define RESISTOR_COLOR_H

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

extern resistor_band_t color_code(resistor_band_t);
extern resistor_band_t *colors();

#ifdef TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
