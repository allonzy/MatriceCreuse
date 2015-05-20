//!
//!	\file		FullMatrix.cpp
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier d'implémentation de la classe FullMatrix. Définit les matrices pleines et leurs possibilités d'utilisation.
//! \details    Cette classe définit ce qu'est une matrice pleine, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
//!

// --------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include "FullMatrix.h"

// --------------------------------

using namespace std;

// --------------------------------


//!
//! \brief      Constructeur de matrice pleine vide.
//! \details    Ce constructeur initialise une matrice pleine vide, de taille 0 par 0.
//!

FullMatrix::FullMatrix(){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
}

// --------------------------------

//!
//! \brief      Constructeur de matrice pleine vide, de taille personnalisée.
//! \details    Ce constructeur initialise une matrice pleine vide dont la taille est donnée en argument.
//! \param		height 	Taille de la matrice en lignes.
//! \param		width 	Taille de la matrice en colonnes.
//!

FullMatrix::FullMatrix(int height, int width){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
	FullMatrix_setEmptyMatrix(height, width);
}

// --------------------------------

//!
//! \brief      Constructeur de matrice pleine, à partir d'un fichier.
//! \details    Ce constructeur initialise une matrice pleine à partir d'un fichier dont le chemin d'accès est donné en argument. (cf #loadMatrix)
//! \param		path 	Chemin d'accès au fichier contenant la matrice à écrire.
//!

FullMatrix::FullMatrix(string name){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);	
	FullMatrix_loadMatrix(name);
}

// --------------------------------

//!
//! \brief      Constructeur de matrice creuse par recopie.
//! \details    Ce constructeur initialise une matrice creuse à partir d'une autre matrice creuse passée en argument.
//! \param		m2 	Matrice à recopier.
//!

FullMatrix::FullMatrix(FullMatrix& m2){
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
	FullMatrix_setEmptyMatrix(m2.FullMatrix_getHeight(),m2.FullMatrix_getWidth());

	for (int iRow = 0; iRow < FullMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < FullMatrix_getHeight(); iCol++)
        {
			FullMatrix_setValue(iRow, iCol, m2.FullMatrix_getValue(iRow, iCol));
        }
    }
}

// --------------------------------

//!
//! \brief      Destructeur de matrice.
//! \details    Destructeur, libère la mémoire allouée à la matrice.
//!

FullMatrix::~FullMatrix(){
	FullMatrix_clear();
}

// --------------------------------

//!
//! \brief      Récupère la taille en lignes de la matrice.
//! \return		Un \e int représentant le nombre de lignes de la matrice.
//!

int FullMatrix::FullMatrix_getHeight(){return fullMatrix_height;}

// --------------------------------

//!
//! \brief      Récupère la taille en colonnes de la matrice.
//! \return		Un \e int représentant le nombre de colonnes de la matrice.
//!

int FullMatrix::FullMatrix_getWidth(){return fullMatrix_width;}

// --------------------------------

//!
//! \brief      Récupère la valeur située en \e X, \e Y dans la matrice.
//! \param		X 	Position en ligne souhaitée.
//! \param		Y 	Position en colonne souhaitée.
//! \return		Un \e int représentant la valeur située en \e X, \e Y dans la matrice.
//!

int FullMatrix::FullMatrix_getValue(int x, int y){
	if (x > FullMatrix_getHeight() || y > FullMatrix_getWidth() || x < 0 || y < 0){
		cerr << "getValue error : value is out of range.\n";
		return 0;
	}
	else return fullMatrix_m[x][y];
}

// --------------------------------

//!
//! \brief      Assigne un nombre de lignes à la matrice.
//! \param		value 	Nombre de lignes de la matrice, défini par l'utilisateur.
//!

void FullMatrix::FullMatrix_setHeight(int value){fullMatrix_height = value;}

// --------------------------------

//!
//! \brief      Assigne un nombre de colonnes à la matrice.
//! \param		value 	Nombre de colonnes de la matrice, défini par l'utilisateur.
//!

void FullMatrix::FullMatrix_setWidth(int value){fullMatrix_width = value;}

// --------------------------------

//!
//! \brief      Assigne une valeur en un point de la matrice.
//! \details	Une case définie à la valeur 0 (zéro) via cette fonction sera effacée.
//!	\param		X 		Position en ligne souhaitée.
//! \param		Y 		Position en colonne souhaitée.
//! \param		value 	Valeur à placer en \e X, \e Y.
//!

