# the original 'makefile' has a flaw:
# 1) it overrides CFLAGS
# 2) it does not pass extra "FLAGS" to $(CC) that could come from environment
#
# It means we need to edit 'makefile' for different builds (DEBUG, etc...),
# which is not practical at all.
#
# I hope this will be use-able for next exercises...

#include gmsl
include makefile

manual=-DUNIT_TEST
debug=$(manual) -DDEBUG

.PHONY: manual debug

manual debug: src/*.c src/*.h
	$(CC) $($@) src/*.c -o $@.out
#debug: src/*.c src/*.h
#	$(CC) $(DEBUG) src/*.c -o $@.out
