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
bool sameCStrings(char *strA, char *strB);

int main(){
   MenuItem myExerciseComp(demonstrateComponent,"title","Do These two c-string have the same value?");

   myExerciseComp.ItemSelected();

}

void demonstrateComponent(){
   char *str1 = "hello";
   char *str2 = "goodbye";

   cout << str1 << " and " << str2 << ((sameCStrings(str1,str2))? " are the same": " are not the same") << endl;

   str1 = "yes";
   str2 = "yes";

   cout << str1 << " and " << str2 << ((sameCStrings(str1,str2))? " are the same": " are not the same") << endl;

   str1 = "123";
   str2 = "1234";

   cout << str1 << " and " << str2 << ((sameCStrings(str1,str2))? " are the same": " are not the same") << endl;

   str1 = "5678";
   str2 = "5678";

   cout << str1 << " and " << str2 << ((sameCStrings(str1,str2))? " are the same": " are not the same") << endl;

}

bool sameCStrings(char *strA, char *strB){

   const char CNULL = '\0';
   int pos = 0;
   while(strA[pos]!=CNULL && strB[pos]!=CNULL){
      if(strA[pos] != strB[pos] ) return false;
      pos++;
   }
   if(strA[pos]==CNULL ^ strB[pos]==CNULL) return false;
   return true;
}
