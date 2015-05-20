//!
//!	\file		SparseMatrix.cpp
//! \author 	Simon Vivier, Jean Marliere, Maxime Dapp
//!	\version	1.0
//! \brief      Fichier d'implémentation de la classe SparseMatrix. Définit les matrices creuses et leurs possibilités d'utilisation.
//! \details    Cette classe définit ce qu'est une matrice creuse, ses accesseurs, ainsi que les surcharges d'opérateurs associées.
//!

// --------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <time.h>
#include <cstdlib>
#include "SparseMatrix.h"

// --------------------------------

using namespace std;

// --------------------------------


//!
//! \brief      Constructeur de matrice creuse vide.
//! \details    Ce constructeur initialise une matrice creuse vide, de taille 0 par 0.
//!

SparseMatrix::SparseMatrix(){
	SparseMatrix_setUse(0);
	SparseMatrix_setHeight(0);
	SparseMatrix_setWidth(0);
}

// --------------------------------

//!
//! \brief      Constructeur de matrice creuse, à partir d'un fichier.
//! \details    Ce constructeur initialise une matrice creuse à partir d'un fichier dont le chemin d'accès est donné en argument. (cf #loadMatrix)
//! \param		path 	Chemin d'accès au fichier contenant la matrice à écrire.
//!

SparseMatrix::SparseMatrix(string path){
	SparseMatrix_setUse(0);
	SparseMatrix_loadMatrix(path);
}

// --------------------------------

//!
//! \brief      Constructeur de matrice creuse par recopie.
//! \details    Ce constructeur initialise une matrice creuse à partir d'une autre matrice creuse passée en argument.
//! \param		m2 	Matrice à recopier.
//!

SparseMatrix::SparseMatrix(SparseMatrix& m2){
	SparseMatrix_setUse(0);
	SparseMatrix_setHeight(0);
	SparseMatrix_setWidth(0);
	SparseMatrix_clear();

	for (int iRow = 0; iRow < SparseMatrix_getWidth(); iRow++)
    {
        for (int iCol = 0; iCol < SparseMatrix_getHeight(); iCol++)
        {
			SparseMatrix_setValue(iRow, iCol, m2.SparseMatrix_getValue(iRow, iCol));
        }
    }
}

// --------------------------------

//!
//! \brief      Constructeur de matrice creuse vide, de taille personnalisée.
//! \details    Ce constructeur initialise une matrice creuse vide dont la taille est donnée en argument.
//! \param		height 	Taille de la matrice en lignes.
//! \param		width 	Taille de la matrice en colonnes.
//!

SparseMatrix::SparseMatrix(int height,int width)
{
	SparseMatrix_setUse(0);
	SparseMatrix_setHeight(height);
	SparseMatrix_setWidth(width);
}

// --------------------------------

//!
//! \brief      Destructeur de matrice.
//! \details    Destructeur, libère la mémoire allouée à la matrice.
//!

SparseMatrix::~SparseMatrix(){

}

// --------------------------------

//!
//! \brief      Récupère le niveau d'utilisation de la matrice.
//! \return		Un \e int représentant le niveau d'utilisation de la matrice.
//!

int SparseMatrix::SparseMatrix_getUse(){return sparseMatrix_use;}

// --------------------------------

//!
//! \brief      Récupère la taille en lignes de la matrice.
//! \return		Un \e int représentant le nombre de lignes de la matrice.
//!

int SparseMatrix::SparseMatrix_getHeight(){return sparseMatrix_height;}

// --------------------------------

//!
//! \brief      Récupère la taille en colonnes de la matrice.
//! \return		Un \e int représentant le nombre de colonnes de la matrice.
//!

int SparseMatrix::SparseMatrix_getWidth(){return sparseMatrix_width;}

// --------------------------------

//!
//! \brief      Récupère la valeur située en \e X, \e Y dans la matrice.
//! \param		X 	Position en ligne souhaitée.
//! \param		Y 	Position en colonne souhaitée.
//! \return		Un \e int représentant la valeur située en \e X, \e Y dans la matrice.
//!

int SparseMatrix::SparseMatrix_getValue(int x,int y){

	if(x > SparseMatrix_getHeight()  || y > SparseMatrix_getWidth()){
		cerr << "getValueError : value is out of range \n";
	}

	else if( ! sparseMatrix_m[make_pair(x,y)]){
		return 0;
	}
	else {
		return sparseMatrix_m[make_pair(x,y)];
	}
}

// --------------------------------

//!
//! \brief      Assigne un pourcentage maximal d'utilisation de la matrice.
//! \param		maxUse 	Pourcentage maximal d'utilisation de la matrice, défini par l'utilisateur.
//!


