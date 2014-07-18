/*
 * PhraseGame.hpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#ifndef PHRASEGAME_HPP_
#define PHRASEGAME_HPP_

#include "SwansonLibs/swansonUtils.hpp"
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonLibs/swansonString.hpp"
#include "RecursiveWordChecker.hpp"

#include <sstream>
#include <string>
#include <set>
#include <list>

class PhraseGame {
public:
   //public guess object
   struct Guess {
      bool succesful;
      string message;
      string guess;
      bool correct;
      int guesesRemaining;
      string revealedPhrase;
   };

private:

   // messages
   static string GUESS_PROMPT;
   //not letter // not word //or a word in it is not in the dictionary
   static string NOT_IN_DICT;
   static string GUESSED_BEFORE;
   static string CORRECT_GUESS;
   static string WRONG_GUESS;
   static string OCCURANCES;

   //global variables
   int mGuessesRemaining;
   string mSecretPhrase;
   set<string> mSourceWords;
   set<string> mGuesseesMade;

   //internal methods
   string GetUserGuess ();
   void RemoveExtraSpaces ( string &guess );

public:
   //public methods
   Guess NextGuess ();
   set<string> GuessesMade () {
      return mGuesseesMade;
   }
   //use for valid letters printout
   string GetSecretPhrase(){
      return mSecretPhrase;
   }
   //use for init game display
   string GetRevealPhrase(){
      string reveal=  GuessChecker::RevealString( mSecretPhrase ,
         mGuesseesMade );
      RemoveExtraSpaces( reveal );
      return reveal;
   }




   ///constructors
   PhraseGame ( set<string> SourceWords , string SecretPhrase , int maxGuesses ) :
         mSourceWords( SourceWords ), mGuessesRemaining( maxGuesses ), mSecretPhrase(
               SecretPhrase ) {
      //add leters of the alphabet to SourceWords
      //for checking validity when guessing
      for ( char letter = 'a' ; letter <= 'z' ; letter++ ) {
         /*stringstream ss;
          ss << letter;
          mSourceWords.insert(string(ss.str()));*/
         mSourceWords.insert( swansonString::GetString( letter ) );

      }
   }
};

//string literals,  this "out of line" definition is to avoid globality with
// using #define
string PhraseGame::GUESS_PROMPT =
      "Enter a letter, or try to guess a word in the phrase,  or go for gold and guess the whole phrase \nWhat is your guess:";
string PhraseGame::NOT_IN_DICT =
      "There is no way for that guess to be right";
string PhraseGame::GUESSED_BEFORE = "You have already guessed that";
string PhraseGame::CORRECT_GUESS = "Good Job, that was in there";
string PhraseGame::WRONG_GUESS = "Nope,  Thats not it";


///////phrase game function definitions///////

PhraseGame::Guess PhraseGame::NextGuess () {
   PhraseGame::Guess myGuess;

   myGuess.guesesRemaining = mGuessesRemaining;

   //build reveal string without new guesses
   myGuess.revealedPhrase = GetRevealPhrase();

   //get input from user
   myGuess.guess = swansonInput::GetString( "what is your guess:" );
   RemoveExtraSpaces( myGuess.guess );
   swansonString::LowerCasePreserve( myGuess.guess );
   //determine guess is valid, &&|| correct

   myGuess.succesful = GuessChecker::GuessIsValid( myGuess.guess ,
         mSourceWords );

   if ( !myGuess.succesful ) {

      myGuess.correct = false;
      myGuess.message = NOT_IN_DICT;
      return myGuess;
   }

   if ( swansonUtil::ExistsInSet( myGuess.guess , mGuesseesMade ) ) {

      myGuess.succesful = false;
      myGuess.correct = false;
      myGuess.message = GUESSED_BEFORE;
      return myGuess;
   }
   /////////////^unsucessful guess^  VSuccesfull guessV ////

   mGuesseesMade.insert( myGuess.guess );

   myGuess.correct = GuessChecker::GuessIsEqual( myGuess.guess ,
         mSecretPhrase );


   if ( myGuess.correct ) {
      myGuess.message = CORRECT_GUESS;
      int occurances = swansonString::NumOccurances( mSecretPhrase ,
            myGuess.guess );
      if ( occurances > 1 ) {
         myGuess.message += " " + swansonString::GetString( occurances )
               + " times";
      }

      //word guessed already, and letter not in other words
      if ( myGuess.guess.size() == 1
            && occurances
                  <= swansonString::NumOccurances( myGuess.revealedPhrase ,
                        myGuess.guess ) )
         myGuess.correct = false;

   }

   if ( !myGuess.correct ) {
      myGuess.message = WRONG_GUESS;
      myGuess.guesesRemaining = --mGuessesRemaining;
   }


   //check for words where all letters have been guessed
   GuessChecker::AddWholeWordsToGuesses(mSecretPhrase, mGuesseesMade);

   //build reveal phrase //with new guesses
   myGuess.revealedPhrase = GetRevealPhrase();


   return myGuess;
}

void PhraseGame::RemoveExtraSpaces ( string &guess ) {
   while ( guess.at( 0 ) == ' ' ) {
      guess.erase( 0 , 1 );
   }
   while ( guess.at( guess.size() - 1 ) == ' ' ) {
      guess.erase( guess.size() - 1 , 1 );
   }
}

#endif /* PHRASEGAME_HPP_ */

//not self running
//controller advances the game, makes method calls
//maintain a game object struct,  can be used for display! by controller!

//need an IN SET method, put it in utils
