/*
 * CompileMenuItem.hpp
 *
 *  Created on: Jul 21, 2014
 *      Author: root
 */

#ifndef COMPILEMENUITEM_HPP_
#define COMPILEMENUITEM_HPP_

#include "menu.hpp"
#include "../SwansonLibs/swansonInput.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
using namespace std;

class CompileMenuItem: public MenuItem {
private:

   string compileCommand, runCommand;
   bool compiled;
   void ItemSelected () {
      if ( compiled )
         system( runCommand.c_str() );
   }
public:

   static const string N0T_COMP;

   CompileMenuItem ( string filename ) :
         MenuItem( filename , "welcome to " + filename ) {
      string binary = "BIN" + filename;
      compileCommand = "g++ -o " + binary + " " + filename + ".cpp";
      runCommand = "./" + binary;

      if ( system( compileCommand.c_str() ) == 0 ) {
         cout << filename << "sucessfully compiled" << endl;
         compiled = true;
      } else {
         if ( !swansonInput::yesNo(
               "something has gone wrong with <" + filename
                     + ">  continue anyways " ) )
            exit( 1 );

         this->title += CompileMenuItem::N0T_COMP;
         this->itemRepeat = false;
         this->hasIntro = false;
         compiled = false;
      }

   }

};

const string CompileMenuItem::N0T_COMP = " NOT COMPILED";


class AutoCompileMenu: public Menu {
   public:

   AutoCompileMenu ( list<string> items , string title =
         "all of the compiled programs" ) :
         Menu( title ) {
      this->clearScreenON = false;

      while(!items.empty()){
         this->addItem(new CompileMenuItem(items.front()));
         items.pop_front();
      }

      this->menuRepeat = true;
      this->clearScreenON=false;
      this->demoAllItem=true;

   }
};

#endif /* COMPILEMENUITEM_HPP_ */
