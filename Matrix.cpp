//!
//!	\file		Matrix.cpp
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier d'implémentation de la classe Matrix. Définit les matrices ainsi que les fonctions qui combinent les deux types de matrice.
//! \details    Cette classe définit ce qu'est une matrice, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
//!

// --------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Matrix.h"

// --------------------------------

using namespace std;

// --------------------------------


//!
//! \brief      Constructeur de matrice pleine vide.
//! \details    Ce constructeur initialise une matrice pleine vide, de taille 0 par 0.
//!

Matrix::Matrix(){
	Matrix_setFullMatrix(new FullMatrix());
	Matrix_setSparseMatrix(NULL);
}

Matrix::Matrix(string filePath, bool isSparse){
	if(!isSparse){
		Matrix_setFullMatrix(new FullMatrix(filePath));
		Matrix_setSparseMatrix(NULL);
	}else{
		Matrix_setSparseMatrix(new SparseMatrix(filePath));
		Matrix_setFullMatrix(NULL);
	}
}

Matrix::Matrix(int height, int width){
	Matrix_setFullMatrix(new FullMatrix(height, width));
	Matrix_setSparseMatrix(NULL);
}

Matrix::Matrix(Matrix& m2){
	if(m2.Matrix_getFullMatrix() != NULL)
		Matrix_setFullMatrix(new FullMatrix(*m2.Matrix_getFullMatrix()));
	else
		Matrix_setFullMatrix(NULL);

	if(m2.Matrix_getSparseMatrix() != NULL)
		Matrix_setSparseMatrix(new SparseMatrix(*m2.Matrix_getSparseMatrix()));
	else
		Matrix_setSparseMatrix(NULL);
}

Matrix::~Matrix(){
	delete Matrix_getFullMatrix();
	delete Matrix_getSparseMatrix();
}

void Matrix::Matrix_display(){
	if(Matrix_getFullMatrix() != NULL)
		Matrix_getFullMatrix()->FullMatrix_display();
	if(Matrix_getSparseMatrix() != NULL)
		Matrix_getSparseMatrix()->SparseMatrix_display();
}

void Matrix::Matrix_conversion(){
	if(Matrix_getFullMatrix() != NULL){

		int nbElem = Matrix_getFullMatrix()->FullMatrix_getHeight() * Matrix_getFullMatrix()->FullMatrix_getWidth();
		int nbZero = 0;
		for (int iRow = 0; iRow < Matrix_getFullMatrix()->FullMatrix_getWidth(); iRow++)
	    {
	        for (int iCol = 0; iCol < Matrix_getFullMatrix()->FullMatrix_getHeight(); iCol++)
	        {
	        	if(Matrix_getFullMatrix()->FullMatrix_getValue(iRow, iCol) == 0)
	        		nbZero++;
	        }
	    }
	    float ratio = 1-(nbZero / nbElem);
	    if(ratio < Matrix::Matrix_getConversionCap()){
	    	Matrix_fullToSparse();
	    	delete Matrix_getFullMatrix();
	    	matrix_fullMatrix = NULL;
	    }

	}
	else if(Matrix_getSparseMatrix() != NULL){

		if(Matrix_getSparseMatrix()->SparseMatrix_getUse() > Matrix::Matrix_getConversionCap()){
			Matrix_sparseToFull();
			delete Matrix_getSparseMatrix();
			matrix_sparseMatrix = NULL;
		}

	}
}

void Matrix::Matrix_sparseToFull(){
	Matrix_setFullMatrix(new FullMatrix(Matrix_getSparseMatrix()->SparseMatrix_getHeight(), Matrix_getSparseMatrix()->SparseMatrix_getWidth()));
	for (int iRow = 0; iRow < Matrix_getFullMatrix()->FullMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < Matrix_getFullMatrix()->FullMatrix_getHeight(); iCol++)
        {
        	Matrix_getFullMatrix()->FullMatrix_setValue(iRow, iCol, Matrix_getSparseMatrix()->SparseMatrix_getValue(iRow, iCol));
        }
    }
}

void Matrix::Matrix_fullToSparse(){
	Matrix_setSparseMatrix(new SparseMatrix(Matrix_getFullMatrix()->FullMatrix_getHeight(), Matrix_getFullMatrix()->FullMatrix_getWidth()));
	for (int iRow = 0; iRow < Matrix_getSparseMatrix()->SparseMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < Matrix_getSparseMatrix()->SparseMatrix_getHeight(); iCol++)
        {
        	Matrix_getSparseMatrix()->SparseMatrix_setValue(iRow, iCol, Matrix_getFullMatrix()->FullMatrix_getValue(iRow, iCol));
        }
    }
}

Matrix& Matrix::operator=(Matrix& m2)
{
	Matrix& m(m2);
	return m;
}

Matrix& Matrix::operator+(Matrix& m2){
	Matrix& tmp(*this);
	tmp += m2;

	return tmp;
}

