
//////////////////////////////////////////////////////////////////////
//																	
//		Authors:		Yehya Awad		
//		E-mails:		yehyaawad.kip@gmail.com								
//		Project: 		Code Chef: Count Steps in Matrix							
//		   File:		SEPT2015CHALLENGE - MSTEP.cpp							
//		   Date:		Sept 4th, 2015															
//																	
//////////////////////////////////////////////////////////////////////


#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;

typedef unordered_map<int,int> IdMatrix;

/* Protos */
void solveNext();
int calculateMinMoves () ;
int getPosId (int mDim, int row, int col);
int getRowFromId (int mDim, int posId);
int getColFromId (int mDim, int posId);
int getDiff (int x, int y);

/* Main Start */
int main () {

	int problemNum = 0;

	cin >> problemNum ;

	for (int i = 0; i < problemNum; ++i)
	{
		solveNext();
	}

	return 0;
}
/* Main End */

int calculateMinMoves () {
	int matrixDimension = 0;
	IdMatrix currentMatrix;

	cin >> matrixDimension;

	// Reading data and pre-processing
	for (int row = 1; row <= matrixDimension; ++row)
	{
		for (int col = 1; col <= matrixDimension; ++col)
		{
			int cellValue;
			// Generate posId
			int posId = getPosId(matrixDimension, row, col);
			// Read in cellValue
			cin >> cellValue;
			// cout << "Cell: " << cellValue << " PosId: " << posId;
			// cout << " Row: " << getRowFromId(matrixDimension, posId);
			// cout << " Col: " << getColFromId(matrixDimension, posId) << endl;
			// Add to matrix
			currentMatrix[cellValue] = posId;
		}
	}
	// Solving
	int moveCounter = 0;
	int mDimensionSquared = matrixDimension * matrixDimension;
	int currCol = getColFromId(matrixDimension, currentMatrix[1]), currRow = getRowFromId(matrixDimension, currentMatrix[1]);

	for (int i = 2; i <= mDimensionSquared; ++i)
	{
		int posId = currentMatrix[i];
		int col = getColFromId(matrixDimension, posId);
		int row = getRowFromId(matrixDimension, posId);

		moveCounter += getDiff(col, currCol);
		moveCounter += getDiff(row, currRow);

		currRow = row;
		currCol = col;
	}

	return moveCounter;
}

void solveNext() {
	
	cout << calculateMinMoves() << "\n";

	return;
}

int getPosId (int mDim, int row, int col) {
	return (mDim * (row-1)) + col ;
}

int getRowFromId (int mDim, int posId) {
	return ceil(float(posId)/float(mDim));
}

int getColFromId (int mDim, int posId) {
	return (posId % mDim) ? posId % mDim : mDim;
}

int getDiff (int x, int y) {
	if (x >= y)
	{
		// cout << "Dif: " << x << " & " << y << " is " << x - y << endl;
		return x - y;
	}

	// cout << "Dif: " << x << " & " << y << " is " << y - x << endl;
	return y - x;
}
