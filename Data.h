#pragma once
#include <vector>

using namespace std;

class Data
{
public:
	Data();

protected:


private:
	vector< vector< vector<int> > > matrixes;

	void clear();
	unsigned int inputUInt();
	vector< vector<int> > createMatrix();
	void inputData(vector< vector<int> >& matrix);
	void displayMatrix(vector< vector<int> > matrix);
	unsigned assertDisplayedExists(vector< vector< vector<int> > > matrixes);
	void selectMatrixes(pair <unsigned, unsigned>& matrixes, unsigned size);
	void generateMatrixes(vector< vector< vector<int> > >& matrixes);
	pair<unsigned, unsigned> getSize(vector< vector<int> > matrix);
	void addSubtract(vector< vector< vector<int> > > matrixes, bool isAddition);
	void multiply(vector< vector< vector<int> > > matrixes);
	void userInterface(vector< vector< vector<int> > >& matrixes);
	void transposeMatrix(vector< vector< vector<int> > > matrixes);
	
};

