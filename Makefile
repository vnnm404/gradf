CC=gcc
CFLAGS=-Iinclude

build/ad.o: src/ad_core.c
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

examples/basic_usage: examples/basic_usage.c build/ad.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf build