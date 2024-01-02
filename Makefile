CC=gcc
# CFLAGS=-Iinclude -fsanitize=address
CFLAGS=-Iinclude

build/ad_core.o: src/ad_core.c include/ad.h
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/ad_operators.o: src/ad_operators.c include/ad.h
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/ad_stack.o: src/ad_stack.c include/ad.h
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/ad_gradf.o: src/ad_gradf.c include/ad.h
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

examples/basic_usage: examples/basic_usage.c build/ad_core.o build/ad_operators.o build/ad_stack.o build/ad_gradf.o
	mkdir -p build
	$(CC) -o build/basic_usage $^ $(CFLAGS)

examples/basic_gradf: examples/basic_gradf.c build/ad_core.o build/ad_operators.o build/ad_stack.o build/ad_gradf.o
	mkdir -p build
	$(CC) -o build/basic_gradf $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf build