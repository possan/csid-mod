
all: csid-light.c # playlist
	gcc csid-light.c -s -o csidl `sdl-config --cflags --libs` -lm # -lSDL

probe: csidl playlist.txt
	./csidl playlist.txt - - 125

install: 
	-cp csidl /usr/local/bin
	-cp csida /usr/local/bin

playlist:
	touch playlist.txt
	ls music/*.sid > playlist.txt

clean:
	rm csidl # playlist.txt

uninstall:
	rm /usr/local/bin/csidl /usr/local/bin/csida
