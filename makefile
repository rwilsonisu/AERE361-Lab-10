CC = gcc
CCFLAGS = -Wall -Werror -Wextra -std=c99
LDFLAGS = -lm

all: gauss-jordan gauss-seidel

gauss-jordan: gauss_jordan.c
	$(CC) gauss_jordan.c -o gauss-jordan $(CCFLAGS) $(LDFLAGS)

gauss-seidel: gauss_seidel.c
	$(CC) gauss_seidel.c -o gauss-seidel $(CCFLAGS) $(LDFLAGS)

clean:
	rm -f gauss-jordan gauss-seidel answer.csv
