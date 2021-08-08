#ifndef RESISTOR_COLOR_TRIO_H
#define RESISTOR_COLOR_TRIO_H

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
    RB_ERR=-1,
} resistor_band_t;

/* max=white-white-white =99 000 000 000=99 Giga
 * warning: overflow before that (untested) !
 */
typedef enum {
    GIGAOHMS=0,
    MEGAOHMS,
    KILOOHMS,
    OHMS,
    UN_ERR=-1
} unit_t;

typedef struct {
    resistor_band_t value;
    unit_t unit;
} resistor_value_t;

extern resistor_value_t color_code(resistor_band_t *);

/* Note: For explanation on section below, see 'GNUfilename' included in
 * link below :
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
