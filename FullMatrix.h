#ifndef _FULLMATRIX_
#define _FULLMATRIX_
#include <iostream>
#include <string>

using namespace std;

class FullMatrix
{
	private:
		int** fullMatrix_m;
		int fullMatrix_height;
		int fullMatrix_width;
	public:
		FullMatrix();
		FullMatrix(int height, int width);
		FullMatrix(string path);
		FullMatrix(FullMatrix& m2);
		~FullMatrix();

		int FullMatrix_getHeight();
		int FullMatrix_getWidth();
		int FullMatrix_getValue(int x, int y);

		void FullMatrix_setHeight(int value);
		void FullMatrix_setWidth(int value);
		void FullMatrix_setValue(int x, int y, int value);

		void FullMatrix_display();

		void FullMatrix_clear();
		void FullMatrix_setEmptyMatrix(int height, int width);

		bool FullMatrix_loadMatrix(string matrixName); 	// matrixName doesn't contain file extension nor the path to this file's directory. // Return false if the file doesn't exist.

		FullMatrix& operator+(FullMatrix& m2);
		FullMatrix& operator+=(FullMatrix& m2);
		// On aura besoin des fonctions d'addition, de soustraction, de multiplication et de divisions.
};
#endif