#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#define MAX_WORDS 20            // at most MAX_WORDS can be found in the test input string
#define MAX_WORD_LENGTH 50      // no individual word can exceed this length

// results structure
typedef struct word_count_word {
   char text[MAX_WORD_LENGTH + 1];      // allow for the string to be null-terminated
   int count;
} word_count_word_t;

#define EXCESSIVE_LENGTH_WORD     -1
#define EXCESSIVE_NUMBER_OF_WORDS -2
#define INVALID_WORD              -3

// count_words - routine to classify the unique words and their frequency in a sentence
// inputs:
//    sentence =  a null-terminated string containing that is analyzed
//
// outputs:
//    words = allocated structure to record the words found and their frequency
//    uniqueWords - number of words in the words structure
//           returns a negative number if an error.
//           words will contain the results up to that point.
int count_words(const char *sentence, word_count_word_t * words);

typedef struct {
    char *word;
    int len;
} word_t;

/* See GNUmakefile in following link for explanation
 * https://exercism.io/my/solutions/103b2f7d92db42309c1988030f5202c7
 */
#ifdef  TESTALL
#undef  TEST_IGNORE
#define TEST_IGNORE() {}
#endif

#endif
