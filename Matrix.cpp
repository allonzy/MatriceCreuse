//!
//!	\file		FullMatrix.cpp
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp, Clément Personnettaz
//!	\version	1.0
//! \brief      Fichier d'implémentation de la classe FullMatrix. Définit les matrices pleines et leurs possibilités d'utilisation.
//! \details    Cette classe définit ce qu'est une matrice pleine, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
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

// --------------------------------

//!
//! \brief      Constructeur de matrice pleine vide, de taille personnalisée.
//! \details    Ce constructeur initialise une matrice pleine vide dont la taille est donnée en argument.
//! \param		height 	Taille de la matrice en lignes.
//! \param		width 	Taille de la matrice en colonnes.
//!

Matrix::Matrix(int height, int width){
	Matrix_setFullMatrix(new FullMatrix(height, width));
	Matrix_setSparseMatrix(NULL);
}

// --------------------------------

//!
//! \brief      Constructeur de matrice pleine, à partir d'un fichier.
//! \details    Ce constructeur initialise une matrice pleine à partir d'un fichier dont le chemin d'accès est donné en argument.
//! \param		filePath 	Chemin d'accès au fichier contenant la matrice à écrire.
//!

Matrix::Matrix(string filePath){
	Matrix_setFullMatrix(new FullMatrix(filePath));
	Matrix_setSparseMatrix(NULL);
}


// --------------------------------

//!
//! \brief      Constructeur de matrice creuse par recopie.
//! \details    Ce constructeur initialise une matrice creuse à partir d'une autre matrice creuse passée en argument.
//! \param		m2 	Matrice à recopier.
//!

Matrix::Matrix(Matrix& m2){
	if(m2.Matrix_getFullMatrix() != NULL)
		Matrix_setFullMatrix(new FullMatrix(m2.Matrix_getFullMatrix()));
	else
		Matrix_setFullMatrix(NULL);

	if(m2.Matrix_getSparseMatrix() != NULL)
		Matrix_setSparseMatrix(new SparseMatrix(m2.Matrix_getSparseMatrix()));
	else
		Matrix_setSparseMatrix(NULL);
}

// --------------------------------

//!
//! \brief      Destructeur de matrice.
//! \details    Destructeur, libère la mémoire allouée à la matrice.
//!

Matrix::~Matrix(){
	delete Matrix_getFullMatrix();
	delete Matrix_getSparseMatrix();
}

// --------------------------------

//!
//! \brief
//! \details
//!

void Matrix::Matrix_conversion(){
	if(Matrix_getFullMatrix() != NULL){

		int nbElem = Matrix_getFullMatrix().FullMatrix_getHeight() * Matrix_getFullMatrix().FullMatrix_getWidth();
		int nbZero = 0;
		for (int iRow = 0; iRow < Matrix_getFullMatrix().FullMatrix_getWidth(); iRow++)
	    {
	        for (int iCol = 0; iCol < Matrix_getFullMatrix().FullMatrix_getHeight(); iCol++)
	        {
	        	if(Matrix_getFullMatrix().FullMatrix_getValue(iRow, iCol) == 0)
	        		nbZero++;
	        }
	    }
	    double ratio = (nbZero / nbElem) * 100;
	    if(ratio > Matrix.Matrix_getConversionCap()){
	    	Matrix_fullToSparse();
	    	delete Matrix_getFullMatrix();
	    }

	}
	else if(Matrix_getSparseMatrix() != NULL){

		if(Matrix_getSparseMatrix().SparseMatrix_getUse() > Matrix.Matrix_getConversionCap()){
			Matrix_sparseToFull();
			delete Matrix_getSparseMatrix();
		}

	}
}

// --------------------------------

//!
//! \brief
//! \details
//!

void Matrix::Matrix_sparseToFull(){
	Matrix_setFullMatrix(new FullMatrix(Matrix_getSparseMatrix().SparseMatrix_getHeight(), Matrix_getSparseMatrix().SparseMatrix_getWidth()));
	for (int iRow = 0; iRow < Matrix_getFullMatrix().FullMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < Matrix_getFullMatrix().FullMatrix_getHeight(); iCol++)
        {
        	Matrix_getFullMatrix().FullMatrix_setValue(iRow, iCol, Matrix_getSparseMatrix().SparseMatrix_getValue());
        }
    }
}

// --------------------------------

//!
//! \brief
//! \details
//!

void Matrix::Matrix_fullToSparse(){
	Matrix_setSparseMatrix(new SparseMatrix(Matrix_getFullMatrix().FullMatrix_getHeight(), Matrix_getFullMatrix().FullMatrix_getWidth()));
	for (int iRow = 0; iRow < Matrix_getSparseMatrix().SparseMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < Matrix_getSparseMatrix().SparseMatrix_getHeight(); iCol++)
        {
        	Matrix_getSparseMatrix().SparseMatrix_setValue(iRow, iCol, Matrix_getFullMatrix().FullMatrix_getValue());
        }
    }
}

// --------------------------------

//!
//! \brief
//! \details
//!

Matrix& Matrix::operator+(Matrix& m2){
	Matrix& tmp(*this);
	tmp += m2;

	return tmp;
}

// --------------------------------

//!
//! \brief
//! \details
//!

Matrix& Matrix::operator+=(Matrix& m2){
	if(Matrix_getFullMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		Matrix_getFullMatrix() += m2.Matrix_getFullMatrix();
		return *this;

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		Matrix_getSparseMatrix() += m2.Matrix_getSparseMatrix();
		return *this;

	}else if(Matrix_getFullMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		m2.Matrix_sparseToFull();
		Matrix_getFullMatrix() += m2.Matrix_getFullMatrix();
		delete m2.Matrix_getFullMatrix();
		return *this;

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		Matrix_sparseToFull();
		Matrix_getFullMatrix() += m2.Matrix_getFullMatrix();
		delete Matrix_getSparseMatrix();
		return *this;

	}
}

// --------------------------------

//!
//! \brief
//! \details
//!

Matrix& Matrix::operator-(Matrix& m2){
	Matrix& tmp(*this);
	tmp -= m2;

	return tmp;
}

// --------------------------------

//!
//! \brief
//! \details
//!

Matrix& Matrix::operator-=(Matrix& m2){
	if(Matrix_getFullMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		Matrix_getFullMatrix() -= m2.Matrix_getFullMatrix();
		return *this;

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		Matrix_getSparseMatrix() -= m2.Matrix_getSparseMatrix();
		return *this;

	}else if(Matrix_getFullMatrix() != NULL && m2.Matrix_getSparseMatrix() != NULL){

		m2.Matrix_conversionForOperations();
		Matrix_getFullMatrix() -= m2.Matrix_getFullMatrix();
		delete m2.Matrix_getFullMatrix();
		return *this;

	}else if(Matrix_getSparseMatrix() != NULL && m2.Matrix_getFullMatrix() != NULL){

		Matrix_conversionForOperations();
		Matrix_getFullMatrix() -= m2.Matrix_getFullMatrix();
		delete Matrix_getSparseMatrix();
		return *this;

	}
}
