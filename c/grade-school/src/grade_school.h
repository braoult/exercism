#ifndef GRADE_SCHOOL_H
#define GRADE_SCHOOL_H

#include <stddef.h>
#include <stdint.h>
//#include <stdbool.h>

#define MAX_NAME_LENGTH 20
#define MAX_STUDENTS    20

typedef struct student_s {
    uint8_t grade;
    char *name;
} student_t;

typedef struct {
    size_t count;
    student_t students[MAX_STUDENTS];
} roster_t;

void clear_roster();
int add_student(char *, uint8_t);
roster_t get_grade(uint8_t);
roster_t get_roster();

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
