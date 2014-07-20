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

void demonstrateComponent ();
bool TwodHasWon ( int player , int gameBoard[][3] );
void showGameBoard ( int gameBoard[][3] );

const int NOT_TAKEN = 0;
const int X = 1; //spaced for addadive set checking
const int O = 10;

bool GameCat(int gameBoard[][3]){
   for ( int index = 0 ; index < 3 ; index++ ) {
      for ( int subIndex = 0 ; subIndex < 3 ; subIndex++ ) {
         if(gameBoard[index][subIndex] == NOT_TAKEN) return false;
      }
   }
   return true;
}

int main () {
   string Intro = "This is Two Dimensional Tic Tac Toe";
   MenuItem myExerciseComp( demonstrateComponent , "title" , Intro );



   myExerciseComp.ItemSelected();

}

void demonstrateComponent () {

   cout << "are your ready?";
   getchar();

   int myGameBoard[3][3];
   bool Xturn = true;
   int selection;
   int player;
   int SIndex, S_SubIndex;

   //init
   for ( int index = 0 ; index < 3 ; index++ ) {
      for ( int subIndex = 0 ; subIndex < 3 ; subIndex++ ) {
         myGameBoard[index][subIndex] = NOT_TAKEN;
      }
   }

   do {

      do {
         showGameBoard( myGameBoard );
         if ( Xturn )
            cout << "it is X's turn";
         else
            cout << "it is O's turn, ";

         selection = swansonInput::GetInt(
               "pick a position that hasnt been chosen[1-9]" , 1 , 9 ) - 1;
         SIndex = selection / 3;
         S_SubIndex = selection % 3;
      } while ( myGameBoard[SIndex][S_SubIndex] != NOT_TAKEN );

      if ( Xturn )
         myGameBoard[SIndex][S_SubIndex] = X;
      else
         myGameBoard[SIndex][S_SubIndex] = O;

      (Xturn) ? player = X : player = O;
      Xturn = !Xturn;

      //only need to check one, X can't win on O's turn
   } while ( !TwodHasWon( player , myGameBoard ) );
   //} while ( true );

   /*cout << ((player == X) ? "Player X has won it!" : "Player O has won it!")
         << endl;*/

   for ( int index = 0 ; index < 3 ; index++ ) {
      for ( int subIndex = 0 ; subIndex < 3 ; subIndex++ ) {
         myGameBoard[index][subIndex] = NOT_TAKEN;
      }
   }
}

void showGameBoard ( int gameBoard[][3] ) {
   swansonUtil::ClearScreen();

   for ( int index = 0 ; index < 3 ; index++ ) {
      for ( int subIndex = 0 ; subIndex < 3 ; subIndex++ ) {
         if ( gameBoard[index][subIndex] == NOT_TAKEN ) {
            cout << "  " << index * 3 + subIndex + 1;
         } else if ( gameBoard[index][subIndex] == X ) {
            cout << "  X";
         } else {
            cout << "  O";
         }
      }
      //end of each row
      cout << endl << endl;
   }
}

bool TwodHasWon ( int player , int gameBoard[][3] ) {

   const int ALL_Os = O*3; //3
   const int ALL_Xs = X*3; //30

   int setOfThree = 0;

   //check rows
   for ( int rows = 0 ; rows < 3 ; rows++ ) {
      setOfThree = 0;
      for ( int collumn = 0 ; collumn < 3 ; collumn++ ) {
         setOfThree += gameBoard[rows][collumn];
      }
      if ( setOfThree == ALL_Os || setOfThree == ALL_Xs )
         return true;
   }

   //check collumns
   for ( int collumn = 0 ; collumn < 3 ; collumn++ ) {
      setOfThree = 0;
      for ( int rows = 0 ; rows < 3 ; rows++ ) {
         setOfThree += gameBoard[rows][collumn];
      }
      if ( setOfThree == ALL_Os || setOfThree == ALL_Xs )
         return true;
   }

   //check diaganols
   setOfThree = 0;
   setOfThree += gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2];
   if ( setOfThree == ALL_Os || setOfThree == ALL_Xs )
      return true;

   setOfThree = 0;
   setOfThree += gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0];
   if ( setOfThree == ALL_Os || setOfThree == ALL_Xs )
      return true;

   //no matching set found
   return false;
}
