
/****************************************************************

	       File: 
	     Author: Yehya Awad
	     E-mail: yha5009@psu.edu
	   Due Date: 1 March 2015
	Description: There are N integers in an array A. All but one 
	integer occur in pairs. Your task is to find out the number 
	that occurs only once.

https://www.hackerrank.com/challenges/lonely-integer
*****************************************************************/

#include <cmath>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <time.h>
#include <unordered_map>
using namespace std;

typedef unordered_map<int,int> intmap;

int main() {

	int result ;
	int N ;

	intmap lonelynums ;

	cin >> N ;

	for (int i = 0; i < N; ++i)
	{
		int localInt ;
		cin >> localInt ;

		if (lonelynums.count(localInt) == 0 )
		{
			lonelynums.insert({localInt,localInt}) ;
		} else {
			lonelynums.erase(localInt) ;
		}
	}

	// using iterator
    for (intmap::iterator it = lonelynums.begin(); it != lonelynums.end(); ++it) 
        cout << it->first; 
    cout << endl; 

}