#ifndef _SPARSEMATRIX_
#define _SPARSEMATRIX_
#include <iostream>
#include <map>
using namespace std;
class SparseMatrix
{
private:
	int sparseMatrix_maxUse;//stock the use in % exemple : [0,0,0,1] is 25
	map <pair<int,int>,int> sparseMatrix_m;
	int sparseMatrix_height;
	int sparseMatrix_width;
public:
	SparseMatrix();
	~SparseMatrix();
	int sparseMatrix_getHeight();
	int sparseMatrix_getWidth();
	int SparseMatrix_getValue(int x,int y);
	int sparseMatrix_getMaxUse();

	void sparseMatrix_setMaxUse(int maxUse);
	void SparseMatrix_setHeight(int height);
	void SparseMatrix_setWidth(int width);
	void SparseMatrix_setValue(int x,int y,int value);
};
#endif
