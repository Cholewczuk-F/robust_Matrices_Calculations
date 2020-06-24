#include "Data.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

//modyfikacje: - transponowanie macierzy - zamiana wierszy z kolumnami

Data::Data() {
	userInterface(matrixes);
}

void Data::userInterface(vector< vector< vector<int> > >& matrixes) {
	unsigned option = 0;

	cout << "Program for addition, subtraction and multiplication of matrixes. Program works on ID's [0-n].\n";
	do
	{
		cout << "\n 1 - Add new matrix.\n 2 - Display matrix.\n 3 - Add matrixes.\n 4 - Subtract matrixes.\n 5 - Multiply matrixes.\n 7 - Transpose Matrix\n 0 - Quit program.\nOption: ";
		option = inputUInt();
		switch (option)
		{
		case 1:
		{
			clear();
			matrixes.push_back(createMatrix());
			inputData(matrixes[0]);

			system("pause");
			clear();
			break;
		}
		case 2:
		{
			clear();
			unsigned matrixNumber = assertDisplayedExists(matrixes);
			if (matrixNumber != -1)
			{
				displayMatrix(matrixes[matrixNumber]);
			}

			system("pause");
			clear();
			break;
		}
		case 3: //dodawanie i odejmowanie muszą mieć identyczne wymiary
		{
			clear();
			addSubtract(matrixes, true);

			system("pause");
			clear();
			break;
		}
		case 4:
		{
			clear();
			addSubtract(matrixes, false);

			system("pause");
			clear();
			break;
		}
		case 5: //liczba elementow w wierszy pierwszej macierzy rowna liczbie elementow w kolumnie drugiej macierzy
		{
			clear();

			multiply(matrixes);
			system("pause");
			clear();
			break;
		}
		case 6: //for testing, randomize 3 matrixes for purposes - eligible for addition & subtraction + illegible, eligible for multiplication
			///generate matrixes
		{
			generateMatrixes(matrixes);
			break;
		}
		case 7:
		{
			clear();
			transposeMatrix(matrixes);

			system("pause");
			clear();
			break;
		}
		default:
		{
			cout << "Invalid option.\n\n";
		}
		}
	} while (option != 0);
}


void Data::transposeMatrix(vector< vector< vector<int> > > matrixes) {
	if (!matrixes.empty()) {
		unsigned matrixSelected = 0;

		do {
			cout << "Which matrix would you like to transpose [0-" << matrixes.size() <<  "]: ";
			matrixSelected = inputUInt();
			if (matrixSelected >= matrixes.size()) {
				cout << "There's not such matrix. Current number of matrixes: " << matrixes.size() << endl;
			}
		} while (matrixSelected >= matrixes.size());

		unsigned rowNumber = matrixes[matrixSelected].size();
		unsigned columnNumber = matrixes[matrixSelected][0].size();
		vector< vector<int> > transposition{ columnNumber, vector<int>(rowNumber) };

		for (int row = 0; row < matrixes[matrixSelected].size(); ++row) {
			for (int column = 0; column < matrixes[matrixSelected][0].size(); ++column) {
				transposition[column][row] = matrixes[matrixSelected][row][column];
			}
		}

		cout << "Selected matrix: " << endl << endl;
		displayMatrix(matrixes[matrixSelected]);
		cout << "Matrix after transposition: " << endl << endl;
		displayMatrix(transposition);
	}
}


unsigned int Data::inputUInt()
{
	string buffer = ""; unsigned int number;
	while (true)
	{
		getline(cin, buffer);
		stringstream intStream(buffer);
		if (intStream >> number)
		{
			return number;
		}
	}
}

void Data::clear()
{
	system("cls");
}

vector< vector<int> > Data::createMatrix()
{
	unsigned int rowNumber = 0; unsigned int columnNumber = 0;

	do
	{
		cout << "How many rows: ";
		rowNumber = inputUInt();
	} while (rowNumber <= 1 || rowNumber > 30);
	do
	{
		cout << "How many columns: ";
		columnNumber = inputUInt();
	} while (columnNumber <= 1 || columnNumber > 30);

	vector< vector<int> > matrix{ rowNumber, vector<int>(columnNumber) };
	return matrix;
}

void Data::inputData(vector< vector<int> >& matrix)
{
	cout << "Matrix data ingest: \n";

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix[i].size(); ++j)
		{
			cout << "Row " << i + 1 << ", column " << j + 1 << ": ";
			matrix[i][j] = inputUInt();
		}
	}
}


void Data::displayMatrix(vector< vector<int> > matrix)
{
	for (auto row : matrix)
	{
		cout << "|";
		for (auto element : row)
		{
			cout << element << setw(5 - to_string(element).length()) << "|";
		}
		cout << endl;
	}
	cout << endl;
}


unsigned Data::assertDisplayedExists(vector< vector< vector<int> > > matrixes)
{
	int matrixNumber = -1;
	do
	{
		cout << "Which matrix to display [0-n]: ";
		matrixNumber = inputUInt();
		if (matrixes.empty())
		{
			cout << "There are no matrixes.\n";
			return -1;
		}
		else if (matrixNumber >= matrixes.size())
		{
			cout << "Given matrix doesn't exist.\n";
		}
	} while (matrixNumber < 0 || matrixNumber >= matrixes.size());

	return matrixNumber;
}


