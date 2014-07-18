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
#include "SwansonObjects/menu.hpp"

using namespace std;

///global variables /////////////////////
//const int MAX_GUESSES = 12;
const int MAX_GUESSES = 4;
const int MAX_WORDS = 5;
const int MIN_WORDS = 3;
//string literals
string STARTGAME_MESSAGE = "Welcome to the Game, Good Luck";
string LOST_GAME = "Congratulations, you got the Secret Phrase";
string WON_GAME = "You were close, but you didn't guess the Secret Phrase";

//global objects//////
Dictionary myDict;

///fuction declarations /////////////////

void display ( int guessRemaining , string revealPhrase , string message ,
      set<string> GuessesMade );

//menu item declarations
void PlayGame ();
void MobyDict(){
   //construcs a dict of 6 letter long words from unformatted file "moby.txt"
   myDict = ThemeDictionary( 6 , "moby.txt" );
   if (!myDict.Filled()) myDict = Dictionary( PreFabDict::getSet() );
}
void PlainDict(){
   myDict = Dictionary( 6 ); //Constructs a dict of 6 letter long words
   if (!myDict.Filled()) myDict = Dictionary( PreFabDict::getSet() );
}

//todo add arg reader for -s and -d   (clear screen off, and dictionary off)
//todo add menu for selecting theme dictionary, or entering your own

int main ( int argc , char* argv[] ) {

   //set clearscreen pointer
   ClearScreen = swansonUtil::ClearScreen;
   //ClearScreen = HackClearScreen; //alternate method;

   myDict = Dictionary( PreFabDict::getSet() ); //Constructs BU dict


   //local variables/objects
   Menu myMenu( Banner() );
   myMenu.demoAllItem = false;

   myMenu.addItem(MobyDict,"Moby.txt","setting dictionary to Moby Dick");
   myMenu.addItem(PlainDict,"Dictionary.txt","setting dictionary to plain");

   MenuItem playGameItem(PlayGame,"Play Game","intro");
   playGameItem.hasIntro = false;
   playGameItem.itemRepeat = false;
   myMenu.addItem(playGameItem);

   //myMenu.addItem(PlayGame,"play game","welcome to game");

   //myMenu.showMenu();
   PlayGame();


   return 0;
}

void PlayGame () {

   //local variables/objects
   PhraseGame::Guess nextGuess;

   //initializations
   swansonUtil::SeedRandom();


   do {
      //use dictionary to make phrase
      string phrase;
      int numWords = swansonUtil::GetRandomInRange( MIN_WORDS , MAX_WORDS );
      for ( int i = 0 ; i < numWords ; ++i ) {
         phrase += myDict.GetRandomWord() + " ";
      }
      phrase.erase( phrase.length() - 1 , 1 ); //remove extra space

      //tsting line wrap
      phrase = "this is my big dumb very long long long string to bge guessed lets see how it goes it is much longer than it should be";

      //instance a new game object
      PhraseGame myGame( myDict.GetSet() , phrase , MAX_GUESSES );

      //initialize game state and display welcome screen
      display( MAX_GUESSES , myGame.GetRevealPhrase() ,
            STARTGAME_MESSAGE , myGame.GuessesMade() );

      do {
         //get a guess from user
         nextGuess = myGame.NextGuess();

         //display results
         display( nextGuess.guesesRemaining , nextGuess.revealedPhrase ,
               nextGuess.message , myGame.GuessesMade() );

         //testing
         cout << endl << "secret is:[" << myGame.GetSecretPhrase() << "]";

         //keep guessing if not solved, or remaining guesses
      } while ( nextGuess.revealedPhrase != myGame.GetSecretPhrase()
            && nextGuess.guesesRemaining > 0 );

      //todo calculate win or loose
      //todo construct special display
      EndGameDisplay(phrase,myGame.GuessesMade());

      //offer to play again
   } while ( swansonInput::yesNo( "Play again" ) );

}

///////////////////////////////////
//black box && STUB testing/////////
///////////////////////////////////

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

