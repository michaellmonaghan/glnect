run: test
	./test

test: test.c
	gcc -lglut -lGL -lGLEW -lfreenect -o test test.c
