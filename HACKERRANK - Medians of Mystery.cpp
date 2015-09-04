#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

/* Thinking space:
	
Sample Input:
				3 3 ? 9
				4 12 ? ? ? 
	Output:		
				12

HOW IT WORKS:
				left = 3 - [12] - right = 3

				If any side = half, then we median that shit.

Sample Input2: ? 8 8 8 ? ? ?
				4 8 8 ? ?
				3 ? 8 ?
	Output:	
				8

HOW IT WORKS:
				left =	2 repeated + 3 - [8] - right = 2 repeated + 3
				should I make a range when repeated?
				like... + or - 2 because it's repeated twice? because median 
Sample Input3: 
				4 ? 6 ? 18
				3 2 ? ?
	Output:	
				Unknown

HOW IT WORKS:
				 


*/


///////////////////////
///// saving time /////
///////////////////////


typedef unordered_map<int,int> intmap;
typedef vector<string> stringVector;
typedef vector<int> intVecTy ;


//////////////////////
///// Prototypes /////
//////////////////////

void PrintLeftRightVals(intVecTy rowInts, intVecTy left, intVecTy right);
intVecTy stringVecTOint(stringVector arg_stringVec);
intVecTy ref_getRestOfLeft(intVecTy a, intVecTy b, intVecTy c, intVecTy d) ;
intVecTy ref_getRestOfRight(intVecTy a, intVecTy b, intVecTy c, intVecTy d) ;
intVecTy ref_getInitialLeft (stringVector row)  ;
intVecTy ref_getInitialRight (stringVector row)  ;
stringVector ref_getInputData(stringVector &row1, stringVector &row2) ;
bool PrintMysteryMedian(intVecTy intRow, intVecTy RowLeft, intVecTy RowRight, int totalSize) ;


////////////////
///// Main /////
////////////////


int main() 
{
	
	long int row1Width, row2Width ; // useless as of now

	stringVector row1, row2, combinedRows;
	intVecTy left1, right1, left2, right2, intRow1, intRow2;
	string currentString ;

	combinedRows = ref_getInputData(row1, row2) ; // useless as of now

	// Reading in the input
	intRow1 = stringVecTOint(row1) ;
	intRow2 = stringVecTOint(row2) ;
	// Getting their size/width
	row1Width = row1.size();  
	row2Width = row2.size() ;
	// Getting the initial left/right values for every number 
	left1 = ref_getInitialLeft(row1) ;
	right1 = ref_getInitialRight(row1) ;
	left2 = ref_getInitialLeft(row2) ;
	right2 = ref_getInitialRight(row2) ;
	// Getting the other left/right values from separate rows if possible
	// for row1
	intVecTy resultLeft1( ref_getRestOfLeft(left1, intRow1, intRow2, left2) );
	intVecTy resultRight1( ref_getRestOfRight(right1, intRow1, intRow2, right2) );
	intVecTy resultLeft2( ref_getRestOfLeft(left2, intRow2, intRow1, left1) );
	intVecTy resultRight2( ref_getRestOfRight(right2, intRow2, intRow1, right1) );
	// PrintLeftRightVals(intRow1, resultLeft1, resultRight1) ; // testing purposes, prints l - num - r
	// PrintLeftRightVals(intRow2, resultLeft2, resultRight2) ; // testing purposes, prints l - num - r

	// Printing result 
	if (PrintMysteryMedian(intRow1, resultLeft1, resultRight1, intRow1.size()+intRow2.size()))
	{
		exit(0) ;
	} else if (PrintMysteryMedian(intRow2, resultLeft2, resultRight2, intRow1.size()+intRow2.size()))
	{
		exit(0) ;
	}
	cout << "Unknown" ;
	return 0;
}


/////////////////////
///// Functions /////
/////////////////////

bool PrintMysteryMedian(intVecTy intRow, intVecTy RowLeft, intVecTy RowRight, int totalSize) 
{
	for (int i = 0; i < intRow.size(); ++i)
	{	
		int number = intRow[i] ;
		int half = totalSize/2 ;
		if (RowLeft[i] >= half && RowRight[i] >= half)
		{
			cout << number ;
			return true ;
		}
	}
	return false ;
}

void PrintLeftRightVals(intVecTy rowInts, intVecTy leftVals, intVecTy rightVals)
{
	for (int i = 0; i < rowInts.size(); ++i)
	{
		if (rowInts[i] == -1) continue ;
		cout << leftVals[i] << "\t - \t" << rowInts[i] <<  "\t - \t" << rightVals[i] << endl ;
	}
	cout << endl ;
}