void Matrix::operator+=(Matrix& m2){
	if(Matrix_getFullMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){
		*Matrix_getFullMatrix() += *(m2.Matrix_getFullMatrix());

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){
		*Matrix_getSparseMatrix() += *(m2.Matrix_getSparseMatrix());

	}else if(Matrix_getFullMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){
		m2.Matrix_sparseToFull();
		*Matrix_getFullMatrix() += *m2.Matrix_getFullMatrix();
		delete m2.Matrix_getFullMatrix();
		m2.matrix_fullMatrix = NULL;

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){
		Matrix_sparseToFull();
		*Matrix_getFullMatrix() += *m2.Matrix_getFullMatrix();
		delete Matrix_getSparseMatrix();
		matrix_sparseMatrix = NULL;

	}
}

Matrix& Matrix::operator-(Matrix& m2){
	Matrix& tmp(*this);
	tmp -= m2;

	return tmp;
}

void Matrix::operator-=(Matrix& m2){
	if(Matrix_getFullMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		*Matrix_getFullMatrix() -= *m2.Matrix_getFullMatrix();

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		*Matrix_getSparseMatrix() -= *m2.Matrix_getSparseMatrix();

	}else if(Matrix_getFullMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		m2.Matrix_sparseToFull();
		*Matrix_getFullMatrix() -= *m2.Matrix_getFullMatrix();
		delete m2.Matrix_getFullMatrix();		
		m2.matrix_fullMatrix = NULL;

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		Matrix_sparseToFull();
		*Matrix_getFullMatrix() -= *m2.Matrix_getFullMatrix();
		delete Matrix_getSparseMatrix();
		matrix_sparseMatrix = NULL;

	}
}

Matrix& Matrix::operator*(Matrix& m2){
	Matrix& tmp(*this);
	tmp *= m2;

	return tmp;
}

void Matrix::operator*=(Matrix& m2){
	if(Matrix_getFullMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		*matrix_fullMatrix = *Matrix_getFullMatrix() * *m2.Matrix_getFullMatrix();

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		*matrix_sparseMatrix = *Matrix_getSparseMatrix() * *m2.Matrix_getSparseMatrix();

	}else if(Matrix_getFullMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		Matrix_fullToSparse();
		*matrix_sparseMatrix = *Matrix_getSparseMatrix() * *m2.Matrix_getSparseMatrix();
		delete Matrix_getFullMatrix();		
		matrix_fullMatrix = NULL;
		Matrix_conversion();

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		m2.Matrix_fullToSparse();
		*matrix_sparseMatrix = *Matrix_getSparseMatrix() * *m2.Matrix_getSparseMatrix();
		delete m2.Matrix_getSparseMatrix();
		m2.matrix_sparseMatrix = NULL;
		Matrix_conversion();

	}
}

int Matrix::Matrix_getConversionCap(){
	return Matrix::matrix_conversionCap;
}

FullMatrix* Matrix::Matrix_getFullMatrix(){
	return matrix_fullMatrix;
}
void Matrix::Matrix_setFullMatrix(FullMatrix* m2){
	if(matrix_fullMatrix != NULL)
		delete matrix_fullMatrix;
	matrix_fullMatrix = m2;
}

SparseMatrix* Matrix::Matrix_getSparseMatrix(){
	return matrix_sparseMatrix;
}
void Matrix::Matrix_setSparseMatrix(SparseMatrix* m2){
	if(matrix_sparseMatrix != NULL)
		delete matrix_sparseMatrix;
	matrix_sparseMatrix = m2;
}

int Matrix::Matrix_getValue(int x, int y){
	if(Matrix_getFullMatrix() != NULL)
		return Matrix_getFullMatrix()->FullMatrix_getValue(x, y);
	if(Matrix_getSparseMatrix() != NULL)
		return Matrix_getSparseMatrix()->SparseMatrix_getValue(x, y);
}
void Matrix::Matrix_setValue(int x, int y, int value){
	if(Matrix_getFullMatrix() != NULL)
		Matrix_getFullMatrix()->FullMatrix_setValue(x, y, value);
	if(Matrix_getSparseMatrix() != NULL)
		Matrix_getSparseMatrix()->SparseMatrix_setValue(x, y, value);
}

int Matrix::Matrix_getHeight(){
	if(Matrix_getFullMatrix() != NULL)
		return Matrix_getFullMatrix()->FullMatrix_getHeight();
	if(Matrix_getSparseMatrix() != NULL)
		return Matrix_getSparseMatrix()->SparseMatrix_getHeight();
}
void Matrix::Matrix_setHeight(int height){
	if(Matrix_getFullMatrix() != NULL)
		Matrix_getFullMatrix()->FullMatrix_setHeight(height);
	if(Matrix_getSparseMatrix() != NULL)
		Matrix_getSparseMatrix()->SparseMatrix_setHeight(height);
}

int Matrix::Matrix_getWidth(){
	if(Matrix_getFullMatrix() != NULL)
		return Matrix_getFullMatrix()->FullMatrix_getWidth();
	if(Matrix_getSparseMatrix() != NULL)
		return Matrix_getSparseMatrix()->SparseMatrix_getWidth();
}
void Matrix::Matrix_setWidth(int width){
	if(Matrix_getFullMatrix() != NULL)
		Matrix_getFullMatrix()->FullMatrix_setWidth(width);
	if(Matrix_getSparseMatrix() != NULL)
		Matrix_getSparseMatrix()->SparseMatrix_setWidth(width);
}