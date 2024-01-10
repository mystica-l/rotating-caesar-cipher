/* File Name: CipherAdvanced.h
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Header file for CipherAdvanced.cpp
 */

#ifndef CIPHERADVANCED_H //Header guards
#define CIPHERADVANCED_H

#include <fstream> //Needed to read through the dictionary
#include <vector> //Needed to create vector containing all the words in the dictionary
#include "Cipher.h"

class CipherAdvanced : protected Cipher //Inherits Cipher class through protected
{
public:
  //Constructor
  CipherAdvanced();

  //Member functions
  void unknownMultiWordScramble(string);
protected:
  //Protected member functions and member variables
  bool hasWords(string);
  int findString(const string&, const string&);
  ifstream dictionary;
  vector<string> dictionaryVector;
  static const string qArray[25];
  static const string invalidTwoLetterCombos[66];
};
#endif
