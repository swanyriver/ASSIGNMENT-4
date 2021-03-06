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
#include <cstdlib>

#include "PhraseGame.hpp"
#include "PreFabDictionary.hpp"
#include "hangmanDisplay.hpp"
#include "SwansonObjects/Dictionary.hpp"
#include "SwansonObjects/menu.hpp"
#include "SwansonObjects/ArgReader.hpp"
#include "SwansonObjects/BlackBoxTesters.hpp"


using namespace std;

///global variables /////////////////////
const int MAX_GUESSES = 7;
const int MAX_WORDS = 5;
const int MIN_WORDS = 3;
const int MAX_WORD_LENGTH = 6;

//global control variables //
bool mDebugOn = false;
bool mPharseTestOn = true;
const string DEBUG = "-d";
const string SIMPLE_MODE = "-s";
const string PHRASE_GEN = "-p";

//string literals
const string STARTGAME_MESSAGE = "Welcome to the Game, Good Luck";
const string WON_GAME = "Congratulations, you got the Secret Phrase";
const string LOST_GAME =
      "You were close, but you didn't guess the Secret Phrase";
const string DICT_INTRO =
      "The words in this game will be chosen from a dictionary\nYou can play with the regular dictionary or use a book for fun flavor,\neven add your own file\n";
const string CLEAR_INTRO =
      "This games uses a system call to clear the screen\nif you prefer not then it can do this in an alternative mode";
const string HOW_MANY_WORDS = "Now Playing with ";
//for entering your own dictionary
const string FILENAME_IN =
      "what is the name and full path of your file (myfile.txt)\nI am trusting you to get it exactly right:";
const string HOW_MANY_LETTERS =
      "What do you want the length of the longest words in the game to be:";
const int IN_MIN_LETTER = 3;
const int IN_MAX_LETTER = 15;
//todo add menu item text here

//global objects//////
Dictionary myDict(false);

Menu DictionaryMenu( DictionaryBanner() + DICT_INTRO );
Menu ClearScreenMenu( SystemBanner() + CLEAR_INTRO );
Menu myMenu( Banner() );

///fuction declarations /////////////////

void display ( int guessRemaining , string revealPhrase , string message ,
      set<string> GuessesMade );

//menu item declarations
void PlayGame ();

//dictionary choices
void showDictionaryMenu () {
   DictionaryMenu.showMenu();
}
void usePreFabDict () {
   myDict = Dictionary( PreFabDict::getSet() );

   myMenu.SetIntro(
         Banner() + HOW_MANY_WORDS
               + swansonString::GetString( myDict.NumWords() ) + " words!!!" );

   if ( myDict.Filled() ) {
      cout << endl
            << "something strange has happend, we had an empty dictionary"
            << " but don't worry, we can still play with my limited stored vocabulary";
      cout << endl << "press anything to continue:";
      getchar();
   } else {
      cout << endl
            << "something has gone very wrong here, we have no words, we cannot play";
      cout << endl << "press anything to exit:";
      exit( 1 );
   }
}

void PlainDict () {
   //Constructs a dict of MaxWordLength letter long words
   myDict = Dictionary( MAX_WORD_LENGTH );
   myMenu.SetIntro(
         Banner() + HOW_MANY_WORDS
               + swansonString::GetString( myDict.NumWords() ) + " words!!!" );

   if ( !myDict.Filled() )
      usePreFabDict();
}

void MakeThemeDictionary ( const string filename , const int maxLenght =
      MAX_WORD_LENGTH ) {
   myDict = ThemeDictionary( maxLenght , filename );
   myMenu.SetIntro(
         Banner() + HOW_MANY_WORDS
               + swansonString::GetString( myDict.NumWords() ) + " words!!!" );
   if ( !myDict.Filled() )
      usePreFabDict();
}

void UserDict () {
   string filename = swansonInput::GetString( FILENAME_IN );
   int maxLenght = swansonInput::GetInt( HOW_MANY_LETTERS , IN_MIN_LETTER ,
         IN_MAX_LETTER );

   MakeThemeDictionary( filename , maxLenght );
}
void MobyDict () {
   //construcs a dict of MaxWordLength letter long words
   //from unformatted file "moby.txt"
   MakeThemeDictionary( "moby.txt" );
}
void FriendsDict () {
   //construcs a dict of 9 letter long words
   //from unformatted file "friends.txt"
   MakeThemeDictionary( "friends.txt" , 9);
}

//clear screen choices
void showClearScreenMenu () {
   ClearScreenMenu.showMenu();
}

