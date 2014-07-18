/*
 * RecursiveWordChecker.hpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#ifndef RECURSIVEWORDCHECKER_HPP_
#define RECURSIVEWORDCHECKER_HPP_

#include <string>
#include "SwansonLibs/swansonString.hpp"
using namespace std;

class GuessChecker {
public:
   static bool guessIsEqual ( string element , string set );
   //todo implement, guess is valid, check if all pieces, words and letters, are in the dictionary
private:
   static list<string> nextSmallestSubSets ( string set );
   static bool guessIsPart ( string element , list<string> setList );
   static bool guessIsPart ( string element , string set );
};

list<string> GuessChecker::nextSmallestSubSets ( string set ) {
   list<string> smallerChunks;
   if ( !(set.find( ' ' ) == string::npos) ) { // there exists spaces, seperate words
      swansonString::SeperateWords( set , smallerChunks );
      return smallerChunks;
   } else { //one word, seperate letters
      int position = 0;
      while ( position < set.size() ) {
         smallerChunks.push_back( set.substr( position , 1 ) );
         position++;
      }
      return smallerChunks;
   }
}
bool GuessChecker::guessIsPart ( string element , string set ) {
   return guessIsPart( element , nextSmallestSubSets( set ) );
}
bool GuessChecker::guessIsPart ( string element , list<string> setList ) {
   if ( setList.empty() )
      return false;
   string MySubSet = setList.back();
   setList.pop_back();
   return (guessIsEqual( element , MySubSet )
         || guessIsPart( element , setList ));
}
bool GuessChecker::guessIsEqual ( string element , string set ) {
   if ( set.size() == 1 )
      return (element == set);
   else
      return ((element == set) || guessIsPart( element , set ));
}

#endif /* RECURSIVEWORDCHECKER_HPP_ */
