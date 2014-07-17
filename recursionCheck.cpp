/*
 * recursionCheck.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const string PHRASE = "my secret phrase";
//const char* phraseWords[] = {"my","secret","phrase"};
const int numWords = 3;

/*bool isInPhrase (char* element, char* set){
   //for all elements

   //if there are spaces, then break down is in phrase

   return (std::strcmp(element,set) || subsetExists(char* element, char* set))
}
bool subsetExists(char* elemnent, char* set){
   //break down set, compare element

}*/
bool containedWithin(string element, string set, int position = 0);
bool areEqual (string element, string set);


bool areEqual (string element, string set){
   //for all elements

   //if there are spaces, then break down is in phrase

   return ((set == element) || containedWithin(element,set));
}
bool containedWithin(string element, string set, int position){
   //break down set, compare element
   if (position == element.size()) return (element == set.substr(position,1));
   else return( ( element == set.substr(position,1) ) || containedWithin(element, set, ++position));
}

//very close, but what about breaking down the element?

int main(){
 cout << "checking recursion" << endl;

 //test data
 string sets[] = {"hello", "goodbye", "farewell", "today"};
 string elements[] = {"o","e","g", "good", "hello" ,"a" ,"b", "z", "f", "today"};
 int setNum = 4;
 int elementNum = 8;

 //test loops
 for (int setIndex = 0; setIndex < setNum; ++setIndex) {
    cout << endl << "set is:" << sets[setIndex] << "    tests:";
   for (int elementIndex = 0; elementIndex < elementNum; ++elementIndex) {
      cout << " "<< elements[elementIndex] <<":" << areEqual(elements[elementIndex],sets[setIndex]);
   }
 }


}



