/*
 * PreFabDictionary.hpp
 *
 *  Created on: Jul 17, 2014
 *      Author: Brandon
 */

#ifndef PREFABDICTIONARY_HPP_
#define PREFABDICTIONARY_HPP_

#include <string>
#include <set>

using std::string;
using std::set;

class PreFabDict{
private:

   //int numWords;

public:
   /*PreFabDict(){
      numWords=14;
   }*/
   static set<string> getSet(){

      int numWords=14;
      string myWords[]= {"hello", "goodbye",
         "my","secret","word",
         "phrase","thank","you",
         "good","bad","bat",
         "cat","jump","dog",
      };


      set<string> words;
      for (int var = 0; var < numWords; ++var) {
         words.insert(myWords[var]);
      }

      return words;
   }
};


/*class PreFabDict{
private:
   static const string myWords[];
   static int numWords;

public:
   static set<string> getSet(){
      set<string> words;
      for (int var = 0; var < numWords; ++var) {
         words.insert(myWords[var]);
      }

      return words;
   }
};
PreFabDict::numWords = 14;
PreFabDict::myWords = {"hello", "goodbye",
         "my","secret","word",
         "phrase","thank","you",
         "good","bad","bat",
         "cat","jump","dog",
   };*/

//todo, find a way to return a dictionary here also, need to set constructed to true, and passs my set





#endif /* PREFABDICTIONARY_HPP_ */
