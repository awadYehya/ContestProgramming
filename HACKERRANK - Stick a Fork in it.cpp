
/****************************************************************

	       File: Stick a Fork in it.cpp
	     Author: Yehya Awad
	     E-mail: yha5009@psu.edu
	   Due Date: 25th May 2014
	Description: A fork in a software project occurs when a group of 
        developers take a copy of source code and start to independently 
        work on it. Such a fork can create a distinct software project that 
        is incompatible with later revisions to the original project. In 
        this problem, you will determine whether or not a software update 
        is likely to go smoothly based on these types of revisions.

    https://www.hackerrank.com/contests/psh-qualifying-contest-spring-2015/challenges/stick-a-fork-in-it-its-done
*****************************************************************/
/*
3 5

old --> New

Gnu_Emacs_18 Lucid_Emacs_19
Lucid_Emacs_19 XEmacs_19
Gnu_Emacs_18 Gnu_Emacs_19 

if old ---> can upgrade?

Gnu_Emacs_18 XEmacs_19 -- OH YES
Lucid_Emacs_19 Gnu_Emacs_19 - OH NO
XEmacs_19 Gnu_Emacs_19 - OH NO
Gnu_Emacs_19 Gnu_Emacs_18 -- OH NO
Gnu_Emacs_18 Gnu_Emacs_18 -- OH YES

ex. Gnu_Emacs_18: vector(Gnu_Emacs_19, Lucid_Emacs_19, XEmacs_19)
ex. Gnu_Emacs_19: vector()
ex. Lucid_Emacs_19: vector(XEmacs_19)
ex. XEmacs_19: vector()

	
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

typedef unordered_map<string,vector<string>> stringmap;

// prototypes
bool isAncestor(string currentPakg, string upgradePakg, stringmap & UniqueVersions) ;

int main() {
    
    long int N, M;
    cin >> N >> M ;

    stringmap UniqueVersions; // unordered_map string key, and vector

    for (long int k = 0; k < N; ++k)
    {
    	string sourcePakg, targetPakg ;
        vector<string> emptyVec ;
    	cin >> sourcePakg >> targetPakg ;
    	if (UniqueVersions.count(sourcePakg) == 0)
    	{
    		UniqueVersions.insert({sourcePakg,emptyVec}) ;

    	}
    	if (UniqueVersions.count(targetPakg) == 0)
    	{
    		UniqueVersions.insert({targetPakg,emptyVec}) ;

    	}

    	UniqueVersions[sourcePakg].push_back(targetPakg) ;

    }

    for (int i = 0; i < M; ++i)
    {
    	string currentPakg, upgradePakg;
    	cin >> currentPakg >> upgradePakg ;

    	if (isAncestor(currentPakg, upgradePakg, UniqueVersions))
    	{
    		cout << "all good" << endl ;
    	} else {
    		cout << "uh oh" << endl ;
    	}

    }
    
    return 0;
}

// recursion function chat checks different levels of ancestry (bad order)
bool isAncestor(string currentPakg, string upgradePakg, stringmap & UniqueVersions)
{
    if (currentPakg == upgradePakg)
    {
        return true;
    }
	for (int i = 0; i < UniqueVersions[currentPakg].size(); ++i)
	{
        //cout << currentPakg << "\t ----> " << UniqueVersions[currentPakg][i] << endl ; 
		if (upgradePakg == UniqueVersions[currentPakg][i])
		{
			return true;
		} else if (isAncestor(UniqueVersions[currentPakg][i], upgradePakg, UniqueVersions))
		{
			return true;
		}
	}

	return false; // did not find as an ancestor to current pakg.
}