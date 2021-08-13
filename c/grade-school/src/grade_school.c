#include "grade_school.h"
#include <string.h>
#include <stdio.h>

#define STD(i) roster.students[i]
#define NAME(i) roster.students[i].name
#define GRADE(i) roster.students[i].grade

static roster_t roster;

void clear_roster()
{
    roster.count=0;
}

/* testing program expects bool here, but I prefer to return students count,
 * it makes more sense for me.
 */
int add_student(char *s, uint8_t g)
{
    int c=roster.count;
    int i;

    if (c >= MAX_STUDENTS)
        return 0;
    // find correct place to insert name
    for (i=0; i<c && (GRADE(i)<g || (GRADE(i)==g && strcmp(s, NAME(i))>0)); ++i)
        ;
    for (int j=c-1; j>=i; --j)                    /* move rest to right */
        STD(j+1)=STD(j);
    NAME(i)=s;                                    /* insert new name */
    GRADE(i)=g;

    return ++roster.count;
}

/* to avoid this everytime, we could build up one roster per grade while
 * adding students, but really overkill here.
 */
roster_t get_grade(uint8_t g)
{
    static roster_t r;
    unsigned i, j=0;

    for (i=0; i<roster.count && GRADE(i)<=g; ++i) {
        if (GRADE(i)==g)
            r.students[j++]=STD(i);
    }
    r.count=j;

    return r;
}

roster_t get_roster()
{
    return roster;
}


/* See GNUmakefile below for explanation
 * https://github.com/braoult/exercism/blob/master/c/templates/GNUmakefile
 */
#ifdef UNIT_TEST
static void print_roster()
{
    unsigned i;
    printf("======== roster size: %lu\n", roster.count);
    for (i=0; i<roster.count; ++i)
        printf("roster(%02d): [%d]%s\n", i, GRADE(i), NAME(i));
    printf("\n");
}

int main(int ac, char **av)
{
    int arg=1;
    uint8_t i;

    for (; arg<ac-1; ++arg, ++arg) {
        i=atoi(av[arg]);
        add_student(av[arg+1], i);
    }
    print_roster();
}
#endif
