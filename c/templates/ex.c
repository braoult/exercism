/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;
    resistor_band_t i[2];

    for (; arg<ac-1; ++arg, ++arg) {
        *i=atoi(av[arg]);
        *(i+1)=atoi(av[arg+1]);
        printf("color(%d, %d)=%d\n", i[0], i[1], color_code(i));
    }
}
#endif
