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

using namespace std;

///global variables /////////////////////



///fuction declarations /////////////////

void display(PhraseGame::Guess guess);

//todo add arg reader for -s and -d   (clear screen off, and dictionary off)
//todo add menu for selecting theme dictionary, or entering your own


int main(int argc , char* argv[]){


   //PreFabDict myFab;
   PhraseGame myGame(PreFabDict::getSet(), "my secret phrase", 8);


   do {
      PhraseGame::Guess nextGuess = myGame.NextGuess();

      display(nextGuess);
   } while (swansonInput::yesNo("keep guessing"));



   return 0;
}

string AllItemsInSet(set<string> myset){
   string oString;
   //set<string>::iterator lookup;
   set<string>::iterator lookup;
   lookup = myset.begin();
   for (int i=0;i<myset.size();i++){
      oString+=*lookup + "/";
      lookup++;
   }

   return oString;

}


void display(PhraseGame::Guess guess){
   //blackboxing
   cout << endl << "guesss is:" << guess.guess << endl;
   cout << endl << "guesses remaing:" << guess.GuesesRemaining;
   cout << endl << "guesses valid:" << guess.succesful;
   cout << endl <<"the phrase set contains: " << AllItemsInSet(guess.PhraseSet);
   cout << endl <<"the guess set contains: " << AllItemsInSet(guess.GuessSet);
   cout << endl <<"the source set contains: " << AllItemsInSet(guess.SourceSet);
}


