//!
//!	\file		Main.cpp
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp, Clément Personnettaz
//!	\version	1.0
//! \brief      Fichier Pricipal pour les Tests.
//! \details    C'est dans ce fichier que les test sur les matrices sont effectuées.
//!

// --------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>

#include <cstdlib>
#include <ctime>

#include "SparseMatrix.h"
#include "FullMatrix.h"
#include "Matrix.h"

using namespace std;

void Test(Matrix m1, Matrix m2, int nbCasePleine, int heightMax, int widthMax);

int main(){
    Matrix m1 = new Matrix();
    Matrix m2 = new Matrix();
    Test(m1,m2,200,100,100)
}

// --------------------------------

//!
//! \brief      Permet de faire les tests sur les matrices.
//! \param		m1 et m2 les 2 matrices qui vont être testées.
//! \param		nbCasePleine la quantité de case qui seront remplies.
//! \param		heightMax taille en ligne maximale qu'auront les Matrices.
//! \param		widthMax taille en colonne maximale qu'auront les Matrices.
//!

void Test(Matrix m1, Matrix m2, int nbCasePleine, int heightMax, int widthMax){
    m1.Matrix_setHeight(heightMax);
    m1.Matrix_setWidth(widthMax);
    m2.Matrix_setHeight(heightMax);
    m2.Matrix_setWidth(widthMax);

    for (int i=0;i<nbCasePleine;i++){
        m1.Matrix_setValue(rand_a_b(0,heightMax),rand_a_b(0,widthMax),rand());
        m2.Matrix_setValue(rand_a_b(0,heightMax),rand_a_b(0,widthMax),rand());
        cout<<"valeur ajoutée"<<endl;
    }
}
