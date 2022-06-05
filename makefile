all: main.o
	gcc main.o -g -o main.exe -lm
main.o: main.c stb_image.h
	gcc -c -g main.c
clean:
	rm main.o main.exe
