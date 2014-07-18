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
   static bool GuessIsEqual ( string element , string mySet );
   static list<string> NextSmallestSubSets ( string mySet );
   //used in other plaeces to create recursion

   static bool GuessIsValid ( string guess, set<string> dictionary);

   static string RevealString( string phrase, set<string> guesses);

   static void AddWholeWordsToGuesses(string phrase, set<string> &guesses);

private:
   static bool GuessIsPart ( string element , list<string> setList );
   static bool GuessIsPart ( string element , string mySet );

   static bool GuessIsValid (list<string> guessList, set<string> dictionary);

   static string RevealString(list<string>phraseList, set<string> guesses);

   static inline bool HasSpaces(string s){
      return (!(s.find( ' ' ) == string::npos));
   }
};

///check if a whole word has been revealed///
///Iterative approach as illustration of recursive method calls ///
void GuessChecker::AddWholeWordsToGuesses(string phrase, set<string> &guesses){
   list<string> phraseWords = NextSmallestSubSets(phrase);
   list<string> phraseLetters;
   string nextword;
   while(!phraseWords.empty()){
      nextword = phraseWords.front();
      phraseWords.pop_front();

      phraseLetters = NextSmallestSubSets(nextword); //get letters

      while(!phraseLetters.empty() &&
         swansonUtil::ExistsInSet(phraseLetters.front(), guesses))
            phraseLetters.pop_front();
      if(phraseLetters.empty()) // all letters in word were in guess set
         guesses.insert(nextword); //add word to guesses
   }


}

//////build reveal string///////////
string GuessChecker::RevealString( string phrase, set<string> guesses){
   if(swansonUtil::ExistsInSet(phrase,guesses)){
      if(phrase.size()>1)return phrase + " ";
      else return phrase;
   }
   else if(phrase.size()>1){
      return RevealString(NextSmallestSubSets(phrase), guesses);
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
bool GuessChecker::GuessIsValid ( string guess, set<string> dictionary){
   if(!HasSpaces(guess)) { //single word or letter, check validity
      return swansonUtil::ExistsInSet(guess,dictionary);
   }
   else return GuessIsValid(NextSmallestSubSets(guess),dictionary);
}

bool GuessChecker::GuessIsValid ( list<string> guessList, set<string> dictionary){
   if ( guessList.empty() )
      return true;
   string MySubGuess = guessList.back();
   guessList.pop_back();
   return (GuessIsValid( MySubGuess, dictionary )
         && GuessIsValid( guessList , dictionary ));
}


/////check correct////////////////////
list<string> GuessChecker::NextSmallestSubSets ( string mySet ) {
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
bool GuessChecker::GuessIsPart ( string element , string mySet ) {
   return GuessIsPart( element , NextSmallestSubSets( mySet ) );
}
bool GuessChecker::GuessIsPart ( string element , list<string> setList ) {
   if ( setList.empty() )
      return false;
   string MySubSet = setList.back();
   setList.pop_back();
   return (GuessIsEqual( element , MySubSet )
         || GuessIsPart( element , setList ));
}
bool GuessChecker::GuessIsEqual ( string element , string mySet ) {
   if ( mySet.size() == 1 )
      return (element == mySet);
   else
      return ((element == mySet) || GuessIsPart( element , mySet ));
}

#endif /* RECURSIVEWORDCHECKER_HPP_ */
