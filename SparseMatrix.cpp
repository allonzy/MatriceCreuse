	SparseMatrix::SparseMatrix(){

	}
	SparseMatrix::SparseMatrix(string path)
	{

	}
	SparseMatrix::~SparseMatrix(){

	}
	int SparseMatrix::sparseMatrix_getMaxUse(){return sparseMatrix_maxUse}
	int SparseMatrix::sparseMatrix_getHeight(){return sparseMatrix_height;}
	int SparseMatrix::sparseMatrix_getWidth(){return sparseMatrix_width}
	int SparseMatrix::SparseMatrix_getValue(int x,int y){
		if(x > sparseMatrix_getHeight()  || y > sparseMatrix_getWidth(){
			cerr << "getValueError:value is out of range \n" ;
		}// remove when the code is complete
		if(!sparseMatrix_m[make_pair(x,y)]return 0;
			else return sparseMatrix_m[make_pair(x,y)];
	}

	void SparseMatrix::sparseMatrix_getMaxUse(int maxUse){sparseMatrix_maxUse=maxUse;}
	void SparseMatrix::SparseMatrix_setHeight(int height){sparseMatrix_height=height;}
	void SparseMatrix::SparseMatrix_setWidth(int width){sparseMatrix_width=width;}
	void SparseMatrix::SparseMatrix_setValue(int x,int y,int value){
		if(value == 0)//
		{
			if(sparseMatrix_m[make_pair(x,y)])
				sparseMatrix_m.erase(make_pair(x,y));
			else return;
		}
		else if(x > sparseMatrix_getHeight()  || y > sparseMatrix_getWidth(){	//value  out of range
			cerr << "setValueError: value is out of range \n";
		}
		else{	//we have a real value to insert
		if(!sparseMatrix_m[make_pair(x,y)])sparseMatrix_m.insert(pair<pair<int,int>,int>(<x,y>,value));//the slot dont exist 
		else sparseMatrix_m[make_pair(x,y)] = value;//we re-set the slot
		}
	}