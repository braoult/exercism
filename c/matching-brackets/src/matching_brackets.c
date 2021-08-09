#include "matching_brackets.h"

/* See GNUmakefile below explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#if defined UNIT_TEST || defined DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#define MAX_STACK 1024

static char STACK[MAX_STACK];
static int stack;
static char match[] = {
    [')'] = '(',
    [']'] = '[',
    ['}'] = '{'
};

static inline int push(char c)
{
    if (stack<MAX_STACK)
        return (STACK[stack++]=c);
    return 0;
}
static inline int pop()
{
    if (stack>0)
        return STACK[--stack];
    return 0;
}

bool is_paired(const char *s)
{
    stack=0;

    for (; *s; s++) {
        switch (*s) {
            case '[': case '(': case '{':
                push(*s);
                break;
            case ']': case ')': case '}':
                if (pop() != match[(int)*s])
                    return false;
                break;
        }
    }
    return stack==0;
}

#ifdef UNIT_TEST
int main(int ac, char **av)
{
    int arg=1;

    for (; arg<ac; ++arg) {
        printf("paired(%s)=%d\n", av[arg], is_paired(av[arg]));
    }
}
#endif
