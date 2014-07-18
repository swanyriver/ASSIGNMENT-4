/*
 * phrase.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#include <string>
#include <iostream>
#include <iterator> //for testing only
#include <set>

#include "PhraseGame.hpp"
#include "PreFabDictionary.hpp"
#include "hangmanDisplay.hpp"
#include "SwansonObjects/Dictionary.hpp"

using namespace std;

///global variables /////////////////////
const int MAX_GUESSES = 12;
const int MAX_WORDS = 5;
const int MIN_WORDS = 3;

///fuction declarations /////////////////

void display ( PhraseGame::Guess guess , set<string> GuessesMade );

//todo add arg reader for -s and -d   (clear screen off, and dictionary off)
//todo add menu for selecting theme dictionary, or entering your own

int main ( int argc , char* argv[] ) {

   //set clearscreen pointer
   ClearScreen = swansonUtil::ClearScreen;
   //ClearScreen = HackClearScreen; //alternate method;

   //local variables
   PhraseGame::Guess nextGuess;
   Dictionary myDict(PreFabDict::getSet()); //contructs BU dict

   myDict = Dictionary(6); //construcs a dict of 6 letter long words

   //construcs a dict of 6 letter long words from unformated file "moby.txt"
   myDict = ThemeDictionary(6,"moby.txt");

   //initializations
   //swansonUtil::SeedRandom();

   do {
      //use dictionary to make phrase
      string phrase;
      int numWords = swansonUtil::GetRandomInRange(MIN_WORDS,MAX_WORDS);
      for (int i = 0; i < numWords; ++i) {
         phrase+=myDict.GetRandomWord() + " ";
      }
      phrase.erase(phrase.length()-1,1); //remove extra space

      //instance a new game object
      PhraseGame myGame( myDict.GetSet() , phrase ,
            MAX_GUESSES );

      //initialize game state and display welcome screen
      nextGuess = myGame.NextGuess( true );
      display( nextGuess , myGame.GuessesMade() );

      do {
         //get a guess from user
         nextGuess = myGame.NextGuess();

         //display results
         display( nextGuess , myGame.GuessesMade() );

         //testing
         cout << endl << "secret is:[" << myGame.GetSecretPhrase() << "]";

         //keep guessing if not solved, or remaining guesses
      } while ( nextGuess.revealedPhrase != myGame.GetSecretPhrase()
            && nextGuess.guesesRemaining > 0 );

      //todo calculate win or loose
      //todo construct special display

      //offer to play again
   } while ( swansonInput::yesNo( "Play again" ) );

   return 0;
}

//black box && STUB testing
/*void display(PhraseGame::Guess guess, set<string> GuessesMade){
 //blackboxing
 cout << endl << "guesss is:" << guess.guess << endl;
 cout << endl << "guesses remaing:" << guess.guesesRemaining;
 cout << endl << "guesses valid:" << guess.succesful;
 cout << endl << "guesses correct:" << guess.correct;
 cout << endl << "message is:" << guess.message;
 cout << endl << "there are " << swansonString::NumOccurances("my secret phrase my", guess.guess)
 << " occurances of " << guess.guess << " in :my secret phrase my";
 cout << endl <<"the guess set contains: " << AllItemsInSet(GuessesMade);
 cout << endl << endl <<"secret phrase: [" << guess.revealedPhrase << "]";
 }

 string AllItemsInSet ( set<string> myset ) {
 string oString;
 //set<string>::iterator lookup;
 set<string>::iterator lookup;
 lookup = myset.begin();
 for ( int i = 0 ; i < myset.size() ; i++ ) {
 oString += *lookup + "/";
 lookup++;
 }

 return oString;

 }

 */