void Data::selectMatrixes(pair <unsigned, unsigned>& matrixes, unsigned size)
{
	unsigned first = 0; unsigned second = 0;
	do
	{
		cout << "Number of first matrix [0-n]: ";
		first = inputUInt();
		cout << "Second matrix [0-n]:";
		second = inputUInt();
		if (first >= size || second >= size)
		{
			cout << "One of the matrixes selected doesn't exist.\n";
		}
	} while (first >= size || second >= size);
	matrixes.first = first;
	matrixes.second = second;
}


void Data::generateMatrixes(vector< vector< vector<int> > >& matrixes)
{
	unsigned tab[] = { 4, 4, 4, 4, 3, 2, 3, 2, 4, 3, 3, 2 };
	for (int i = 0; i < 6; ++i)
	{
		matrixes.push_back(vector< vector<int> > { tab[i * 2], vector<int>(tab[i * 2 + 1]) });
		for (auto& row : matrixes[i])
		{
			for (auto& element : row)
			{
				element = rand() % 15;
			}
		}
	}
}

pair<unsigned, unsigned> Data::getSize(vector< vector<int> > matrix) //returns pair containing size of a matrix 
{
	pair<unsigned, unsigned> size = { matrix.size(),  matrix[0].size() };
	return size;
}



void Data::addSubtract(vector< vector< vector<int> > > matrixes, bool isAddition)
{
	if (!matrixes.empty())
	{
		pair<unsigned, unsigned> selectedMatrixes = { 0, 0 };
		cout << "You will now select two matrixes to be " << (isAddition ? "add.\n\n" : "subtracted.\n\n");
		selectMatrixes(selectedMatrixes, matrixes.size());

		pair<unsigned, unsigned> firstSize = getSize(matrixes[selectedMatrixes.first]);
		pair<unsigned, unsigned> secondSize = getSize(matrixes[selectedMatrixes.second]);
		if (firstSize.first == secondSize.first && firstSize.second == secondSize.second)
		{
			vector< vector<int> > result{ firstSize.first, vector<int>(firstSize.second) };
			if (isAddition)
			{
				for (int row = 0; row < firstSize.first; ++row)
				{
					for (int column = 0; column < firstSize.second; ++column)
					{
						result[row][column] = matrixes[selectedMatrixes.first][row][column] + matrixes[selectedMatrixes.second][row][column];
					}
				}
			}
			else
			{
				for (int row = 0; row < firstSize.first; ++row)
				{
					for (int column = 0; column < firstSize.second; ++column)
					{
						result[row][column] = matrixes[selectedMatrixes.first][row][column] - matrixes[selectedMatrixes.second][row][column];
					}
				}
			}
			cout << "Matrix 1: " << endl << endl;
			displayMatrix(matrixes[selectedMatrixes.first]);
			cout << "Matrix 2: " << endl << endl;
			displayMatrix(matrixes[selectedMatrixes.second]);

			cout << "Result of " << (isAddition ? "addition: " : "subtraction: ") << endl << endl;
			displayMatrix(result);
		}
		else
		{
			cout << "The matrixes have to be of same dimensions for them to " << (isAddition ? "be added." : "be subtracted.") << endl;
		}
	}
	else
	{
		cout << "There are no matrixes.\n";
	}
}

void Data::multiply(vector< vector< vector<int> > > matrixes)
{
	if (!matrixes.empty())
	{
		pair<unsigned, unsigned> selectedMatrixes = { 0, 0 };
		cout << "You will now select matrix A - multiplied, and matrix B - multiplier.\n\n";
		selectMatrixes(selectedMatrixes, matrixes.size());

		pair<unsigned, unsigned> firstSize = getSize(matrixes[selectedMatrixes.first]);
		pair<unsigned, unsigned> secondSize = getSize(matrixes[selectedMatrixes.second]);

		if (firstSize.second == secondSize.first)
		{
			vector< vector<int> > result{ firstSize.first, vector<int>(secondSize.second) };
			for (int row = 0; row < firstSize.first; ++row)
			{
				for (int column = 0; column < secondSize.second; ++column)
				{
					int sum = 0;
					for (int element = 0; element < firstSize.second; ++element)
					{
						sum += matrixes[selectedMatrixes.first][row][element] * matrixes[selectedMatrixes.second][element][column];
					}
					result[row][column] = sum;
				}
			}
			cout << "Matrix 1: " << endl << endl;
			displayMatrix(matrixes[selectedMatrixes.first]);
			cout << "Matrix 2: " << endl << endl;
			displayMatrix(matrixes[selectedMatrixes.second]);

			cout << "Result of multiplication:" << endl << endl;
			displayMatrix(result);
		}
		else
		{
			cout << "Number of columns in matrix A doesn't correspond to number of rows in matrix B. Try again.\n";
		}
	}
	else
	{
		cout << "There are no matrixes.\n";
	}
}