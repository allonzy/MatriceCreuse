#include "Matrix.h"
#include "FullMatrix.h"
#include "SparseMatrix.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void SparseCalc()
{
	SparseMatrix a("Test");
	SparseMatrix b("Test2");
	SparseMatrix c("Test");
	system("clear");

	cout << "Quel type d'opération voulez-vous ?" << endl;
	cout << "1 -> Addition" << endl << "2 -> Ajout" << endl << "3 -> Soustraction" << endl << "4 -> Retrait" << endl << "5 -> Multiplication" << endl << "6 -> Egalité" << endl;
	int i = 0;
	cin >> i;
	switch(i)
	{
		case 1:
		{
			c = a+b;
			c.SparseMatrix_display();
			break;
		}
		case 2:
		{
			a+=b;
			a.SparseMatrix_display();
			break;
		}
		case 3:
		/*{
			c = a-b;
			break;
		}
		case 4:
		{
			a-=b;
			break;
		}
		case 5:*/
		{
			c = a*b;
			c.SparseMatrix_display();
			break;
		}
		case 6:
		{
			a=b;
			a.SparseMatrix_display();
			cout << endl;
			b.SparseMatrix_display();
			break;
		}
		default:
		{
			cerr << "error" << endl;
			break;
		}
	}
}

void FullCalc()
{
	FullMatrix a("Test");
	FullMatrix b("Test2");
	FullMatrix c("Test");
	system("clear");

	cout << "Quel type d'opération voulez-vous ?" << endl;
	cout << "1 -> Addition" << endl << "2 -> Ajout" << endl << "3 -> Soustraction" << endl << "4 -> Retrait" << endl << "5 -> Multiplication" << endl << "6 -> Egalité" << endl;
	int i = 0;
	cin >> i;
	switch(i)
	{
		case 1:
		{
			c = a+b;
			c.FullMatrix_display();
			cout << endl << endl;
			a.FullMatrix_display();
			break;
		}
		case 2:
		{
			a+=b;
			a.FullMatrix_display();
			break;
		}
		case 3:
		{
			c = a-b;
			c.FullMatrix_display();
			break;
		}
		case 4:
		{
			a-=b;
			a.FullMatrix_display();
			break;
		}
		case 5:
		{
			c = a*b;
			c.FullMatrix_display();
			break;
		}
		case 6:
		{
			a=b;
			a.FullMatrix_display();
			cout << endl;
			b.FullMatrix_display();
			break;
		}
		default:
		{
			cerr << "error" << endl;
			break;
		}
	}
}

int main(int argc, char const *argv[])
{
	cout << "Quel type de calculette voulez-vous ?" << endl;
	cout << "1 -> Matrice pleine" << endl << "2 -> Matrice creuse" << endl;
	int i = 0;
	cin >> i;
	switch(i)
	{
		case 1:
		{
			FullCalc();
			break;
		}
		case 2:
		{
			SparseCalc();
			break;
		}
		default:
		{
			cerr << "error" << endl;
			break;
		}
	}
	return 0;
}
