//!
//!	\file		FullMatrix.h
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier de déclaration de la classe FullMatrix. Définit les matrices pleines et leurs possibilités d'utilisation.
//!

// --------------------------------

#ifndef FULLMATRIX_H
#define FULLMATRIX_H

#include <iostream>
#include <string>

// --------------------------------

using namespace std;

// --------------------------------

//!
//! \class 		FullMatrix
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//! \brief      Cette classe définit ce qu'est une matrice pleine, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
//!

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

		bool FullMatrix_loadMatrix(string matrixName);

		FullMatrix& operator+(FullMatrix& m2);
		FullMatrix& operator+=(FullMatrix& m2);
		FullMatrix& operator-(FullMatrix& m2);
		FullMatrix& operator-=(FullMatrix& m2);
		
};

#endif