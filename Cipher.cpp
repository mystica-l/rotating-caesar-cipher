/* File Name: Cipher.cpp
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Source code for Cipher objects
 * Cipher objects can encrypt and decrypt messages using a rotating caesar shift cipher and a queue data type
 */

#include "Cipher.h" //Source file needs own header file

/* Default Constructor */
//Initializes a queue and sets the key to "cpsc"
Cipher::Cipher()
{
  keySize = 4;
  q = Queue();
  key = new char[4] {'c', 'p', 's', 'c'};
  for(int i = 0; i < 4; i ++)
    {
      q.enqueue(key[i]);
    } 
}

/* Overloaded Constructor */
//Initializes a queue and sets the key to the input
Cipher::Cipher(int size, char * inputKey)
{
  keySize = size;
  q = Queue();
  key = new char[size];
  for(int i = 0; i < size; i ++)
    {
      key[i] = inputKey[i];
      q.enqueue(key[i]);
    }
}

/* Destructor */
//Frees up the memory used by the key pointer
Cipher::~Cipher()
{
  delete [] key;
}

//Initialization of an alphabet array to be used by letter shift
const char Cipher::alphabet[] {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

/* setCipher */
//Frees up the memory already allocated to key and replaces it with new memory and a different key
void Cipher::setCipher(int size, char * inputKey)
{
  keySize = size;
  q.clear();
  delete[] key;
  key = new char[size];
  for(int i = 0; i < size; i ++)
    {
      key[i] = inputKey[i];
      q.enqueue(key[i]);
    }
}

/* getCipher */
//Returns a pointer to the key cipher
char * Cipher::getCipher()
{
  char * returnCipher = key;
  return returnCipher;
}

/* encodeMessage */
//Takes in a message and iterates through it to encode it using letterShift
string Cipher::encodeMessage(string in)
{
  string returnString = "";
  char shift;
  //resetQueue is needed for each new call of encodeMessage so the previous queue change doesn't mess it up
  resetQueue();
  int length = static_cast<int>(in.length());
  for(int i = 0; i < length; i ++)
    {
      q.dequeue(shift);
      returnString += letterShift(in[i], shift, false);
      q.enqueue(shift);
    }
  return returnString;      
}

/* decodeMessage */
//Takes in a message and iterates through it to decode it using letterShift
string Cipher::decodeMessage(string in)
{
  string returnString = "";
  char shift;
  //resetQueue is needed for each new call of encodeMessage so the previous queue change doesn't mess it up
  resetQueue();
  int length = static_cast<int>(in.length());
  for(int i = 0; i < length; i ++)
    {
      q.dequeue(shift);
      returnString += letterShift(in[i], shift, true);
      q.enqueue(shift);
    }
  return returnString;
}

/* letterShfit */
//Takes in a letter, a shift, and which way it needs to be shifted
char Cipher::letterShift(char shifted, char shifter, bool reverse)
{
  char newChar;

  //Utilizes modulous and ASCII values to adjust newChar to the value it should be
  if(!reverse)
    {
      newChar = (static_cast<int>(shifted) - 96 + static_cast<int>(shifter) - 96) % 26;
    }
  else
    {
      newChar = (static_cast<int>(shifted) - 96 - (static_cast<int>(shifter) - 96) + 26) % 26;
    }
  if(newChar == 0)
    {
      newChar = 26;
    }

  //Grabs the character from the alphabet and returns it
  return alphabet[newChar - 1];
}

/* resetQueue */
//Clears the queue and requeues the key
void Cipher::resetQueue()
{
  q.clear();
  for(int i = 0; i < keySize; i ++)
    {
      q.enqueue(key[i]);
    }
}