void FullMatrix::FullMatrix_setValue(int x, int y, int value){
	if (x > FullMatrix_getHeight() || y > FullMatrix_getWidth() || x < 0 || y < 0){
		cerr << "setValue error : position is out of range.\n";
		return;
	}
	else {fullMatrix_m[x][y] = value;}
}

// --------------------------------

//!
//! \brief      Affiche la matrice.
//!

void FullMatrix::FullMatrix_display(){
	for (int x = 0; x < FullMatrix_getHeight(); x++){
		for (int y = 0; y < FullMatrix_getWidth(); y++){
			cout << setw(5);
			cout << FullMatrix_getValue(x, y) << " ";
		}
		cout << endl;
	}
}

// --------------------------------

//!
//! \brief      Vide la matrice.
//! \details	Une case définie à la valeur 0 (zéro) via cette fonction sera effacée.
//!	\param		X 		Position en ligne souhaitée.
//! \param		Y 		Position en colonne souhaitée.
//! \param		value 	Valeur à placer en \e X, \e Y.
//!

void FullMatrix::FullMatrix_clear(){
	for (int i = 0; i < FullMatrix_getHeight(); i++)
	{
		delete [] fullMatrix_m[i];
	}
	FullMatrix_setHeight(0);
	FullMatrix_setWidth(0);
}

// --------------------------------

//!
//! \brief      Réinitialise la matrice.
//!	\param		height 		Nombre de lignes souhaité.
//! \param		width 		Nombre de colonnes souhaité.
//!

void FullMatrix::FullMatrix_setEmptyMatrix(int height, int width){
	FullMatrix_clear();
	FullMatrix_setHeight(height);
	FullMatrix_setWidth(width);

	fullMatrix_m = new int*[height];

	for (int i = 0; i < height; i++)
	{
		fullMatrix_m[i] = new int[width];
	}
}

// --------------------------------

//!
//! \brief      Charge une matrice depuis un fichier texte.
//! \details	Une case définie à la valeur 0 (zéro) via cette fonction sera effacée.
//!	\param		matrixName 		Nom du fichier contenant la matrice à écrire, sans extension.
//! \returns	Renvoie un booléen : true si tout s'est bien passé et que la matrice est écrite correctement, false et un message d'erreur sinon.
//!

bool FullMatrix::FullMatrix_loadMatrix(string matrixName){
	int rowSize;														
	int colSize;													
	int value;															

	string pathToMatrix = "Matrix/" + matrixName + ".full"; 
	ifstream loadedMatrix(pathToMatrix.c_str(), ios::in);
	if(loadedMatrix)
    {
    	loadedMatrix >> rowSize;
    	loadedMatrix >> colSize;
    	FullMatrix_setEmptyMatrix(rowSize,colSize);
		for (int iRow = 0; iRow < FullMatrix_getHeight(); iRow++)
        {
        	for (int iCol = 0; iCol < FullMatrix_getWidth(); iCol++)
        	{
        		loadedMatrix >> value;
        		FullMatrix_setValue(iRow, iCol, value);
        	}
        }
        loadedMatrix.close();
    }
    else
    {
    	cerr << "loadMatrix error : impossible to open " << matrixName << ".full\n";
    	return false;
    }
    return true;
}
bool FullMatrix::FullMatrix_saveMatrix(string matrixName)
{
	string pathToMatrix = "Matrix/" + matrixName + ".full";
	ofstream Matrix(pathToMatrix.c_str(), ios::out);
        
        if(Matrix)
        {
            Matrix << FullMatrix_getWidth() <<" "<< FullMatrix_getHeight()<< "\n";
            for(int x = 0;x < FullMatrix_getHeight() ; x++){
            	for (int y = 0; y < FullMatrix_getWidth(); y++)
            	{
            		Matrix << FullMatrix_getValue(x,y) << " ";
            	}
            	Matrix << "\n";
            }

                Matrix.close();
        } 
            else
    {
    	cerr << "saveMatrix error : impossible to create " << matrixName << ".full\n";
    	return false;
    }

}
// --------------------------------

//!
//! \brief      Opérateur d'addition (+) de matrices pleines.
//! \details	Permet l'addition des valeurs d'une matrice dans une autre.
//!	\param		m2 		Matrice à additionner avec la première.
//! \returns	Renvoie une matrice, résultant de l'opération.
//!