void SparseMatrix::SparseMatrix_setUse(){
	if(SparseMatrix_getHeight() != 0 && SparseMatrix_getWidth() != 0){
		float numberOfCase = SparseMatrix_getHeight() * SparseMatrix_getWidth();
		float usedCase =sparseMatrix_m.size();
		float use = usedCase / numberOfCase * 100;

		SparseMatrix_setUse(use);
	}
	else SparseMatrix_setUse(0);
}
//---------------------------------
pair<int,int> SparseMatrix::SparseMatrix_getKey(map<pair<int,int>,int>::iterator itr)
{
	return (*itr).first;
}
// --------------------------------

//!
//! \brief      Assigne un pourcentage maximal d'utilisation de la matrice.
//! \param		maxUse 	Pourcentage maximal d'utilisation de la matrice, défini par l'utilisateur.
//!


void SparseMatrix::SparseMatrix_setUse(float use){
	if(use >= 0 && use <= 100)
		sparseMatrix_use=use;
	else cerr << "setUse error : out of range \n";
}

// --------------------------------

//!
//! \brief      Assigne un nombre de lignes à la matrice.
//! \param		height 	Nombre de lignes de la matrice, défini par l'utilisateur.
//!

void SparseMatrix::SparseMatrix_setHeight(int height){sparseMatrix_height=height;}

// --------------------------------

//!
//! \brief      Assigne un nombre de colonnes à la matrice.
//! \param		width 	Nombre de colonnes de la matrice, défini par l'utilisateur.
//!

void SparseMatrix::SparseMatrix_setWidth(int width){sparseMatrix_width=width;}

// --------------------------------

//!
//! \brief      Assigne une valeur en un point de la matrice.
//! \details	Une case définie à la valeur 0 (zéro) via cette fonction sera effacée.
//!	\param		X 		Position en ligne souhaitée.
//! \param		Y 		Position en colonne souhaitée.
//! \param		value 	Valeur à placer en \e X, \e Y.
//!

