//!
//!	\file		Matrix.h
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier de déclaration de la classe Matrix. Définit les matrices.
//!

// --------------------------------

#include <string>
#include "FullMatrix.h"
#include "SparseMatrix.h"

class Matrix
{

	private:
		FullMatrix* matrix_fullMatrix;
		SparseMatrix* matrix_sparseMatrix;
		const static int matrix_conversionCap = 70;

	public:
		Matrix();
		Matrix(string filePath, bool isSparse);
		Matrix(int height, int width);
		Matrix(Matrix& m2);
		~Matrix();

		Matrix& operator+(Matrix& m2);
		Matrix& operator+=(Matrix& m2);
		Matrix& operator-(Matrix& m2);
		Matrix& operator-=(Matrix& m2);
		//Matrix operator*(Matrix m2);
		//Matrix operator*=(Matrix m2);
		static int Matrix_getConversionCap();

		int Matrix_getValue(int x, int y);
		void Matrix_setValue(int x, int y, int value);

		int Matrix_getHeight();
		void Matrix_setHeight(int height);

		int Matrix_getWidth();
		void Matrix_setWidth(int width);

		FullMatrix* Matrix_getFullMatrix();
		void Matrix_setFullMatrix(FullMatrix* m2);

		SparseMatrix* Matrix_getSparseMatrix();
		void Matrix_setSparseMatrix(SparseMatrix* m2);

		void Matrix_conversion();
		void Matrix_sparseToFull();
		void Matrix_fullToSparse();
		void Matrix_display();
};