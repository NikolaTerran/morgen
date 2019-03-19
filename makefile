all: main.o 3d.o matrix.o parser.o line.o util.o curve.o random.o trans.o engine.h
	gcc main.o 3d.o matrix.o line.o util.o random.o curve.o trans.o -lm
	gcc -o parser 3d.o matrix.o line.o util.o random.o parser.o curve.o trans.o -lm
	rm *.o

main.o: main.c engine.h
	gcc -c main.c

matrix.o: matrix.c engine.h
	gcc -c matrix.c

util.o: util.c engine.h
	gcc -c util.c

line.o: line.c engine.h
	gcc -c line.c
	
random.o: random.c engine.h
	gcc -c random.c

parser.o: parser.c engine.h
	gcc -c parser.c

curve.o: curve.c engine.h
	gcc -c curve.c
	
3d.o: 3d.c engine.h
	gcc -c 3d.c
	
trans.o: trans.c engine.h
	gcc -c trans.c
	
run:
	./a.out

clean:
	rm a.out parser *.ppm *.png
