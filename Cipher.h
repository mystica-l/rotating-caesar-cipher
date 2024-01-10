/* File Name: Cipher.h
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Header file for Cipher.cpp
 */
#ifndef CIPHER_H //Header guards
#define CIPHER_H

#include <string> //Needed to use string objects
#include "Queue.h" //Cipher relies on queues to deocde and encode messages

class Cipher
{
public:
  //Constructors and destructors
  Cipher();
  Cipher(int, char*);
  ~Cipher();

  //Member functions
  void setCipher(int, char*);
  char * getCipher();
  string encodeMessage(string);
  string decodeMessage(string);
  static char letterShift(char, char, bool);
  void resetQueue();
protected:
  //Member variables
  char * key;
  string keyString;
  Queue q;
  int keySize;
  static const char alphabet[26];
};
#endif
