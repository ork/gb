EXEC     = gb
CC       = clang

CFLAGS   = -std=c99 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS  += -Wno-gnu-binary-literal

SRC      = $(wildcard *.c)
OBJ      = $(SRC:.c=.o)

all: $(EXEC)

${EXEC}: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
