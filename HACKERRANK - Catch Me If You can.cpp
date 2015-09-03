
/****************************************************************

           File: Catch me if you can.cpp
         Author: Yehya Awad
         E-mail: yha5009@psu.edu
           Date: 28th Feb 2015
    Description: You are an FBI agent hot on the trail of a clever fraudster named Carmen. She is employing a variety of transportation methods to get from one city to the next: airplane, bus, ferry, taxi, and train. You’ve found a way to track what type of tickets she is purchasing. Use the information about the types of transportation available at different cities to figure out where Carmen has escaped to.

https://www.hackerrank.com/contests/psh-qualifying-contest-spring-2015/challenges/catch-me-if-you-can
*****************************************************************/
/*

modes - taxi, airplane, ferry, train, bus
  
    
*/


////////////////////////////////////////////
///// Code works as of March 6th, 2015 /////
////////////////////////////////////////////


#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

typedef vector<vector<string>> VectorVectorString ;
typedef unordered_map<string,VectorVectorString> d_stringmap;
typedef unordered_map<string, int> stringmap;
typedef set<string> stringSet;

// prototypes
void initModes (d_stringmap & UniqueRoutes, string start) ;
int getModeID (string mode) ;
bool solveProblem(string start,d_stringmap & UniqueRoutes, stringmap & result) ;
//bool takeRoute(string start, vector<string> & modesList, d_stringmap & UniqueRoutes, int modeIndex, stringmap & result) ;
string getModeString (int modeID);
bool allCitiesPossible(d_stringmap & UniqueRoutes, stringmap & result) ;
bool findCities(string start, vector<string> & modesList, d_stringmap & UniqueRoutes) ;
void printStringSet(stringSet arg_stringSet, int step) ;

int main() {
   
   d_stringmap UniqueRoutes ; // holds cities, then mode + destination
   // each vector is for the mode, then vector holds destinations
   vector <string> UniqueLocations ; // for testing

   stringmap result ;

   int Routes;
   cin >> Routes ;
   vector<string> destinations ;
   VectorVectorString emptyVecVec ;


   /////////////////////////////////
   ///// Reading in route info /////
   /////////////////////////////////
   
   for (int i = 0; i < Routes; ++i)
   {
       string mode, start, end;
       cin >> mode >> start >> end ;
       int modeID = getModeID(mode) ; // each mode has a number for indexing purposes in the vectorvector

       // Inserting route
       if (UniqueRoutes.count(start) == 0)
       {
            UniqueRoutes.insert({start,emptyVecVec}) ;
            UniqueLocations.push_back(start) ;
            initModes(UniqueRoutes, start) ;
            UniqueRoutes[start][modeID].push_back(end) ;
       } else
       {
            UniqueRoutes[start][modeID].push_back(end) ;
       }
       if (UniqueRoutes.count(end) == 0)
      {
        UniqueRoutes.insert({end,emptyVecVec}) ;
        UniqueLocations.push_back(end) ;
        initModes(UniqueRoutes, end) ;
      }
   }

   // Outputing all of the unique routes (testing to see if it read properly)
   /*
   for (int i = 0; i < UniqueLocations.size(); ++i)
    {
        string start = UniqueLocations[i];
        string end ;

        for (int o = 0; o < 5; ++o)
        {
            for (int k = 0; k < UniqueRoutes[start][o].size(); ++k)
            {
                end = UniqueRoutes[start][o][k] ;
                cout << "Route: " << start << "\t ---> \t" << end << "\t using mode: \t" << getModeString(o) << "\t mode ID \t" << o << endl ;
            }
        }
    }
    cout << endl ; // apart of the test too
    */


    /////////////////////////////////////
    ///// Solving provided problems /////
    /////////////////////////////////////
    

    int numOfProblems ;
    cin >> numOfProblems ;

   for (int i = 0; i < numOfProblems; ++i)
   {
       string start ;
       cin >> start ;
       //cout << "Starting at " << start << " let's see if we can follow this route." << endl ;
       if (solveProblem(start, UniqueRoutes, result) == false) 
       {
            cout << "Impossible" << endl ;
       } else {
          vector<string> sortedCities ;
          for (stringmap::iterator it = result.begin(); it != result.end(); ++it)
          {
            sortedCities.push_back(it->first) ;
          }
          sort(sortedCities.begin(), sortedCities.end());
          //cout << "Result contains " << sortedCities.size() << " cities, they are: " << endl; // testing
          for (int o = 0; o < sortedCities.size(); ++o)
          {
            cout << sortedCities[o] << " " ;
          }
          cout << endl ;
          result.clear() ;
          sortedCities.clear();
       }
   }

    return 0;
}


///////////////////////////
///// Other functions /////
///////////////////////////

// Returns an integer ID for the string of a mode of transportation
int getModeID (string mode) {
   if (mode == "taxi") {
        return 0 ;
   }
   else if (mode == "airplane") {
        return 1 ;
   }
   else if (mode == "bus") {
        return 2 ;
   }
   else if (mode == "ferry") {
        return 3 ;
   }
   else if (mode == "train") {
        return 4 ;
   }
    return 0 ;
}

// Returns string of mode using modeID
string getModeString (int modeID) {
    switch (modeID) {
        case 0:
            return "taxi" ;
        case 1:
            return "airplane" ;
        case 2:
            return "bus" ;
        case 3:
            return "ferry" ;
        case 4:
            return "train" ;
    }
    return "error" ;
}

