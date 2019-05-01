all: engine.h main.o point.o canvas.o line.o curve.o matrix.o trans.o 3d.o
	gcc 3d.o matrix.o point.o main.o canvas.o curve.o line.o trans.o -lm -lpthread
	./a.out

main.o: main.c engine.h
	gcc -c main.c

matrix.o: matrix.c engine.h
	gcc -c matrix.c

line.o: line.c engine.h
	gcc -c line.c

point.o: point.c engine.h
	gcc -c point.c
#parser.o: parser.c engine.h
#	gcc -c parser.c

curve.o: curve.c engine.h
	gcc -c curve.c

3d.o: 3d.c engine.h
	gcc -c 3d.c

trans.o: trans.c engine.h
	gcc -c trans.c

canvas.o: canvas.c engine.h
	gcc -c canvas.c

run:
	./a.out

clean:
	rm *.o *.out parser *.ppm *.png
