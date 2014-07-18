/*
 * phrase.cpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#include <string>
#include <iostream>

#include "PhraseGame.hpp"
#include "PreFabDictionary.hpp"


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




void display(PhraseGame::Guess guess){
   //blackboxing
   cout << "guesss is" << guess.guess << endl;

}


