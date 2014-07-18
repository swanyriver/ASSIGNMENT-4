/*
 * hangmanDisplay.hpp
 *
 *  Created on: Jul 18, 2014
 *      Author: Brandon
 */

#ifndef HANGMANDISPLAY_HPP_
#define HANGMANDISPLAY_HPP_

#include <set>
#include <iostream>
#include <string>
#include "RecursiveWordChecker.hpp"
using namespace std;

///special display/////////////////

const int WIDTH_DISPLAY = 75;
const int SIDEBAR_DISPLAY = 21;

#define LINE_SEPERATE "***************************************************************************"
#define SECRET_PHRASE_LABEL "*   SECRET PHRASE   * "
#define GUESS_MADE_LABEL "*   GUESSES MADE    * "
#define LETTERS_LABEL "* LETTERS AVAILABLE * "
#define GUESS_REMAINING_LABEL "* GUESSES REMAINING * "

#define LETTERS_UNREAVEALED_LABEL "*  WHAT'S MISSING   * "
#define REVEAL_WORD_LABEL         "* SECRET PHRASE WAS * "

//////////////////////////////

//refresh terminal screen
void (*ClearScreen) ();

/**************************************************************
 *
 * * Entry:none
 *
 * * Exit: 100 return characters to output stream
 *
 * * Purpose: obscure secret word
 *
 * ***************************************************************/
void HackClearScreen () {
   string clearScrn = "";
   clearScrn.append( 100 , '\n' );
   std::cout << clearScrn;
}

/**************************************************************
 *
 * Entry: string with ' ' as delimiter
 *
 * Exit: multi line strings
 *
 * Purpose: format strings to word wrap on multi lines
 *
 * ***************************************************************/

string LineWrap ( string output , int sideBarWidth , int DisplayWidth ) {
   //cout << "coming into linewrap with:" << output << endl;

   if ( output.length() < DisplayWidth ) {
      output.append( DisplayWidth - output.size() - 1 , ' ' );
      output += "*";
      return output;
   } else {
      int lastSpace = output.find_last_of( ' ' , DisplayWidth - 1 );
      string thisLine = output.substr( 0 , lastSpace );
      output.erase( 0 , lastSpace );

      //cout << "output:" << output << endl << "thisline:" << thisLine << endl;
      //cout << "remaining space:" << DisplayWidth -  thisLine.size() - 1;
      //getchar();

      thisLine.append( DisplayWidth - thisLine.size() - 1 , ' ' );
      thisLine += "*\n";

      output.insert( 0 , sideBarWidth , '*' );

      return thisLine + LineWrap( output , sideBarWidth , DisplayWidth );
   }
}

/**************************************************************
 *
 * Entry: none
 *
 * Exit: outputs the letters reveled in the secret word and guesses remaining
 *
 * Purpose: inform player 2 of his status in the game
 *
 * ***************************************************************/

