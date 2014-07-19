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

using namespace std;

void demonstrateComponent();

int main(){
   MenuItem myExerciseComp(demonstrateComponent,"title","It is time for some pointer fun!!");

   myExerciseComp.ItemSelected();

}

string myString = "this is my string";
string *pMyString = &myString;

void demonstrateComponent(){

   string prompt = "I have a string value called myString and a pointer to it called pMyString";
         prompt +="\npMyString is defined as a string* because it points to a location in memory that\nstores a string";
         prompt += "\nRight now the variable myString is equal to:\"" + myString + "\"";
         prompt += "\nAnd if I dereferenced pMyString (*pMyString) it would tell you that that\nlocation in memory holds:\"";
         prompt += *pMyString + "\"\n\n What would you like myString to hold next:";

   *pMyString = swansonInput::GetString(prompt);

   cout << endl <<  "now myString holds:\"" << myString << "\"\nI assigned it this via the pointer pMystring like so"
         << "\n\n   *pMyString = \"" << myString << "\""
         << "\n\nBut the pMyString has not changed, it is still holding the memory address of myString";




}
