all: build/csid build/csidl

clean:
	rm -f build/*

build/libcsidfull.o: src/libcsidfull.c include/libcsid.h
	gcc -c src/libcsidfull.c -o build/libcsidfull.o -lm -Iinclude

build/libcsidlight.o: src/libcsidlight.c include/libcsid.h
	gcc -c src/libcsidlight.c -o build/libcsidlight.o -lm -Iinclude

build/csid: examples/csid.c include/libcsid.h build/libcsidfull.o
	gcc examples/csid.c build/libcsidfull.o -o build/csid -lm -Iinclude `sdl-config --cflags --libs`

build/csidl: examples/csid.c include/libcsid.h build/libcsidlight.o
	gcc examples/csid.c build/libcsidlight.o -o build/csidl -lm -Iinclude `sdl-config --cflags --libs`

install: build/csid build/csidl
	cp build/csid /usr/local/bin
	cp build/csidl /usr/local/bin