void display ( int guessRemaining , string revealPhrase , string message ,
      set<string> guessesMade ) {

   string secretPhraseLine, lettersLine, guessesLine, guessRemainingLine;
   string lettersRemainingLine, phraseRevealLine;
   string messageLine;
   string wordGuessesMadeLine;

   //build secret word string
   secretPhraseLine = SECRET_PHRASE_LABEL;
   secretPhraseLine = LineWrap( secretPhraseLine + revealPhrase ,
         SIDEBAR_DISPLAY , WIDTH_DISPLAY );

   /*cout << endl << secretPhraseLine << endl;
    getchar();*/

   //build letters available & guesses made string
   lettersLine = LETTERS_LABEL;
   guessesLine = GUESS_MADE_LABEL;
   for ( char currentChar = 'a' ; currentChar <= 'z' ; currentChar++ ) {

      //for each letter place a letter or empty space, acording to guesses
      if ( swansonUtil::ExistsInSet( swansonString::GetString( currentChar ) ,
            guessesMade ) ) {
         guessesLine.push_back( currentChar );
         guessesLine += " ";
         lettersLine += "  ";
      } else {
         lettersLine.push_back( currentChar );
         lettersLine += " ";
         guessesLine += "  ";
      }
   }
   guessesLine += "*";
   lettersLine += "*";

   /*cout << endl << guessesLine << endl;
    cout << endl << lettersLine << endl;
    getchar();*/

   wordGuessesMadeLine.append( SIDEBAR_DISPLAY , '*' );
   string guesses;
   set<string>::iterator lookup = guessesMade.begin();
   for ( int x = 0 ; x < guessesMade.size() ; x++ ) {
      if ( (*lookup).size() > 1 )
         guesses += *lookup + ", ";
      lookup++;
   }
   if ( guesses.empty() )
      wordGuessesMadeLine.append( WIDTH_DISPLAY - SIDEBAR_DISPLAY , '*' );
   else {
      guesses.erase( guesses.size() - 2 , 2 ); //remove final ", "
      wordGuessesMadeLine = LineWrap( wordGuessesMadeLine + " " + guesses ,
            SIDEBAR_DISPLAY , WIDTH_DISPLAY );
   }
   //allow display to grow if words get larger than one line
   //they will be alpha sorted

   //build guesses remaining string
   guessRemainingLine = GUESS_REMAINING_LABEL;
   for ( int i = 0 ; i < guessRemaining ; i++ ) {
      guessRemainingLine += "? ";
   }
   guessRemainingLine = LineWrap( guessRemainingLine , SIDEBAR_DISPLAY ,
         WIDTH_DISPLAY );

   /* cout << endl << guessRemainingLine << endl;
    getchar();*/

   //build message line
   messageLine = LINE_SEPERATE;
   if ( !message.empty() ) {
      message = "  " + message + "  ";
      int pos = WIDTH_DISPLAY / 2.0 - message.length() / 2.0;
      messageLine.replace( pos , message.size() , message );
   }

   /*cout << endl << messageLine << endl;
    getchar();*/

   //output display
   ClearScreen();
   cout << LINE_SEPERATE << endl;
   cout << LINE_SEPERATE << endl;
   cout << secretPhraseLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << lettersLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << guessesLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << wordGuessesMadeLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << guessRemainingLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << messageLine << endl;
   cout << LINE_SEPERATE << endl;

}

void EndGameDisplay ( string secretPhrase , set<string> guesses ) {

   //todo construct special display

   string LettersMissedLine = LETTERS_UNREAVEALED_LABEL;
   string secretPhraseLine = REVEAL_WORD_LABEL + secretPhrase;

   set<string> missed = GuessChecker::ElementsMissed( secretPhrase , guesses );

   set<string>::iterator lookup = missed.begin();
   for ( int x = 0 ; x < missed.size() ; x++ ) {
      LettersMissedLine += *lookup++ + " ";
   }

   LettersMissedLine = LineWrap( LettersMissedLine , SIDEBAR_DISPLAY ,
         WIDTH_DISPLAY );
   secretPhraseLine = LineWrap( secretPhraseLine , SIDEBAR_DISPLAY ,
         WIDTH_DISPLAY );

   cout << secretPhraseLine << endl;
   cout << LINE_SEPERATE << endl;
   cout << LettersMissedLine << endl;
   cout << LINE_SEPERATE << endl;

}

/**************************************************************
 *
 * * Entry: none
 *
 * * Exit: a 6 line string, ascii art for title
 *
 * * Purpose: create output for program header
 *
 * ***************************************************************/
string Banner () {
   ////TEXT GENERATED BY /// http://patorjk.com/software/taag/
   string Banner;
   Banner = "   _____                    _    __          __           _ \n";
   Banner += "  / ____|                  | |   \\ \\        / /          | |\n";
   Banner +=
         " | (___   ___  ___ _ __ ___| |_   \\ \\  /\\  / /__  _ __ __| |\n";
   Banner +=
         "  \\___ \\ / _ \\/ __| '__/ _ \\ __|   \\ \\/  \\/ / _ \\| '__/ _` |\n";
   Banner += "  ____) |  __/ (__| | |  __/ |_     \\  /\\  / (_) | | | (_| |\n";
   Banner +=
         " |_____/ \\___|\\___|_|  \\___|\\__|     \\/  \\/ \\___/|_|  \\__,_|\n";

   return Banner;
}

#endif /* HANGMANDISPLAY_HPP_ */
