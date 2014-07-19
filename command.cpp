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
#include <stdlib.h>
#include "SwansonLibs/swansonString.hpp"

using namespace std;


const int HIGH_GRADE = 5;

int main ( int argc , char* argv[]) {
   string Intro = "lets make a histogram of grades";
   //MenuItem myExerciseComp( demonstrateComponent , "title" , Intro );
   cout << Intro << endl;

   int score;
   int myGradeHisto[HIGH_GRADE];

   //init to zero
   for ( int index = 0 ; index < HIGH_GRADE ; index++ ) {
      myGradeHisto[index] = 0;
   }

   //here switch based on global argc valu
   int index =1;
   while(index<argc) {
      score = atoi(argv[index]);
      if ( score >= 0 && score <= HIGH_GRADE ) {
         myGradeHisto[score]++;
      }
      index++;
   }

   //output scores
   cout << endl << "here is our wonderfull histogram:" << endl;
   for ( int index = 0 ; index < HIGH_GRADE ; index++ ) {
      cout << myGradeHisto[index] << " student(s) received a score of:" << index
            << endl;
   }


}