void initModes (d_stringmap & UniqueRoutes, string start) {
    vector<string> emptyVec ;
    for (int i = 0; i < 5; ++i)
    {
        // initializing empty mode vector
        UniqueRoutes[start].push_back(emptyVec) ;
    }
}

bool solveProblem(string start,d_stringmap & UniqueRoutes, stringmap & result) {
    vector<string> modesList ;

    for (int i = 0; i < 53; ++i)
    {
        string mode;
        cin >> mode; 
        modesList.push_back(mode) ;
        //cout << mode << endl ;
        if (mode == "stop") break ;
    }
    if (UniqueRoutes.count(start) == 0) return false ;

    //return takeRoute(start, modesList, UniqueRoutes, 0, result);
    return findCities(start, modesList, UniqueRoutes) ; // new and improved takeRoute
    return true ; // for compiler warning
}


//////////////////////////////////////////////////////////
///// The Optomized Function for mucher better speed /////
//////////////////////////////////////////////////////////


// replacement function for takeRoute which was recursive.
// Much more efficient with resources. 
// Thanks for the help Dr. Blum, March 6th, 2015
bool findCities(string start, vector<string> & modesList, d_stringmap & UniqueRoutes) 
{
  stringSet currentStepCities, nextStepCities ;

  int numberOfSteps = modesList.size() ;
  currentStepCities.insert(start) ; // first city
  int modeID = 0 ;

  for (int i = 0; i < numberOfSteps-1; ++i)
  {
    modeID = getModeID(modesList[i]) ; // gets the mode
    for (stringSet::iterator CityString=currentStepCities.begin(); CityString!=currentStepCities.end(); ++CityString)
    {
      for (int o = 0; o < UniqueRoutes[*CityString][modeID].size(); ++o)
      {
        if (UniqueRoutes[*CityString][modeID].size() == 0)
        {
          continue ;
        }
        nextStepCities.insert(UniqueRoutes[*CityString][modeID][o]) ;
      }
    }
    printStringSet(currentStepCities, i);
    currentStepCities = nextStepCities ;
    nextStepCities.clear() ;
  }

  if (currentStepCities.empty())
  {
    return false ;
  } else {
    stringSet result = currentStepCities ;
    for (stringSet::iterator jkt=result.begin(); jkt!=result.end(); ++jkt)
    {
      cout << *jkt << " " ;
    }
    cout << endl ;
    return true ;
  }

}

void printStringSet(stringSet arg_stringSet, int step) {
  cout << "At step " << step << endl ;
  for (stringSet::iterator result=arg_stringSet.begin(); result!=arg_stringSet.end(); ++result)
    {
      cout << *result << " " ;
    }
    cout << endl ;
}


/////////////////////////////////////////////////////
///// Old slow function, replaced by findCities /////
/////////////////////////////////////////////////////

/*
bool takeRoute(string start, vector<string> & modesList, d_stringmap & UniqueRoutes, int modeIndex, stringmap & result) {
    cout << "At " << start << " travelled " << modeIndex << " steps by " << modesList[modeIndex] << endl;
    // at the final stop we...
    if (modesList[modeIndex] == "stop") 
    {
        if (result.count(start) == 0)
        {
          result.insert({start,0}) ;
        }
        // cout << " found!" << endl ;
        return true ;
    }
    if (allCitiesPossible(UniqueRoutes,result))
    {
      return true ;
    }
    // Part 1
    //cout << "Part 1" << endl ; // testing
    bool notImpossible = false ;
    int modeID = getModeID(modesList[modeIndex]) ;
    //cout << "Part 1.5" << endl ; // testing
    string nextStart ;
    //cout << "Part 2" << endl ; //testing
    //cout << endl << "Possible Routes at " << start << " mode " << modesList[modeIndex] << " are "; // testing
    //cout << UniqueRoutes[start][modeID].size() << endl ; // testing
    //cout << "They are: " << endl ; // testing

    if (UniqueRoutes[start][modeID].size() == 0) 
    {
        //cout << "No route found from " << start << " for " << modesList[modeIndex] << endl;
        return false;
    }
    
    // for testing, printing out all possible routes,
    // for (int i = 0; i < UniqueRoutes[start][modeID].size(); ++i)
    // {
    //   cout << UniqueRoutes[start][modeID][i] << ", " ;
    // }
    // cout << endl << endl ; // testing

    for (int i = 0; i < UniqueRoutes[start][modeID].size(); ++i)
    {
        // cout << "In this loop " << i << endl ;
        nextStart = UniqueRoutes[start][modeID][i];
        //cout << "After nextStart " << nextStart << " with modeIndex " << modeIndex << endl ;
        if (takeRoute(nextStart, modesList, UniqueRoutes, modeIndex+1, result))
        {
            notImpossible = true ;

            //cout << notImpossible << "Setting notImpossible to true at " << start << endl ;
        }
        // cout << "Back from " << nextStart << " route. " << notImpossible << endl ;
    }

    if (notImpossible == true)
    {
        //cout << "Not Impossible, returning true." << endl ;
        return true ;
    }

    // cout << "Failed, returning false at " << start << endl ;
    return false;
}
*/

bool allCitiesPossible(d_stringmap & UniqueRoutes, stringmap & result) {
  
  bool notFound = false ;
  for (d_stringmap::iterator kt = UniqueRoutes.begin(); kt != UniqueRoutes.end(); ++kt)
  {
    if (result.count(kt->first) == 0)
    {
      return false ;
      //cout << "ALL CITIES NOT POSSIBLE!" << endl ;
    }
  }
  
  //cout << "ALL CITIES POSSIBLE!!!" << endl ;
  return true ;
}





