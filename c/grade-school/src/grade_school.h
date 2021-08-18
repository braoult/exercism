#ifndef GRADE_SCHOOL_H
#define GRADE_SCHOOL_H

#include <stddef.h>
#include <stdint.h>

#define MAX_STUDENTS    20

typedef struct student_s {
    uint8_t grade;
    const char *name;
} student_t;

typedef struct {
    size_t count;
    student_t students[MAX_STUDENTS];
} roster_t;

void clear_roster(void);
int add_student(const char *student, const uint8_t grade);
roster_t get_grade(const uint8_t grade);
roster_t get_roster(void);

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
