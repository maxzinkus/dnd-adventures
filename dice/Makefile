CC=clang
CFLAGS=-Wall -Werror -Wpedantic -std=c17 -O3 -flto
TARGETS=dice

.PHONY: all clean

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

test:
	$(CC) $(CFLAGS) -DTEST_MODE dice.c -o dice

clean:
		$(RM) $(TARGETS)
