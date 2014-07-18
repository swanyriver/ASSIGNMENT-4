/*
 * preFabMaker.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: Brandon
 */
#include <iostream>
#include <fstream>
#include <string>

#include "SwansonObjects/Dictionary.hpp"

using namespace std;

const string filename = "prefab.txt";
const string dictionarySource = "dictionary.txt";
const int MaxLetters= 6;

int main(){
   Dictionary myDictionary(MaxLetters,dictionarySource);
   if(!myDictionary.Filled()) return 1;

   fstream out;
   out.open(filename);

   if(out.fail()) return(1);

   out << "string myWords[]= { ";

   for(int i=1;i<=1000;i++){
      out << " \"" <<myDictionary.GetRandomWord() << "\",";
      if(i%15==0) out << endl;
   }
   out << "};";

   out.close();

   return 0;
}



