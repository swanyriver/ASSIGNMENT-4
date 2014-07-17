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

using namespace std;

void demonstrateComponent();

int main(){
   MenuItem myExerciseComp(demonstrateComponent,"title","intro");

   myExerciseComp.ItemSelected();

}

void demonstrateComponent(){
   cout << "this function has run" << endl;
}
