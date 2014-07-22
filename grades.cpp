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
#include <string>
#include "SwansonObjects/menu.hpp"
#include "SwansonLibs/swansonString.hpp"
#include "SwansonLibs/swansonInput.hpp"

using namespace std;

void demonstrateComponent ();

const int HIGH_GRADE = 5;
const int SENTINAL = -1;

int main () {
   string Intro = "lets make a histogram of grades\nEnter grades from 0 to "
         + swansonString::GetString( HIGH_GRADE ) + " with a value of "
         + swansonString::GetString( SENTINAL ) + " to stop";
   GoItem myExerciseComp( demonstrateComponent , "title" , Intro );

   myExerciseComp.ItemSelected();

}

void demonstrateComponent () {
   int score;
   int myGradeHisto[HIGH_GRADE];

   string prompt = "whats the next grade ("
         + swansonString::GetString( SENTINAL ) + " to stop):";

   //init to zero
   for ( int index = 0 ; index < HIGH_GRADE ; index++ ) {
      myGradeHisto[index] = 0;
   }

   //here switch based on global argc valu
   do {
      score = swansonInput::GetInt( prompt );
      if ( score >= 0 && score <= HIGH_GRADE ) {
         myGradeHisto[score]++;
      }
   } while ( score != SENTINAL );

   //output scores
   cout << endl << "here is our wonderfull histogram:" << endl;
   for ( int index = 0 ; index < HIGH_GRADE ; index++ ) {
      cout << myGradeHisto[index] << " student(s) received a score of:" << index
            << endl;
   }
}

