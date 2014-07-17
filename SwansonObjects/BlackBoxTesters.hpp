/*
 * dictionaryTester.hpp
 *
 *  Created on: Jul 14, 2014
 *      Author: Brandon
 */

#ifndef BLACKBOXTESTER_HPP_
#define BLACKBOXTESTER_HPP_

#include <iostream>
#include <string>
#include <list>
#include "Dictionary.hpp"

using namespace std;

class DictionaryTester {
public:
   //////////////////////test functions of dictionary /////////////////////////
   static void TestDictionary ( Dictionary testDict ) {
      const int NUMRANDOM = 10;
      long int size = testDict.NumWords();
      cout << endl << endl << size << " words" << endl;

      string test[] = { "hello", "goodbye", "toodaloo", "6454klj", "thank you",
            "japan", "frost" };

      for ( int i = 0 ; i < 7 ; i++ ) {
         cout << test[i]
               << (testDict.IsAWord( test[i] ) ? " is a word" : " isn't a word")
               << endl;

      }
      cout << endl << "random words" << endl;
      for ( int i = 0 ; i < NUMRANDOM ; i++ )
         cout << testDict.GetRandomWord() << endl;

      getchar();
   }
   ///////////////////////end of test functions ///////////////////////////////
};


////todo,  adapt for repetative output /////
///todo move to another library ////////
///todo add start and stop string messages ///
///todo add overload call for a function that take an int as a paramater for enumaration
///todo use printf for this so that the number can be inserted into message

template <typename Type>
class OverAll{
private:
   list <Type> mAllElements;
   bool enumerated;
public:
   OverAll(bool enumed = false):enumerated(enumed){};
   OverAll(list <Type> allElements):
      enumerated(false), mAllElements(allElements){};
   void setEnumerated(bool onOff){ enumerated = onOff;}
   void Add(Type element){
      mAllElements.push_back(element);
   }
   void Go(void (*doThis)(Type toThis)){
      Go(doThis,mAllElements);
   }
   void Go(void (*doThis)(Type toThis), list<Type> allElements){
      int enumeration = 0;
      while(!allElements.empty()){
         if(enumerated){
            cout << endl <<"//////////";
            cout << "   ITEM " << enumeration << " Beginning  ";
            cout << "//////////////";
         }
         doThis(allElements.front());
         allElements.pop_front();

         if(enumerated){
            cout << endl << "////////////";
            cout << "   ITEM " << enumeration << " completed  ";
            cout << "////////////" << endl << endl;
            enumeration++;
         }
      }
   }
};


#endif /* BLACKBOXTESTER_HPP_ */
