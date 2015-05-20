//!
//!	\file		SparseMatrix.h
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier de déclaration de la classe SparseMatrix. Définit les matrices creuses et leurs possibilités d'utilisation.
//!

// --------------------------------

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <time.h>

// --------------------------------

using namespace std;

// --------------------------------

//!
//! \class 		SparseMatrix
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//! \brief      Cette classe définit ce qu'est une matrice creuse, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
//!

class SparseMatrix
{
	private:
		int sparseMatrix_use;
		map<pair<int,int>,int> sparseMatrix_m;
		int sparseMatrix_height;
		int sparseMatrix_width;

		void SparseMatrix_setUse(int use);
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

		void SparseMatrix_setUse();
		void SparseMatrix_setHeight(int height);
		void SparseMatrix_setWidth(int width);
		void SparseMatrix_setValue(int x,int y,int value);

		void SparseMatrix_clear();
		void SparseMatrix_display();
		bool SparseMatrix_loadMatrix(string matrixName);
		bool SparseMatrix_saveMatrix(string matrixName);
		void operator+=(SparseMatrix& m2);
		SparseMatrix& operator+(SparseMatrix& m2);
		SparseMatrix& operator*(SparseMatrix& m2);
		SparseMatrix& operator=(SparseMatrix& m2);

		void SparseMatrix_random(float use);
		void SparseMatrix_random();



};

// --------------------------------

#endif
