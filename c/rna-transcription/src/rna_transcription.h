#ifndef RNA_TRANSCRIPTION_H
#define RNA_TRANSCRIPTION_H

char *to_rna(const char *dna);

/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
