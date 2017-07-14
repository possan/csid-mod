all: test testlight

clean:
	rm -f test.o testlight.o libcsid.o libcsidlight.o csid csidl

libcsid.o: libcsid.c
	gcc -c libcsid.c -o libcsid.o -lm

libcsidlight.o: libcsidlight.c
	gcc -c libcsidlight.c -o libcsidlight.o -lm

test.o: test.c
	gcc -c test.c -o test.o -lm `sdl-config --cflags --libs`

testlight.o: testlight.c
	gcc -c testlight.c -o testlight.o -lm `sdl-config --cflags --libs`

test: test.o libcsid.o
	gcc test.o libcsid.o -o csid `sdl-config --cflags --libs` -lm

testlight: testlight.o libcsidlight.o
	gcc testlight.o libcsidlight.o -o csidl `sdl-config --cflags --libs` -lm

install:
	cp csid /usr/local/bin
	cp csidl /usr/local/bin