intVecTy stringVecTOint(stringVector arg_stringVec)
{
	intVecTy intVector ;
	for (int i = 0; i < arg_stringVec.size(); ++i)
	{
		if (arg_stringVec[i] != "?")
		{
			intVector.push_back(stoi(arg_stringVec[i], NULL, 10));
		} else 
		{
			intVector.push_back(-1) ; // -1 , meaning ? mark
		}
	}

	return intVector ;
}

// basically extracts any remaining left values from the other row input to help in finding median
intVecTy ref_getRestOfLeft(intVecTy first_Left, intVecTy first_intRow, intVecTy second_intRow, intVecTy second_Left) 
{
	intVecTy resultLeft ;

	// Sample Input:
	// 			3 3 ? 9
	// 			4 12 ? ? ? 
	// right row1 2 1 0
	// left row1  0 1 2
	// right row2 3  2 1 0
	// left row2  0  1 2 3

	for (int i = 0; i < first_intRow.size(); ++i)
	{
		int first_Num = first_intRow[i] ;
		// cout << "Starting to find rest of left for: " << first_Num << endl ;
		if (first_Num == -1) 
		{
			resultLeft.push_back(-1);
			continue ;
		}
		for (int O = 0; O < second_intRow.size(); ++O)
		{	
			// cout << "In O Loop" << endl ;
			int SecondRowSize = second_intRow.size() ;
			int s_Left = second_Left[SecondRowSize-O-1] ; // number of left digits of the second number.
			int second_Num = second_intRow[SecondRowSize-O-1];
			// cout << "\t Now at: " << second_Num << endl ;
			if (second_Num == -1 && O == SecondRowSize-1)
			{
				resultLeft.push_back(first_Left[i]) ;
				continue ;
			} else if (second_Num == -1)
			{
				continue ;
			} else if (second_Num <= first_Num)
			{
				// cout << "for " << first_Num << " adding " <<  s_Left + 1 << " to left from " << second_Num << endl ;
				// cout << "resultLeft at index " << i << " number " << first_Num << " is " << first_Left[i] + s_Left + 1 << endl ;
				resultLeft.push_back(first_Left[i] + s_Left + 1) ;
				break ;
			} else if (O == SecondRowSize-1) 
			{
				resultLeft.push_back(first_Left[i]) ;
			}
		}

	}

	return resultLeft ;
}

// basically extracts any remaining right values from the other row input to help in finding median
intVecTy ref_getRestOfRight(intVecTy first_Right, intVecTy first_intRow, intVecTy second_intRow, intVecTy second_Right) 
{
	intVecTy resultRight ;

	for (int i = 0; i < first_intRow.size(); ++i)
	{
		int first_Num = first_intRow[i] ;
		if (first_Num == -1) 
		{
			resultRight.push_back(-1);
			continue ;
		}
		for (int O = 0; O < second_intRow.size(); ++O)
		{	
			int SecondRowSize = second_intRow.size() ;
			int s_Right = second_Right[O] ; // number of Right digits of the second number.
			int second_Num = second_intRow[O];
			if (second_Num == -1 && O == SecondRowSize-1)
			{
				resultRight.push_back(first_Right[i]) ;
				continue ;
			} else if ( second_Num == -1 )
			{
				continue ;
			}
			else if (second_Num >= first_Num)
			{
				// cout << "for " << first_Num << " adding " <<  s_Right + 1 << " to right from " << second_Num << endl ;
				// cout << "resultRight at index " << i << " number " << first_Num << " is " << first_Right[i] + s_Right + 1 << endl ;
				resultRight.push_back(first_Right[i] + s_Right + 1) ;
				break ;
			} else if (O == SecondRowSize-1) 
			{
				resultRight.push_back(first_Right[i]) ;
			}
		}
	}

	return resultRight ;
}

// simple evaluation of left value based on index
intVecTy ref_getInitialLeft (stringVector row)  
{
	intVecTy leftVals;

	for (int i = 0; i < row.size(); ++i)
	{
		leftVals.push_back(i) ;
	}

	return leftVals;
}

// simple evaluation of right value based on index
intVecTy ref_getInitialRight (stringVector row)  
{
	intVecTy rightVals;

	for (int i = 0; i < row.size(); ++i)
	{
		rightVals.push_back(row.size() - i - 1);
	}

	return rightVals;
}

// simply combining two string vectors // not really used, thought I would, but didn't need to.
stringVector ref_getInputData(stringVector &row1, stringVector &row2)
{
	stringVector combinedRows ;

	int width ;
	cin >> width ;
	for (int i = 0; i < width; ++i)
	{
		string numba ;
		cin >> numba ;

		row1.push_back(numba) ;
		combinedRows.push_back(numba) ;
	}

	cin >> width ;
	for (int i = 0; i < width; ++i)
	{
		string numba ;
		cin >> numba ;

		row2.push_back(numba) ;
		combinedRows.push_back(numba) ;
	}

	return combinedRows ;
}