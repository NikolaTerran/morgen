all: main.o array.o engine.h point.o matrix.o line.o curve.o
	nvcc -arch=sm_35 -rdc=true -o output matrix.o point.o main.o array.o line.o curve.o -lm -lcudadevrt

main.o: main.cu engine.h
	nvcc -c main.cu

array.o: array.cu engine.h
	nvcc -c array.cu

matrix.o: matrix.cu engine.h
	nvcc -c matrix.cu

point.o: point.cu engine.h
	nvcc -c point.cu

line.o: line.cu engine.h
	nvcc -arch=sm_35 -rdc=true -c line.cu -lcudadevrt

curve.o: curve.cu engine.h
	nvcc -c curve.cu

clean:
	rm *.o *.ppm output a.out *.png

run:
	./output