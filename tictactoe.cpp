/***********************************************************
 *
 * * Author: Brandon Swanson
 *
 * * Date Created: 07-17-2014
 *
 * * Last Modification Date: 07-17-2014
 *
 * * Filename:
 *
 *
 * * Overview: Week 4 Exercise Component #
 * *
 * * Input:
 * *
 * * Output:
 * *
 * ***********************************************************/

#include <iostream>
#include "SwansonObjects/menu.hpp"
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonLibs/swansonUtils.hpp"

using namespace std;

const int NOT_TAKEN = 0;
const int X = 1;
const int O = 2;

void demonstrateComponent ();
bool HardCodedWinCheck ( int player , int gameBoard[] );
bool GameCat(int gameBoard[]){
   for(int i=1;i<10;i++){
      if(gameBoard[i]==NOT_TAKEN) return false;
   }
   return true;
}



int main () {
   string Intro = "This is One Dimensional Tic Tac Toe";
   MenuItem myExerciseComp( demonstrateComponent , "title" , Intro );

   while(!swansonInput::yesNo("are you ready for tic tac toe"))

   myExerciseComp.ItemSelected();

}

void showGameBoard ( int gameBoard[] ) {
   swansonUtil::ClearScreen();
   for ( int index = 1 ; index < 10 ; index++ ) {
      if ( gameBoard[index] == NOT_TAKEN ) {
         cout << "  " << index;
      } else if ( gameBoard[index] == X ) {
         cout << "  X";
      } else {
         cout << "  O";
      }
      if ( index % 3 == 0 )
         cout << endl << endl;
   }
}

void demonstrateComponent () {

   int myGameBoard[10];
   bool Xturn = true;
   int selection;
   int player;

   for ( int index = 1 ; index < 10 ; index++ ) {
      myGameBoard[index] = NOT_TAKEN;
   }

   do {

      do {
         showGameBoard( myGameBoard );
         if ( Xturn )
            cout << "it is X's turn";
         else
            cout << "it is O's turn, ";

         selection = swansonInput::GetInt(
               "pick a position that hasnt been chosen[1-9]" , 1 , 9 );
      } while ( myGameBoard[selection] != NOT_TAKEN );

      if ( Xturn )
         myGameBoard[selection] = X;
      else
         myGameBoard[selection] = O;

      (Xturn)?player=X:player=O;
      Xturn = !Xturn;

      //only need to check one, X can't win on O's turn
   } while ( !HardCodedWinCheck( player, myGameBoard ) && !GameCat(myGameBoard) );

   showGameBoard(myGameBoard);
   if(GameCat(myGameBoard)) cout << "game is cat";
   else cout <<
         ( (player==X)? "Player X has won it!" : "Player O has won it!")
         << endl;

}

bool HardCodedWinCheck ( int player , int gameBoard[] ) {

   //rows////
   if ( gameBoard[1] == player && gameBoard[2] == player
         && gameBoard[2] == player )
      return true;
   if ( gameBoard[4] == player && gameBoard[5] == player
         && gameBoard[6] == player )
      return true;
   if ( gameBoard[7] == player && gameBoard[8] == player
         && gameBoard[9] == player )
      return true;
   //collums///
   if ( gameBoard[1] == player && gameBoard[4] == player
         && gameBoard[7] == player )
      return true;
   if ( gameBoard[2] == player && gameBoard[5] == player
         && gameBoard[8] == player )
      return true;
   if ( gameBoard[3] == player && gameBoard[6] == player
         && gameBoard[9] == player )
      return true;
   //diags//
   if ( gameBoard[1] == player && gameBoard[5] == player
         && gameBoard[9] == player )
      return true;
   if ( gameBoard[3] == player && gameBoard[5] == player
         && gameBoard[7] == player )
      return true;

   //no matching sets of 3
   return false;
}
