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
# 1) copy it into exercise directory
# 2) add ex.h to exercise include file
# 3) add ex.c to exercise source code, and create a suitable main function
# 4) use make with one of the following targets :
#   all: compile and run all predefined tests.
#   nowarn: compile with no -Wall and -Wextra, and run all predefined tests
#   debug: compile with -DDEBUG and run all predefined tests
#   mem: perform memcheck with all tests enabled
#   unit: build standalone (unit) binary
#   unitnowarn: build standalone binary with -Wall and -Wextra disabled
#   unitdebug: build standalone binary with -DDEBUG
#
# Original 'makefile' targets can be used (test, memcheck, clean, ...)

.PHONY: default all nowarn debug mem unitnowarn unitdebug unit

default: all

include makefile

all: CFLAGS+=-DTESTALL
all: clean test

nowarn: CFLAGS:=$(filter-out -Wextra -Wall,$(CFLAGS))
nowarn: all

debug: CFLAGS+=-DDEBUG
debug: all

mem: CFLAGS+=-DTESTALL
mem: clean memcheck

unitnowarn: CFLAGS:=$(filter-out -Wextra -Wall,$(CFLAGS))
unitnowarn: clean unit

unitdebug: CFLAGS+=-DDEBUG
unitdebug: clean unit

unit: CFLAGS+=-DUNIT_TEST
unit: src/*.c src/*.h
	$(CC) $(CFLAGS) src/*.c -o tests.out  $(LIBS)
