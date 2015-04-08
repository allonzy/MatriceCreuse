#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "FullMatrix.h"

using namespace std;

FullMatrix::FullMatrix(){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
}

FullMatrix::FullMatrix(int height, int width){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
	FullMatrix_setEmptyMatrix(height, width);
}

FullMatrix::FullMatrix(string name){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);	
	FullMatrix_loadMatrix(name);
}

FullMatrix::FullMatrix(FullMatrix& m2){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
	FullMatrix_setEmptyMatrix(m2.FullMatrix_getHeight(),m2.FullMatrix_getWidth());

	for (int iRow = 0; iRow < FullMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < FullMatrix_getHeight(); iCol++)
        {
			FullMatrix_setValue(iRow, iCol, m2.FullMatrix_getValue(iRow, iCol));
        }
    }
}

FullMatrix::~FullMatrix(){
	FullMatrix_clear();
}

int FullMatrix::FullMatrix_getHeight(){return fullMatrix_height;}

int FullMatrix::FullMatrix_getWidth(){return fullMatrix_width;}

int FullMatrix::FullMatrix_getValue(int x, int y){
	if (x > FullMatrix_getHeight() || y > FullMatrix_getWidth() || x < 0 || y < 0){
		cerr << "getValue error : value is out of range.\n";
		return 0;
	}
	else return fullMatrix_m[x][y];
}

void FullMatrix::FullMatrix_setHeight(int value){fullMatrix_height = value;}

void FullMatrix::FullMatrix_setWidth(int value){fullMatrix_width = value;}

void FullMatrix::FullMatrix_setValue(int x, int y, int value){
	if (x > FullMatrix_getHeight() || y > FullMatrix_getWidth() || x < 0 || y < 0){
		cerr << "setValue error : position is out of range.\n";
		return;
	}
	else {fullMatrix_m[x][y] = value;}
}

void FullMatrix::FullMatrix_display(){
	for (int x = 0; x < FullMatrix_getHeight(); x++){
		for (int y = 0; y < FullMatrix_getWidth(); y++){
			cout << setw(5);
			cout << FullMatrix_getValue(x, y) << " ";
		}
		cout << endl;
	}
}

void FullMatrix::FullMatrix_clear()
{
	for (int i = 0; i < FullMatrix_getHeight(); i++)
	{
		delete [] fullMatrix_m[i];
	}
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
}

void FullMatrix::FullMatrix_setEmptyMatrix(int height, int width)
{
	FullMatrix_clear();
	FullMatrix_setHeight(height);
	FullMatrix_setWidth(width);

	fullMatrix_m = new int*[height];

	for (int i = 0; i < height; i++)
	{
		fullMatrix_m[i] = new int[width];
	}
}

bool FullMatrix::FullMatrix_loadMatrix(string matrixName)
{
	int rowSize;														// Number of rows.
	int colSize;														// Number of cols.
	int value;															// Readed value to assign to the matrix.

	string pathToMatrix = "Matrix/" + matrixName + ".full"; 
	ifstream loadedMatrix(pathToMatrix.c_str(), ios::in);
	if(loadedMatrix)
    {
    	loadedMatrix >> rowSize;
    	loadedMatrix >> colSize;
    	FullMatrix_setEmptyMatrix(rowSize,colSize);

		for (int iRow = 0; iRow < rowSize; iRow++)
        {
        	for (int iCol = 0; iCol < colSize; iCol++)
        	{
        		loadedMatrix >> value;
        		FullMatrix_setValue(iRow, iCol, value);
        	}
        }
        loadedMatrix.close();
    }
    else
    {
    	cerr << "loadMatrix error : impossible to open " << matrixName << ".full\n";
    	return false;
    }
}

FullMatrix& FullMatrix::operator+(FullMatrix& m2)
{
	if (FullMatrix_getHeight() != m2.FullMatrix_getHeight() || FullMatrix_getWidth() != m2.FullMatrix_getWidth())
	{
		cerr << "operator + error : matrix uncompatible." << endl;
		return *this;
	}
	
	FullMatrix& tmp(*this);
	tmp += m2;

	return tmp;
}

FullMatrix& FullMatrix::operator+=(FullMatrix& m2)
{
	if (FullMatrix_getHeight() != m2.FullMatrix_getHeight() || FullMatrix_getWidth() != m2.FullMatrix_getWidth())
	{
		cerr << "operator += error : matrix uncompatible." << endl;
		return* this;
	}
	for (int iRow = 0; iRow < FullMatrix_getHeight(); iRow++)
	{
		for (int iCol = 0; iCol < FullMatrix_getWidth(); iCol++)
		{
			int v1 = FullMatrix_getValue(iRow,iCol);
        	int v2 = m2.FullMatrix_getValue(iRow,iCol);
        	FullMatrix_setValue(iRow, iCol,v1+v2);
		}
	}
	return *this;
}