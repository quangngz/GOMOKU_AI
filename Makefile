CC = gcc
CFLAGS = -Wall -Wextra
SHELL = /bin/bash

FILES := $(wildcard tests/test[0-9]*.txt)

# Default target
all: final

# Build the main program
final: functions.o main.o
	@$(CC) $(CFLAGS) -o final functions.o main.o

functions.o: functions.c
	@$(CC) $(CFLAGS) -c functions.c

main.o: main.c
	@$(CC) $(CFLAGS) -c main.c

# Build the test runner
test: test.c functions.c
	@$(CC) $(CFLAGS) -o test test.c functions.c

# Run automated tests
run-tests: test
	@for f in $(FILES); do \
		case $$f in *-output.txt) continue ;; esac; \
		outf=$${f%.txt}-output.txt; \
		echo "Testing $$f ..."; \
		./test $$f > temp_output.txt; \
		if diff -q temp_output.txt $$outf > /dev/null; then \
			echo "PASS: $$f"; \
		else \
			echo "FAIL: $$f"; \
			diff temp_output.txt $$outf; \
		fi; \
		echo "-----------------------------"; \
	done

# Clean build artifacts
clean: 
	@rm -f final test *.o temp_output.txt
