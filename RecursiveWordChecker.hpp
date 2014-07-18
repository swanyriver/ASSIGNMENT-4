/*
 * RecursiveWordChecker.hpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#ifndef RECURSIVEWORDCHECKER_HPP_
#define RECURSIVEWORDCHECKER_HPP_

#include <string>
#include <set>
#include "SwansonLibs/swansonString.hpp"



using namespace std;

class GuessChecker {
public:
   static bool guessIsEqual ( string element , string mySet );
   static list<string> nextSmallestSubSets ( string mySet );
   //used in other plaeces to create recursion

   static bool guessIsValid ( string guess, set<string> dictionary);

   static string RevealString( string phrase, set<string> guesses);

private:
   static bool guessIsPart ( string element , list<string> setList );
   static bool guessIsPart ( string element , string mySet );

   static bool guessIsValid (list<string> guessList, set<string> dictionary);

   static string RevealString(list<string>phraseList, set<string> guesses);

   static inline bool HasSpaces(string s){
      return (!(s.find( ' ' ) == string::npos));
   }
};


//////build reveal string///////////
string GuessChecker::RevealString( string phrase, set<string> guesses){
   if(swansonUtil::ExistsInSet(phrase,guesses)){
      if(phrase.size()>1)return phrase + " ";
      else return phrase;
   }
   else if(phrase.size()>1){
      return RevealString(nextSmallestSubSets(phrase), guesses);
   }else return "-";
}
string GuessChecker::RevealString( list<string>phraseList, set<string> guesses){
   string myPhrase = phraseList.front();
   phraseList.pop_front();

   if (phraseList.empty())return RevealString(myPhrase, guesses) + " ";
   else{
      return RevealString(myPhrase, guesses) +
            RevealString(phraseList,guesses);
   }
}

/////check valid////////////////////
bool GuessChecker::guessIsValid ( string guess, set<string> dictionary){
   if(!HasSpaces(guess)) { //single word or letter, check validity
      return swansonUtil::ExistsInSet(guess,dictionary);
   }
   else return guessIsValid(nextSmallestSubSets(guess),dictionary);
}

bool GuessChecker::guessIsValid ( list<string> guessList, set<string> dictionary){
   if ( guessList.empty() )
      return true;
   string MySubGuess = guessList.back();
   guessList.pop_back();
   return (guessIsValid( MySubGuess, dictionary )
         && guessIsValid( guessList , dictionary ));
}


/////check correct////////////////////
list<string> GuessChecker::nextSmallestSubSets ( string mySet ) {
   list<string> smallerChunks;
   //todo replace with HAS SPACES METHOD, UNDER TESTING
   if ( HasSpaces(mySet) ) { // there exists spaces, seperate words
      swansonString::SeperateWords( mySet , smallerChunks );
      return smallerChunks;
   } else { //one word, seperate letters
      int position = 0;
      while ( position < mySet.size() ) {
         smallerChunks.push_back( mySet.substr( position , 1 ) );
         position++;
      }
      return smallerChunks;
   }
}
bool GuessChecker::guessIsPart ( string element , string mySet ) {
   return guessIsPart( element , nextSmallestSubSets( mySet ) );
}
bool GuessChecker::guessIsPart ( string element , list<string> setList ) {
   if ( setList.empty() )
      return false;
   string MySubSet = setList.back();
   setList.pop_back();
   return (guessIsEqual( element , MySubSet )
         || guessIsPart( element , setList ));
}
bool GuessChecker::guessIsEqual ( string element , string mySet ) {
   if ( mySet.size() == 1 )
      return (element == mySet);
   else
      return ((element == mySet) || guessIsPart( element , mySet ));
}

#endif /* RECURSIVEWORDCHECKER_HPP_ */
