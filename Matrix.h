//!
//!	\file		Matrix.h
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier de déclaration de la classe Matrix. Définit les matrices.
//!

// --------------------------------

#include <string>

class Matrix
{

	private:
		FullMatrix* fullMatrix;
		SparseMatrix* sparseMatrix;
		const static int conversionCap = 70;

	public:
		Matrix();
		Matrix(string filePath);
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

		int Matrix_getValue();
		void Matrix_setValue(int x, int y, int value);

		int Matrix_getHeight();
		void Matrix_setHeight(int height);

		int Matrix_getWidth();
		void Matrix_setWidth(int width);

		void Matrix_conversion();
		void Matrix_conversionForOperations();
		void Matrix_sparseToFull();
		void Matrix_fullToSparse();
};