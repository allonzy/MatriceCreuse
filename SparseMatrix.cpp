#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "SparseMatrix.h"
using namespace std;
SparseMatrix::SparseMatrix(){

}
SparseMatrix::SparseMatrix(string path)
{
	SparseMatrix_setUse(0);
	SparseMatrix_loadMatrix(path);
}
SparseMatrix::SparseMatrix(SparseMatrix& m2){
	SparseMatrix_setUse(0);
	SparseMatrix_setHeight(0);
	SparseMatrix_setWidth(0);
	SparseMatrix_clear();

	for (int iRow = 0; iRow < SparseMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < SparseMatrix_getHeight(); iCol++)
        {
			SparseMatrix_setValue(iRow, iCol, m2.SparseMatrix_getValue(iRow, iCol));
        }
    }
}
SparseMatrix::SparseMatrix(int height,int width)
{
	SparseMatrix_setUse(0);
	SparseMatrix_setHeight(height);
	SparseMatrix_setWidth(width);
}
SparseMatrix::~SparseMatrix(){

}
int SparseMatrix::SparseMatrix_getMaxUse(){return sparseMatrix_maxUse;}
int SparseMatrix::SparseMatrix_getUse(){return sparseMatrix_use;}
int SparseMatrix::SparseMatrix_getHeight(){return sparseMatrix_height;}
int SparseMatrix::SparseMatrix_getWidth(){return sparseMatrix_width;}
int SparseMatrix::SparseMatrix_getValue(int x,int y){

	if(x > SparseMatrix_getHeight()  || y > SparseMatrix_getWidth()){
		cerr << "getValueError:value is out of range \n" ;
	}// remove when the code is complete
	if( ! sparseMatrix_m[make_pair(x,y)])return 0;
		else return sparseMatrix_m[make_pair(x,y)];
}

void SparseMatrix::SparseMatrix_setMaxUse(int maxUse){sparseMatrix_maxUse=maxUse;}
void SparseMatrix::SparseMatrix_setUse(int use){sparseMatrix_use=use;}
void SparseMatrix::SparseMatrix_setHeight(int height){sparseMatrix_height=height;}
void SparseMatrix::SparseMatrix_setWidth(int width){sparseMatrix_width=width;}
void SparseMatrix::SparseMatrix_setValue(int x,int y,int value){
	map<pair<int,int>,int>::iterator it = sparseMatrix_m.find(make_pair(x,y));
	if(value == 0)//
	{
		if(!sparseMatrix_m[make_pair(x,y)])
			sparseMatrix_m.erase(it);
		else return;
	}
	else if(x > SparseMatrix_getHeight()  || y > SparseMatrix_getWidth() ){	//value  out of range
		cerr << "setValueError: value is out of range \n";
	}
	else{	//we have a real value to insert
		sparseMatrix_m.insert(it, std::pair<pair<int,int>,int>(make_pair(x,y),value));//we re-set the slot
	}
}


void SparseMatrix::SparseMatrix_clear()
{
	sparseMatrix_m.clear();
}
void SparseMatrix::SparseMatrix_display(){
	for (int x = 0; x < SparseMatrix_getHeight(); x++){
		for (int y = 0; y < SparseMatrix_getWidth(); y++){
			cout << setw(5);
			cout << SparseMatrix_getValue(x, y) << " ";
		}
		cout << endl;
	}
}

bool SparseMatrix::SparseMatrix_loadMatrix(string matrixName)
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
    	SparseMatrix_clear();
    	int row,col;
			while(true )
			{
        		loadedMatrix >>row>>col >> value;
        		SparseMatrix_setValue(row, col, value);
        		if(loadedMatrix.eof())break;
        	}
        loadedMatrix.close();
    }
    else
    {
    	cerr << "loadMatrix error : impossible to open " << matrixName << ".full\n";
    	return false;
    }
    return true;
}

SparseMatrix& SparseMatrix::operator+=(SparseMatrix& m2)
{
	if (SparseMatrix_getHeight() != m2.SparseMatrix_getHeight() || SparseMatrix_getWidth() != m2.SparseMatrix_getWidth())
	{
		cerr << "operator += error : matrix uncompatible." << endl;
		return* this;
	}
	for (int iRow = 0; iRow < SparseMatrix_getHeight(); iRow++)
	{
		for (int iCol = 0; iCol < SparseMatrix_getWidth(); iCol++)
		{
			int v1 = SparseMatrix_getValue(iRow,iCol);
        	int v2 = m2.SparseMatrix_getValue(iRow,iCol);
        	SparseMatrix_setValue(iRow, iCol,v1+v2);
		}
	}
	return *this;
}

SparseMatrix& SparseMatrix::operator+(SparseMatrix& m2)
{
	if (SparseMatrix_getHeight() != m2.SparseMatrix_getHeight() || SparseMatrix_getWidth() != m2.SparseMatrix_getWidth())
	{
		cerr << "operator + error : matrix uncompatible." << endl;
		return *this;
	}
	
	SparseMatrix& tmp(*this);
	tmp += m2;

	return tmp;
}
int main(int argc, char const *argv[])
{
	SparseMatrix m(100,100);
	m.SparseMatrix_setValue(1,5,100);
	cout<<m.SparseMatrix_getValue(1,5);
	return 0;
}