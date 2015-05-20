Calculette: main.o SparseMatrix.o FullMatrix.o
	g++ -o Calculette main.cpp SparseMatrix.o FullMatrix.o


SparseMatrix.o: SparseMatrix.cpp SparseMatrix.h
	g++ -o SparseMatrix.o -c SparseMatrix.cpp;

FullMatrix.o: FullMatrix.cpp FullMatrix.h
	g++ -o FullMatrix.o -c FullMatrix.cpp;

clean:
	rm *.o

run:
	./Calculette