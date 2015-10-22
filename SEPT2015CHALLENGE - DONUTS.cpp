//////////////////////////////////////////////////////////////////////
//																	
//		Authors:		Yehya Awad		
//		E-mails:		yehyaawad.kip@gmail.com								
//		Project: 		Code Chef: Donuts							
//		   File:		SEPT2015CHALLENGE - DONUTS.cpp							
//		   Date:		Sept 8th, 2015								
//		   Link:		https://www.codechef.com/problems/DONUTS
//         Soln: 		https://www.codechef.com/viewsolution/8171137							
//																	
//////////////////////////////////////////////////////////////////////

/* Algorithm 
 
Try to use more chains to connect other chains.
 
Solve (donutsNum, chainsNum, chainsList)
	sort chainsList from least to highest
	for key,val in chainsList
		if (val is less than chainsList.ssize - i - cutsNum - 1)
			cutsNum += val;
			loop again;
		else 
			// After for loop we have exhausted all possible
			// removals of chains
			add the remaining  trivial cuts (between chains);
			break out of loop;
	
	return cutsNum;
*/
 
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int solve() {
	// Read data
	int donutSum, chainsNum;
	vector<int> chainsList;
 
	cin >> donutSum >> chainsNum;
 
	for (int i = 0; i < chainsNum; ++i)
	{
		int temp;
		scanf("%d", &temp); // apparently much faster than cin
		chainsList.push_back(temp);
	}
	// Solve algorithm 
	int cutsNum = 0;
	sort(chainsList.begin(), chainsList.end());
	for (int i = 0; i < chainsList.size(); i++) {
		int val = chainsList[i];
		int listSize = chainsList.size();
		if (val < listSize - 1 - cutsNum - i)
		{
			cutsNum += val;
			continue;
		} else {
			cutsNum += listSize - 1 - cutsNum - i;
			break;
		}
	}
	
	return cutsNum;
}

int main () {
	int T ;
 
	cin >> T;
 
	for (int i = 0; i < T; ++i)
	{
		cout << solve() << endl;
	}
 	return 0;
}