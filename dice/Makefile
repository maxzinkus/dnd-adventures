CC=clang
CFLAGS=-Wall -Werror -Wpedantic -std=c17 -O3 -flto
TARGETS=dice

.PHONY: all test clean

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test: dice_test

dice_test: dice.c
	$(CC) $(CFLAGS) -DTEST_MODE $< -o $@

clean:
		$(RM) $(TARGETS) dice_test
