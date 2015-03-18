#include <iostream>
#include "FullMatrix.h"

using namespace std;

FullMatrix::FullMatrix(){}

FullMatrix::FullMatrix(int height, int width){
	FullMatrix_setHeight(height);
	FullMatrix_setWidth(width);
}

FullMatrix::FullMatrix(string path){
	ifstream dataMatrix(path);
	if (!dataMatrix.isOpen()){
		cerr << "FullMatrix error : invalid path.\n";
		return;
	}
	else{
		
	}

}

FullMatrix::~FullMatrix(){
	
}

int FullMatrix::FullMatrix_getHeight(){return fullMatrix_height;}

int FullMatrix::FullMatrix_getWidth(){return fullMatrix_width;}

int FullMatrix::FullMatrix_getValue(int x, int y){
	if (x > FullMatrix_getHeight() || y > FullMatrix_getWidth()){
		cerr << "getValue error : value is out of range.\n";
		return 0;
	}
	else return fullMatrix_m[x][y];
}

void FullMatrix::FullMatrix_setHeight(int value){fullMatrix_height = value;}

void FullMatrix::FullMatrix_setWidth(int value){fullMatrix_width = value;}

void FullMatrix::FullMatrix_setValue(int x, int y, int value){
	if (x > FullMatrix_getHeight() || y > FullMatrix_getWidth()){
		cerr << "setValue error : value is out of range.\n";
		return;
	}
	else {fullMatrix_m[x][y] = value;}

void FullMatrix::FullMatrix_display(){
	for (int x = 0; x < FullMatrix_getHeight(); x++){
		for (int y = 0; y < FullMatrix_getWidth(); y++){
			cout << FullMatrix_getValue(x, y) << " ";
		}
		cout << endl;
	}
}