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
bool TwodHasWon ( int **gameBoard );
void showGameBoard ( int **gameBoard );
bool CatGame(int **gameBoard  );

const int NOT_TAKEN = 0;
const int X = 1; //spaced for addadive set checking
const int O = 10;

int main () {
   string Intro = "This is Dynamic Two Dimensional Tic Tac Toe";
   MenuItem myExerciseComp( demonstrateComponent , "title" , Intro );

   myExerciseComp.ItemSelected();

}

int boardSize;

void demonstrateComponent () {

   boardSize = swansonInput::GetInt( "how big should the board be:" , 3 , 9 );

   bool Xturn = true;
   int selection;
   int player;
   int SIndex, S_SubIndex;

   //Double Dynamic initializaton found at StackOverFlow, Explained below
   //SO.com/questions/16001803/pointer-to-pointer-dynamic-two-dimensional-array

   //dynamic array of pointer size boardsize
   int **myGameBoard = new int*[boardSize];

   for ( int i = 0 ; i < boardSize ; ++i ) {
      myGameBoard[i] = new int[boardSize];
      // myGameBoard[x][] pointer is now pointing to dynamic array of ints;
   }

   for ( int index = 0 ; index < boardSize ; index++ ) {
      for ( int subIndex = 0 ; subIndex < boardSize ; subIndex++ ) {
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
               "pick a position that hasnt been chosen" , 1 ,
               boardSize * boardSize ) - 1;
         SIndex = selection / boardSize;
         S_SubIndex = selection % boardSize;
      } while ( myGameBoard[SIndex][S_SubIndex] != NOT_TAKEN );

      if ( Xturn )
         myGameBoard[SIndex][S_SubIndex] = X;
      else
         myGameBoard[SIndex][S_SubIndex] = O;

      (Xturn) ? player = X : player = O;
      Xturn = !Xturn;

      //only need to check one, X can't win on O's turn
   } while ( !TwodHasWon( myGameBoard ) && !CatGame(myGameBoard));

   showGameBoard(myGameBoard);
   if(TwodHasWon(myGameBoard) ){
      cout << ((player == X) ? "Player X has won it!" : "Player O has won it!")
         << endl;
   }
   else cout << "the board is CAT" << endl;


}

void showGameBoard ( int **gameBoard ) {
   swansonUtil::ClearScreen();

   for ( int index = 0 ; index < boardSize ; index++ ) {
      for ( int subIndex = 0 ; subIndex < boardSize ; subIndex++ ) {
         if ( gameBoard[index][subIndex] == NOT_TAKEN ) {
            int position = index * boardSize + subIndex + 1;
            cout << "  " << position;
            if ( position < 10 )
               cout << " ";
         } else if ( gameBoard[index][subIndex] == X ) {
            cout << "  X ";
         } else {
            cout << "  O ";
         }
      }
      //end of each row
      cout << endl << endl;
   }
}

bool CatGame( int **gameBoard  ){
   for ( int index = 0 ; index < boardSize ; index++ ) {
      for ( int subIndex = 0 ; subIndex < boardSize ; subIndex++ ) {
         if(gameBoard[index][subIndex] == NOT_TAKEN) return false;
         //if there is a slot not taken, then game is still playable
      }
   }
   //all positions taken
   return true;
}

bool TwodHasWon ( int **gameBoard ) {

   const int ALL_Os = O * boardSize; //3
   const int ALL_Xs = X * boardSize; //30

   int setinLine = 0;

   //check rows
   for ( int rows = 0 ; rows < boardSize ; rows++ ) {
      setinLine = 0;
      for ( int collumn = 0 ; collumn < boardSize ; collumn++ ) {
         setinLine += gameBoard[rows][collumn];
      }
      if ( setinLine == ALL_Os || setinLine == ALL_Xs )
         return true;
   }

   //check collumns
   for ( int collumn = 0 ; collumn < boardSize ; collumn++ ) {
      setinLine = 0;
      for ( int rows = 0 ; rows < boardSize ; rows++ ) {
         setinLine += gameBoard[rows][collumn];
      }
      if ( setinLine == ALL_Os || setinLine == ALL_Xs )
         return true;
   }

   //check diaganols //todo needs refactor
   /*setOfThree = 0;
    setOfThree += gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2];
    if ( setOfThree == ALL_Os || setOfThree == ALL_Xs )
    return true;

    setOfThree = 0;
    setOfThree += gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0];
    if ( setOfThree == ALL_Os || setOfThree == ALL_Xs )
    return true;*/

   //no matching set found
   //diagonal 1 y=x
   setinLine = 0;
   for ( int x = 0 ; x < boardSize ; x++ ) {

      int y = x;
      setinLine += gameBoard[y][x];
      //for testing
      /*cout << "checking " << x << "," << y;
      cout << "it is";
      switch (gameBoard[y][x]) {
         case NOT_TAKEN : cout << " not chosen" ;break;
         case X : cout << " X "; break;
         case O : cout << " O "; break;
         default: cout << " undefined"; break;
      }
      cout << endl;*/
   }
   if ( setinLine == ALL_Os || setinLine == ALL_Xs )
      return true;

   //digaonal 2, = diagonal 1 reflected across point (boardsize/2,boardsize/2)
   //y=(x-boardsize-1)*-1   or y=(-x)+boardsize-1
   setinLine = 0;
   for ( int x = 0 ; x < boardSize ; x++ ) {

      int y = (x*-1)+boardSize-1;
      setinLine += gameBoard[y][x];
      //for testing
      /*cout << "checking " << x << "," << y;
      cout << "it is";
      switch (gameBoard[y][x]) {
         case NOT_TAKEN : cout << " not chosen" ;break;
         case X : cout << " X "; break;
         case O : cout << " O "; break;
         default: cout << " undefined"; break;
      }
      cout << endl;*/
   }
   if ( setinLine == ALL_Os || setinLine == ALL_Xs )
      return true;

   return false;
}
