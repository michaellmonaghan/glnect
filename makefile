
SDL_CFLAGS=$(shell sdl2-config --libs --cflags)

run: test
	./test

test: test.c
	gcc -lglut -lGL -lGLEW -lfreenect -o test test.c

sdltest: sdltest.c
	gcc $(SDL_CFLAGS) -lGL -o sdltest sdltest.c

runsdltest: sdltest
	./sdltest
a:
	echo CFLAGS
