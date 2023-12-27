all: run

cobs_test: cobs_test.c cobs.c
	gcc -Wall -mwin32 -o $@ $^

run: cobs_test
	./$^

clean:
	rm -f cobs_test.exe