FullMatrix& FullMatrix::operator+(FullMatrix& m2){
	if (FullMatrix_getHeight() != m2.FullMatrix_getHeight() || FullMatrix_getWidth() != m2.FullMatrix_getWidth())
	{
		cerr << "operator + error : matrix uncompatible." << endl;
		return *this;
	}
	
	FullMatrix& tmp(*this);
	tmp += m2;

	return tmp;
}

// --------------------------------

//!
//! \brief      Opérateur d'ajout (+=) de matrices pleines.
//! \details	Permet l'ajout des valeurs d'une matrice dans une autre.
//!	\param		m2 		Matrice à ajouter dans la première.
//! \returns	Renvoie un pointeur sur la matrice résultat.
//!

void FullMatrix::operator+=(FullMatrix& m2){
	if (FullMatrix_getHeight() != m2.FullMatrix_getHeight() || FullMatrix_getWidth() != m2.FullMatrix_getWidth()){
		cerr << "operator += error : matrix uncompatible." << endl;
	}
	else
	{
		for (int iRow = 0; iRow < FullMatrix_getHeight(); iRow++)
		{
			for (int iCol = 0; iCol < FullMatrix_getWidth(); iCol++)
			{
				int v1 = FullMatrix_getValue(iRow,iCol);
	        	int v2 = m2.FullMatrix_getValue(iRow,iCol);
	        	FullMatrix_setValue(iRow, iCol,v1+v2);
			}
		}
	}
}

// --------------------------------

//!
//! \brief      Opérateur de soustraction (-) de matrices pleines.
//! \details	Permet la soustraction des valeurs d'une matrice avec une autre.
//!	\param		m2 		Matrice à soustraire avec la première.
//! \returns	Renvoie une matrice, résultant de l'opération.
//!

FullMatrix& FullMatrix::operator-(FullMatrix& m2){
	if (FullMatrix_getHeight() != m2.FullMatrix_getHeight() || FullMatrix_getWidth() != m2.FullMatrix_getWidth())
	{
		cerr << "operator - error : matrix uncompatible." << endl;
		return *this;
	}
	
	FullMatrix& tmp(*this);
	tmp -= m2;

	return tmp;
}

// --------------------------------

//!
//! \brief      Opérateur de retrait (-=) de matrices pleines.
//! \details	Permet la retrait des valeurs d'une matrice d'une autre.
//!	\param		m2 		Matrice à retirer de la première.
//! \returns	Renvoie un pointeur sur la matrice résultat.
//!

void FullMatrix::operator-=(FullMatrix& m2){
	if (FullMatrix_getHeight() != m2.FullMatrix_getHeight() || FullMatrix_getWidth() != m2.FullMatrix_getWidth())
	{
		cerr << "operator -= error : matrix uncompatible." << endl;
	}
	else
	{
		for (int iRow = 0; iRow < FullMatrix_getHeight(); iRow++)
		{
			for (int iCol = 0; iCol < FullMatrix_getWidth(); iCol++)
			{
				int v1 = FullMatrix_getValue(iRow,iCol);
	        	int v2 = m2.FullMatrix_getValue(iRow,iCol);
	        	FullMatrix_setValue(iRow, iCol,v1-v2);
			}
		}
	}
}

// --------------------------------
FullMatrix& FullMatrix::operator=(FullMatrix& m2)
{
	FullMatrix& m(m2);
	return m;
}
//--------------------------------
FullMatrix& FullMatrix::operator*(FullMatrix& m2)
{
	if(FullMatrix_getWidth() != FullMatrix_getHeight()){
			cerr << "operator*: incompatible matrix\n ";
			return *this;
		}
	else {
		FullMatrix m(FullMatrix_getHeight() , m2.FullMatrix_getWidth()) ;
		for (int x = 0; x < FullMatrix_getHeight(); x++)
		{
			for (int y = 0; y < FullMatrix_getWidth(); y++)
			{
				int tmpTotal = 0;
				for(int i = 0 ;i < m2.FullMatrix_getHeight() ; i++){
					tmpTotal += FullMatrix_getValue(x,i) * FullMatrix_getValue(i,y);
				}
				FullMatrix_setValue(x,y,tmpTotal);
			}
		}
	}
}
void FullMatrix::FullMatrix_random()
{
	int NumberCase=FullMatrix_getHeight()*FullMatrix_getWidth();
	for(int i = 0 ; i < NumberCase ; i++)
	{
		int x = rand()% FullMatrix_getWidth();
		int y = rand()% FullMatrix_getHeight();
		int value = rand() % 2000 -1000;
		FullMatrix_setValue(x,y,value);
	}

}