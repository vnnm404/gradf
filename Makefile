CC=gcc
CFLAGS=-Iinclude

build/ad_core.o: src/ad_core.c include/ad.h
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/ad_operators.o: src/ad_operators.c include/ad.h
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

examples/basic_usage: examples/basic_usage.c build/ad_core.o build/ad_operators.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf build examples/build_usage