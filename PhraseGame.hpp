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

      //for testing
      set<string> PhraseSet;
      set<string> GuessSet;
      set<string> SourceSet;
   };

   set<string> mGuesseesMade;

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
   set<string> mPhraseWords;  // todo maybe depricate! not used

   //private construction method
   set<string> PopulatePhraseSet ( string secretPhrase );

   //internal methods
   string GetUserGuess ();
   bool CorrectGuess ( string guess );
   void RemoveExtraSpaces ( string &guess );

public:
   //public methods
   Guess NextGuess ();
   set<string> GuessesMade () {
      return mGuesseesMade;
   }
   ;
   //todo possibly deprecate in favor of persitent string in display object
   //this will avoid alpha sorted answers

   ///constructors
   PhraseGame ( set<string> SourceWords , string SecretPhrase , int maxGuesses ) :
         mSourceWords( SourceWords ), mPhraseWords(
               PopulatePhraseSet( SecretPhrase ) ), mGuessesRemaining(
               maxGuesses ), mSecretPhrase( SecretPhrase ) {
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

string PhraseGame::GUESS_PROMPT =
      "Enter a letter, or try to guess a word in the phrase,  or go for gold and guess the whole phrase \nWhat is your guess:";
string PhraseGame::NOT_IN_DICT =
      "There is no possible way for that guess to be right so I won't count it against you";
string PhraseGame::GUESSED_BEFORE = "You have already guessed that";
string PhraseGame::CORRECT_GUESS = "Good Job, that was in there"; //todo adapt to do printf guess and
string PhraseGame::WRONG_GUESS = "Nope,  Thats not it";
//todo  GUESS CORRECT,  GUESS INCORECT

///////phrase game function definitions///////

PhraseGame::Guess PhraseGame::NextGuess () {
   PhraseGame::Guess myGuess;

   //for testing
   myGuess.SourceSet = mSourceWords;
   myGuess.PhraseSet = mPhraseWords;

   myGuess.guesesRemaining = mGuessesRemaining;

   //get input from user
   myGuess.guess = swansonInput::GetString( "what is your guess:" );
   RemoveExtraSpaces( myGuess.guess );
   swansonString::LowerCasePreserve( myGuess.guess );
   //determine guess is valid, &&|| correct

   myGuess.succesful = GuessChecker::guessIsValid( myGuess.guess ,
         mSourceWords );

   if ( !myGuess.succesful ) {
      //build reveal string
      myGuess.revealedPhrase = GuessChecker::RevealString( mSecretPhrase ,
            mGuesseesMade );
      RemoveExtraSpaces( myGuess.revealedPhrase );

      myGuess.correct = false;
      myGuess.message = NOT_IN_DICT;
      return myGuess;
   }

   if ( swansonUtil::ExistsInSet( myGuess.guess , mGuesseesMade ) ) {
      //build reveal string
      myGuess.revealedPhrase = GuessChecker::RevealString( mSecretPhrase ,
            mGuesseesMade );
      RemoveExtraSpaces( myGuess.revealedPhrase );

      myGuess.succesful = false;
      myGuess.correct = false;
      myGuess.message = GUESSED_BEFORE;
      return myGuess;
   }
   /////////////^unsucessful guess^  VSuccesfull guessV ////

   mGuesseesMade.insert( myGuess.guess );

   myGuess.correct = GuessChecker::guessIsEqual( myGuess.guess ,
         mSecretPhrase );

   //build reveal string with new guesses
   myGuess.revealedPhrase = GuessChecker::RevealString( mSecretPhrase ,
         mGuesseesMade );
   RemoveExtraSpaces( myGuess.revealedPhrase );

   if ( !myGuess.correct ) {
      myGuess.message = WRONG_GUESS;
      myGuess.guesesRemaining = --mGuessesRemaining;
   } else {
      myGuess.message = CORRECT_GUESS;
      int occurances = swansonString::NumOccurances( mSecretPhrase ,
            myGuess.guess );
      if ( occurances > 1 ) {
         myGuess.message += " " + swansonString::GetString( occurances )
               + " times";
      }
   }

   //string mRevealedPhrase;  //todo build method in recurse  //use WORDCHECKER
   myGuess.revealedPhrase = GuessChecker::RevealString( mSecretPhrase ,
         mGuesseesMade );
   RemoveExtraSpaces( myGuess.revealedPhrase );

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

bool PhraseGame::CorrectGuess ( string guess ) {
   return true; //use REcuse Checker
}

//construction method
set<string> PhraseGame::PopulatePhraseSet ( string secretPhrase ) {
   //use recurion, populate the set
   set<string> phraseSet;

   //add whole phrase
   phraseSet.insert( secretPhrase );

   //add individual words and letters //iterative
   list<string> words;
   swansonString::SeperateWords( secretPhrase , words );
   while ( !words.empty() ) {
      string nextWord = words.front();
      words.pop_front();
      phraseSet.insert( nextWord );
      int position = 0;
      while ( position < nextWord.size() ) {
         phraseSet.insert( nextWord.substr( position++ , 1 ) );
      }
   }

   return phraseSet;

}

#endif /* PHRASEGAME_HPP_ */

//not self running
//controller advances the game, makes method calls
//maintain a game object struct,  can be used for display! by controller!

//need an IN SET method, put it in utils
