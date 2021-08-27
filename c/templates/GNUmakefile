# The original 'makefile' has a flaw:
# 1) it overrides CFLAGS
# 2) it does not pass extra "FLAGS" to $(CC) that could come from environment
#
# It means :
# - we need to edit 'makefile' for different builds (DEBUG, etc...), which is
#   not practical at all.
# - Also, it does not allow to run all tests without editing the test source
#   code.
#
# To use this makefile (GNU make only):
#   "make": build with all predefined tests (without editing test source code)
#   "make debugall": build with all predefined tests and debug code
#   "make mem": perform memcheck with all tests enabled
#   "make unit": build standalone (unit) test
#   "make debug": build standalone test with debugging code
#
# Original 'makefile' targets can be used (test, memcheck, clean, ...)

.PHONY: default all mem unit debug std debugtest

default: all

# default is to build with all predefined tests
BUILD := teststall

include makefile

all: CFLAGS+=-DTESTALL
all: clean test

nowarn: CFLAGS:=$(filter-out -Wextra -Wall,$(CFLAGS))
nowarn: clean test

debugall: CFLAGS+=-DDEBUG
debugall: all

debugtest: CFLAGS+=-DDEBUG
debugtest: test

mem: CFLAGS+=-DTESTALL
mem: clean memcheck

unit: CFLAGS+=-DUNIT_TEST
unit: clean std

debug: CFLAGS+=-DUNIT_TEST -DDEBUG
debug: clean std

debugtest: CFLAGS+=-DDEBUG
debugtest: test

std: src/*.c src/*.h
	$(CC) $(CFLAGS) src/*.c -o tests.out  $(LIBS)
