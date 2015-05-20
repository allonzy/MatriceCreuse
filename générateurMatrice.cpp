#include "Matrix.h"
#include "FullMatrix.h"
#include "SparseMatrix.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
using namespace std;

int main(int argc, char const *argv[])
{
	srand (time(NULL));
	SparseMatrix a(1000, 1000);
	a.SparseMatrix_random(1);
	SparseMatrix b(1000, 1000);
	b.SparseMatrix_random(1);
	a = a*b ;
	cout << a.SparseMatrix_getUse()<<endl;
	a.SparseMatrix_saveMatrix("yolo");
	return 0;
}