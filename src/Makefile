EXEC     = gb
CC       = clang

CFLAGS   = -std=c99 -O3 -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS  += -Wno-gnu-binary-literal -Wno-gnu-case-range

SRC      = $(wildcard *.c memory/*.c)
OBJ      = $(SRC:.c=.o)

all: $(EXEC)

${EXEC}: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o memory/*.o

mrproper: clean
	@rm -rf $(EXEC)
