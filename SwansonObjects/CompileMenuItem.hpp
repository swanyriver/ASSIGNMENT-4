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
using namespace std;

class CompileMenuItem: public MenuItem {
private:

   string compileCommand, runCommand;
   bool compiled;
   void ItemSelected () {
      if(compiled) system(runCommand.c_str());
   }
public:

   static  const string N0T_COMP;

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
         this->itemRepeat=false;
         this->hasIntro=false;
         compiled = false;
      }

   }

};

const string CompileMenuItem::N0T_COMP = " NOT COMPILED";

#endif /* COMPILEMENUITEM_HPP_ */