void SparseMatrix::SparseMatrix_setValue(int x,int y,int value){
					// On place un itérateur à la position donnée.
	if(value == 0){																			// Si la valeur de cette case vaut 0 (zéro) ...
	map<pair<int,int>,int>::iterator it = sparseMatrix_m.find(make_pair(x,y) );
		if( it != sparseMatrix_m.end())
			sparseMatrix_m.erase(make_pair(x,y));											// On efface la case donnée.
		else return;
	}
	else if(x > SparseMatrix_getHeight()  || y > SparseMatrix_getWidth() || x < 0 || y < 0){					// Sinon, si la valeur est hors des bornes de la matrice ...
		cerr << "setValueError: value(x:"<<x<<")("<<y<<") is out of range \n";									// ... on affiche une erreur.
	}
	else{																					// Sinon, on a une valeur correcte ...
		sparseMatrix_m[make_pair(x,y)]=value;												// ... on réassigne donc la case à la valeur donnée.
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

void SparseMatrix::SparseMatrix_clear()
{
	sparseMatrix_m.clear();
}

// --------------------------------

//!
//! \brief      Affiche la matrice.
//!

void SparseMatrix::SparseMatrix_display(){
	for (int x = 0; x < SparseMatrix_getHeight(); x++){
		for (int y = 0; y < SparseMatrix_getWidth(); y++){
			cout << setw(5);
			cout << SparseMatrix_getValue(x, y) << " ";
		}
		cout << endl;
	}
}

// --------------------------------

//!
//! \brief      Charge une matrice depuis un fichier texte.
//! \details	Une case définie à la valeur 0 (zéro) via cette fonction sera effacée.
//!	\param		matrixName 		Nom du fichier contenant la matrice à écrire, sans extension.
//! \returns	Renvoie un booléen : true si tout s'est bien passé et que la matrice est écrite correctement, false et un message d'erreur sinon.
//!


bool SparseMatrix::SparseMatrix_loadMatrix(string matrixName)
{
	int rowSize=0;
	int colSize=0;
	int value;

	string pathToMatrix = "Matrix/" + matrixName + ".sparse"; 
	ifstream loadedMatrix(pathToMatrix.c_str(), ios::in);
	if(loadedMatrix)
    {
    	loadedMatrix >> colSize;
    	loadedMatrix >> rowSize;
    	SparseMatrix_setHeight(colSize);
    	SparseMatrix_setWidth(rowSize);
    	SparseMatrix_clear();
    	int row,col;
			while(true)
			{
        		loadedMatrix >>row>>col >> value;
        		SparseMatrix_setValue(row, col, value);
        		if(loadedMatrix.eof())break;
        	}
        loadedMatrix.close();
        SparseMatrix_setUse();
    }
    else
    {
    	cerr << "loadMatrix error : impossible to open " << matrixName << ".sparse\n";
    	return false;
    }
    return true;
}
//---------------------------------
bool SparseMatrix::SparseMatrix_saveMatrix(string matrixName)
{
	string pathToMatrix = "Matrix/" + matrixName + ".sparse";
	ofstream Matrix(pathToMatrix.c_str(), ios::out);  //déclaration du flux et ouverture du fichier
      //  Matrix.open(pathToMatrix);
        if(Matrix)  // si l'ouverture a réussi
        {
            Matrix << SparseMatrix_getWidth() <<" "<< SparseMatrix_getHeight()<< "\n";
            for(int x = 0;x < SparseMatrix_getHeight() ; x++){
            	for (int y = 0; y < SparseMatrix_getWidth(); y++)
            	{
            		if(SparseMatrix_getValue(x,y) != 0)Matrix <<x<<" "<<y<<" "<< SparseMatrix_getValue(x,y) << "\n";
            	}
            }

                Matrix.close();  // on referme le fichier
        } 
            else
    {
    	cerr << "saveMatrix error : impossible to create " << matrixName << ".sparse\n";
    	return false;
    }

}
// --------------------------------

//!
//! \brief      Opérateur d'ajout (+=) de matrices creuses.
//! \details	Permet l'ajout des valeurs d'une matrice dans une autre.
//!	\param		m2 		Matrice à ajouter dans la première.
//! \returns	Renvoie un pointeur sur la matrice résultat.
//!

void SparseMatrix::operator+=(SparseMatrix& m2)
{
	if (SparseMatrix_getHeight() != m2.SparseMatrix_getHeight() || SparseMatrix_getWidth() != m2.SparseMatrix_getWidth()){
		cerr << "operator += error : matrix uncompatible." << endl;
	}
	else {
		for (int iRow = 0; iRow < SparseMatrix_getHeight(); iRow++)
		{
			for (int iCol = 0; iCol < SparseMatrix_getWidth(); iCol++)
			{
				int v1 = SparseMatrix_getValue(iRow,iCol);
	        	int v2 = m2.SparseMatrix_getValue(iRow,iCol);
	        	SparseMatrix_setValue(iRow, iCol,v1+v2);
			}
		}
		SparseMatrix_setUse();
	}
}

// --------------------------------

//!
//! \brief      Opérateur d'addition (+) de matrices creuses.
//! \details	Permet l'addition des valeurs d'une matrice dans une autre.
//!	\param		m2 		Matrice à additionner avec la première.
//! \returns	Renvoie une matrice, résultant de l'opération.
//!

SparseMatrix& SparseMatrix::operator+(SparseMatrix& m2)
{
	if (SparseMatrix_getHeight() != m2.SparseMatrix_getHeight() || SparseMatrix_getWidth() != m2.SparseMatrix_getWidth())
	{
		cerr << "operator + error : matrix uncompatible." << endl;
		return *this;
	}
	
	SparseMatrix& tmp(*this);
	tmp += m2;
	return tmp;
}
//!
//! \brief      Opérateur de multiplication (*) de matrices creuses.
//! \details	Permet la multiplication des valeurs d'une matrice dans une autre.
//!	\param		m2 		Matrice à multiplier avec la première.
//! \returns	Renvoie une matrice, résultant de l'opération.
//!

SparseMatrix& SparseMatrix::operator*(SparseMatrix& m2)
{
	if(SparseMatrix_getWidth() != m2.SparseMatrix_getHeight()){
			cerr << "operator*: incompatible matrix\n ";
			return *this;
		}
	else {
		int j=0;
		SparseMatrix& m(m2);
		m.SparseMatrix_setHeight( SparseMatrix_getHeight() );
		m.SparseMatrix_setWidth( m2.SparseMatrix_getWidth() );
		map<pair<int,int>,int>::iterator it= sparseMatrix_m.begin();
		while(it != sparseMatrix_m.end())
		{
			int x=SparseMatrix_getKey(it).first;
			int y=SparseMatrix_getKey(it).second;
			int tmpTotal = 0;
			for(int i = 0 ;i < m2.SparseMatrix_getHeight() ; i++){
				tmpTotal += m.SparseMatrix_getValue(x,i) * m.SparseMatrix_getValue(i,y);
			}
			m.SparseMatrix_setValue(x,y,tmpTotal);
			it++;
			j++;
		}
		cout <<endl<< j<<endl;
		return m;
	}

}
// --------------------------------
SparseMatrix& SparseMatrix::operator=(SparseMatrix& m2)
{
	SparseMatrix& m(m2);
	return m;
}

// --------------------------------

void SparseMatrix::SparseMatrix_random(float use)
{
	float tmpNumberCase = use/100 * SparseMatrix_getHeight()*SparseMatrix_getWidth();
	int NumberCase=tmpNumberCase;
	for(int i = 0 ; i < NumberCase ; i++)
	{
		int x = rand()% SparseMatrix_getWidth();
		int y = rand()% SparseMatrix_getHeight();
		int value = rand() % 2000 -1000;
		SparseMatrix_setValue(x,y,value);
	}
	SparseMatrix_setUse();
}
//----------------------------------
void SparseMatrix::SparseMatrix_random()
{
	float use = rand()% 100;
	SparseMatrix_random(use);
}