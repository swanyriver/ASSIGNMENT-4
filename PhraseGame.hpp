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
      string errorMsg;
      string guess;
      bool correct;
      int GuesesRemaining;
      //int occurences; //todo implement later
      string mRevealedPhrase;

      //for testing
      set<string> PhraseSet;
      set<string> GuessSet;
      set<string> SourceSet;
   };

   set<string> mGuesseesMade;

private:

   //error messages
   //not letter // not word //or a word in it is not in the dictionary
   static string NOT_IN_DICT;

   //global variables
   int mGuessesRemaining;
   string mSecretPhrase;
   set<string> mSourceWords;
   set<string> mPhraseWords;


   //private construction method
   set<string> PopulatePhraseSet ( string secretPhrase );

   //internal methods
   string GetRevealedPhrase ();
   string GetUserGuess ();
   bool CorrectGuess ( string guess );

public:
   //public methods
   Guess NextGuess ();
   set<string> GuessesMade(){ return mGuesseesMade; };

   ///constructors
   PhraseGame ( set<string> SourceWords , string SecretPhrase , int maxGuesses ) :
         mSourceWords( SourceWords ), mPhraseWords(
               PopulatePhraseSet( SecretPhrase ) ), mGuessesRemaining(
               maxGuesses ), mSecretPhrase( SecretPhrase ) {
      //add leters of the alphabet to SourceWords
      //for checking validity when guessing
      for (char letter = 'a'; letter <= 'z'; letter++){
         stringstream ss;
         ss << letter;
         mSourceWords.insert(string(ss.str()));
      }
   }
};

string PhraseGame::NOT_IN_DICT = "There is no possible way for that guess to be right so I won't count it against you";


///////phrase game function definitions///////

PhraseGame::Guess PhraseGame::NextGuess () {
   PhraseGame::Guess myGuess;

   //get input from user
   myGuess.guess = swansonInput::GetString("what is your guess:");
   swansonString::LowerCasePreserve(myGuess.guess);
   //determine guess is valid, &&|| correct

   myGuess.succesful = GuessChecker::guessIsValid(myGuess.guess, mSourceWords);


   //bool succesful;
   //string errorMsg;
   //string mRevealedPhrase;
   /////////////unsucessful guess

   //string guess;
   //bool correct;
   mGuesseesMade.insert(myGuess.guess);
   myGuess.GuesesRemaining = --mGuessesRemaining;
   //string mRevealedPhrase;
   ///////////////succesful input


   //int occurences; //todo implement later


   //for testing
   myGuess.SourceSet = mSourceWords;
   myGuess.PhraseSet = mPhraseWords;
   myGuess.GuessSet = mGuesseesMade; //actually needed for display

   return myGuess;
}



string PhraseGame::GetRevealedPhrase () {
   return " part 0f -re-v-ea-ed ph-ra-e";

}

/*string PhraseGame::GetUserGuess () {
   return
}*/

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
   swansonString::SeperateWords(secretPhrase,words);
   while(!words.empty()){
      string nextWord = words.front();
      words.pop_front();
      phraseSet.insert(nextWord);
      int position =0;
      while(position<nextWord.size()){
         phraseSet.insert(nextWord.substr(position++,1));
      }
   }

   return phraseSet;

}

#endif /* PHRASEGAME_HPP_ */

//not self running
//controller advances the game, makes method calls
//maintain a game object struct,  can be used for display! by controller!

//need an IN SET method, put it in utils
