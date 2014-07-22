/*
 * compileItems.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: root
 */

#include "SwansonObjects/menu.hpp"
#include "SwansonObjects/CompileMenuItem.hpp"

#include "SwansonLibs/swansonInput.hpp"

using namespace std;
#include <iostream>
#include <string>
#include <list>

//testing
#include "hangmanDisplay.hpp"

void normalItem(){
   cout << Banner();
}

int main(){


   //string names[] = {"arrayFun","grades"};
   list<string> mynames;
   mynames.push_back("arrayFun");
   mynames.push_back("grades");


   AutoCompileMenu myMenu(mynames);

   myMenu.addItem(new GoItem(normalItem,"print banner",""));
   myMenu.GetLastItem()->hasIntro=false;

   myMenu.showMenu();

/*   //swansonInput::yesNo("begin");

   Menu myMenu("all  programs");

   GoItem myGo(normalItem,"normal item", "welcome to basecalss");

   myMenu.addItem( &myGo);
  myMenu.addItem( new GoItem(normalItem,"temporary normal item", "welcome to basecalss"));
  //myMenu.addItem(GoItem(normalItem,"normal item2", "welcome to basecalss"));
  myMenu.addItem(new CompileMenuItem("hello virtual"));
  myMenu.addItem(new CompileMenuItem("hello virtual2"));

   myMenu.addItem(new CompileMenuItem("arrayFun"));
   myMenu.addItem(new CompileMenuItem("grades"));
   myMenu.addItem(new GoItem(normalItem,"banner","here is the banner"));

   //swansonInput::yesNo("show Menu");

   myMenu.clearScreenON=false;
   myMenu.showMenu();*/


}