void HackyClearSelected () {
   ClearScreen = HackClearScreen; //alternate method;
   myMenu.setClear(HackClearScreen);
   DictionaryMenu.setClear(HackClearScreen);
   ClearScreenMenu.setClear(HackClearScreen);
}
void SystemClearSelected () {
   ClearScreen = swansonUtil::ClearScreen;
   myMenu.setClear(swansonUtil::ClearScreen);
   DictionaryMenu.setClear(swansonUtil::ClearScreen);
   ClearScreenMenu.setClear(swansonUtil::ClearScreen);
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////int main()/////
//////////////////////////////////////////////////////PROGRAM BEGINS HERE////
/////////////////////////////////////////////////////////////////////////////
int main ( int argc , char* argv[] ) {

   //test ascii art
   /*cout << SystemBanner(); getchar();
   cout << DictionaryBanner(); getchar();
   cout << Banner(); getchar();*/

   ///process command line arguments//////////////
   //string and bool pointer combo, bool will be set true if flag is in argsv[]
   ARGinAttor::ControlFlag debugFlag = {DEBUG, &mDebugOn};
   ARGinAttor::ControlFlag phraseFlag = {PHRASE_GEN, &mPharseTestOn};
   list<ARGinAttor::ControlFlag> flags;
   flags.push_back(debugFlag);
   flags.push_back(phraseFlag);
   //args and ControlFlags passed to ARGinAttor
   ARGinAttor myARGinAttor( argc , argv, flags );

   //check Arginators arguement set<string> for -s SIMPLE MODE
   if(myARGinAttor.ArgumentPassedIn(SIMPLE_MODE)){
      HackyClearSelected();
   }
   ///finished command line arguments//////////////

   //set clearscreen pointer //system call by default
   //except for menu //to avoid failure to launch //can be switched via menu
   ClearScreen = swansonUtil::ClearScreen;

   //initializations
   swansonUtil::SeedRandom();
   PlainDict(); //full dictionary by default
   myMenu.demoAllItem = false;

   //dict menu
   DictionaryMenu.demoAllItem = false;
   DictionaryMenu.menuRepeat = false;
   MenuItem plain( PlainDict , "normal dictionary" ,
         "loading the dictionary in" );
   plain.itemRepeat = false;
   DictionaryMenu.addItem( plain );

   MenuItem moby( MobyDict , "Moby Dick Words" , "loading Moby Dick in" );
   moby.itemRepeat = false;
   DictionaryMenu.addItem( moby );

   MenuItem friends( FriendsDict , "Friends TV Words (play like its 1995!!)" , "loading in Chandler, Joey, Ross, Monica, Pheoby, and Rachel" );
   friends.itemRepeat = false;
   DictionaryMenu.addItem( friends );

   MenuItem user( UserDict , "Make Your Own \"MyDictionary.txt\"" ,
         "This is exciting, what kind of words do you have to play with today?" );
   user.itemRepeat = false;
   DictionaryMenu.addItem( user );

   //clear menu
   ClearScreenMenu.menuRepeat = false;
   ClearScreenMenu.demoAllItem = false;
   MenuItem onItem( SystemClearSelected , "Use System()" ,
         "system calibrated" );
   onItem.itemRepeat = false;
   ClearScreenMenu.addItem( onItem );
   MenuItem offItem( HackyClearSelected , "Use Alternate Method" ,
         "REROUTING BITS AND BYTES" );
   offItem.itemRepeat = false;
   ClearScreenMenu.addItem( offItem );

   MenuItem DictMenuItem( showDictionaryMenu , "Dictionary Settings" , "" );
   MenuItem ClearMenuItem( showClearScreenMenu , "System() Config" , "" );
   DictMenuItem.hasIntro = false;
   ClearMenuItem.hasIntro = false;
   DictMenuItem.itemRepeat = false;
   ClearMenuItem.itemRepeat = false;


   MenuItem playGameItem( PlayGame , "Play Game" , "intro" , "Play Again" );
   playGameItem.hasIntro = false;
   playGameItem.itemRepeat = true;

   myMenu.addItem( playGameItem );  // [1] play game
   myMenu.addItem( DictMenuItem );  // [2] dictionary settings
   myMenu.addItem( ClearMenuItem ); // [3] system config
                                    // [4] exit menu

   myMenu.showMenu();

   //PlayGame();

   return 0;
}

void PlayGame () {

   //////testing phrase generation
   if(mPharseTestOn){
      DictionaryTester::MakePhrases(myDict);
   }

   /////////////end test

   //local variables/objects
   PhraseGame::Guess nextGuess;

   //use dictionary to make phrase
   string phrase;
   int numWords = swansonUtil::GetRandomInRange( MIN_WORDS , MAX_WORDS );
   for ( int i = 0 ; i < numWords ; ++i ) {
      phrase += myDict.GetRandomWord() + " ";
   }
   phrase.erase( phrase.length() - 1 , 1 ); //remove extra space

   //testing line wrap
   //phrase = "this is my big dumb very long long long string to bge guessed lets see how it goes it is much longer than it should be";

   //instance a new game object
   PhraseGame myGame( myDict.GetSet() , phrase , MAX_GUESSES );

   //initialize game state and display welcome screen
   display( MAX_GUESSES , myGame.GetRevealPhrase() , STARTGAME_MESSAGE ,
         myGame.GuessesMade() );
   //help text for debug
   if ( mDebugOn ) DebugDisplay(myGame.GetSecretPhrase());

   do {
      //get a guess from user
      nextGuess = myGame.NextGuess();

      //display results
      display( nextGuess.guesesRemaining , nextGuess.revealedPhrase ,
            nextGuess.message , myGame.GuessesMade() );
      //help text for debug
      if ( mDebugOn ) DebugDisplay(myGame.GetSecretPhrase());

      //keep guessing if not solved, or remaining guesses
   } while ( nextGuess.revealedPhrase != myGame.GetSecretPhrase()
         && nextGuess.guesesRemaining > 0 );

   //output final results
   if ( myGame.GetRevealPhrase() == myGame.GetSecretPhrase() ) {
      display( nextGuess.guesesRemaining , nextGuess.revealedPhrase , WON_GAME ,
            myGame.GuessesMade() );
   } else {
      display( nextGuess.guesesRemaining , nextGuess.revealedPhrase ,
            LOST_GAME , myGame.GuessesMade() );
      EndGameDisplay( phrase , myGame.GuessesMade() );
   }

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

