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
#include "SwansonLibs/swansonInput.hpp"
//#include "CompileMenuItem.hpp"

using namespace std;

void demonstrateComponent ();

int main () {

   const string INTRO = "We are going to collect some numbers\nPut them into an array\nAnd then add them up!";

   GoItem myExerciseComp( demonstrateComponent , "" , INTRO );

   myExerciseComp.ItemSelected();

}

void demonstrateComponent () {
   const int NUM_ELEMENTS = 4;
   int numbers[NUM_ELEMENTS];

   for ( int i = 0 ; i < NUM_ELEMENTS ; i++ ) {

      numbers[i] = swansonInput::GetInt(
            "number " + swansonString::GetString( i + 1 ) + " of "
                  + swansonString::GetString( NUM_ELEMENTS ) + " will be:" );
   }

   long int sum=0;
   for ( int i = 0 ; i < NUM_ELEMENTS ; i++ ) sum += numbers[i];

   cout << endl << "the sum is:" << sum;


}
