#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
using namespace std;
class SparseMatrix
{
private:
	int sparseMatrix_maxUse;//stock the use in % exemple : [0,0,0,1] is 25
	int sparseMatrix_use;
	map<pair<int,int>,int> sparseMatrix_m;
	int sparseMatrix_height;
	int sparseMatrix_width;
public:
	SparseMatrix();
	SparseMatrix(int height,int width);
	SparseMatrix(SparseMatrix& m2);
	SparseMatrix(string path);
	~SparseMatrix();

	int SparseMatrix_getHeight();
	int SparseMatrix_getWidth();
	int SparseMatrix_getValue(int x,int y);
	int SparseMatrix_getMaxUse();
	int SparseMatrix_getUse();
	void SparseMatrix_setMaxUse(int maxUse);
	void SparseMatrix_setUse(int use);
	void SparseMatrix_setHeight(int height);
	void SparseMatrix_setWidth(int width);
	void SparseMatrix_setValue(int x,int y,int value);
	void SparseMatrix_clear();
	void SparseMatrix_display();
	bool SparseMatrix_loadMatrix(string matrixName);
	SparseMatrix& operator+=(SparseMatrix& m2);
	SparseMatrix& operator+(SparseMatrix& m2);
};
