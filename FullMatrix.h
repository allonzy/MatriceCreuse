#ifndef _FULLMATRIX_
#define _FULLMATRIX_
#include <iostream>
#include <map>

using namespace std;

class FullMatrix
{
	private:
		int** fullMatrix_m;
		int fullMatrix_height;
		int fullMatrix_width;
	public:
		FullMatrix();
		FullMatrix(int height, int width)
		FullMatrix(string path);
		~FullMatrix();

		int FullMatrix_getHeight();
		int FullMatrix_getWidth();
		int FullMatrix_getValue(int x, int y);

		void FullMatrix_setHeight(int value);
		void FullMatrix_setWidth(int value);
		void FullMatrix_setValue(int x, int y, int value);

		void FullMatrix_display();
};
#endif