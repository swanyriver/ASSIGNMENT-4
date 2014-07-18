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

using namespace std;

///global variables /////////////////////

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

   do {
      //instance a new game object
      PhraseGame myGame( PreFabDict::getSet() , "my secret phrase" , 8 );

      nextGuess = myGame.NextGuess(true);
      display(nextGuess , myGame.GuessesMade());


      do {
         //get a guess from user
         nextGuess = myGame.NextGuess();

         //display results
         display( nextGuess , myGame.GuessesMade() );

         //keep guessing if not solved, or remaining guesses
      } while ( nextGuess.revealedPhrase != myGame.GetSecretPhrase()
            && nextGuess.guesesRemaining > 0 );

      //calculate win or loose
      //construct special display

      //offer to play again
   } while (swansonInput::yesNo("Play again"));

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

