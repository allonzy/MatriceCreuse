//!
//!	\file		SparseMatrix.h
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp, Clément Personnettaz
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

// --------------------------------

using namespace std;

// --------------------------------

//!
//! \class 		SparseMatrix
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp, Clément Personnettaz
//! \brief      Cette classe définit ce qu'est une matrice creuse, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
//!

class SparseMatrix
{
	private:
		int sparseMatrix_maxUse;                    // Variable : Pourcentage d'utilisation de la matrice.
		int sparseMatrix_use;                       // Variable : Niveau d'utilisation de la matrice.
		map<pair<int,int>,int> sparseMatrix_m;      //
		int sparseMatrix_height;                    // Variable : Taille en lignes de la matrice.
		int sparseMatrix_width;                     // Variable : Taille en colonnes de la matrice.
		int sparseMatrix_elements;                  // Variable : Nombre d'éléments différents de 0

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
        int SparseMatrix_getElements();

		void SparseMatrix_setMaxUse(int maxUse);
		void SparseMatrix_setHeight(int height);
		void SparseMatrix_setWidth(int width);
		void SparseMatrix_setValue(int x,int y,int value);
		void SparseMatrix_setElements(int elements);

        void SparseMatrix_percentUse();
		void SparseMatrix_clear();
		void SparseMatrix_display();
		bool SparseMatrix_loadMatrix(string matrixName);

		SparseMatrix& operator+=(SparseMatrix& m2);
		SparseMatrix& operator+(SparseMatrix& m2);
};

// --------------------------------

#endif
