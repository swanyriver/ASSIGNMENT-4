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
#include "SwansonLibs/swansonInput.hpp"
#include "SwansonObjects/menu.hpp"

using namespace std;

void demonstrateComponent();

int main(){
   MenuItem myExerciseComp(demonstrateComponent,"title","welcome to Dynamic Arrays");

   myExerciseComp.ItemSelected();

}

void demonstrateComponent(){
   int arraySize = swansonInput::GetInt("how big do you want this array to be:",2,8);
   int *numbers = new int[arraySize];

   for(int index = 0; index < arraySize;  index++){
      numbers[index] = swansonInput::GetInt("what is the next number:");
   }

   cout << endl << "here are the numbers: ";
   for(int index = 0; index < arraySize;  index++){
      cout << numbers[index] << ((index+1<arraySize)?  "/" : "");
   }
}
