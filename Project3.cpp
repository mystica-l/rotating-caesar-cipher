/* File Name: Project3.cpp
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Driver file for Cipher.cpp. Prompts user for for a key and encyrpts and decrypts given strings
 */

#include "Cipher.h" //Needs Cipher to encode and decode messages
#include <iostream> //Needed to print out menus and results

using namespace std; //Needed to avoid typing out std:: for every standard library function

//Function prototypes
bool makeKey(string&);
void printMenu();
void encode(string, char*);
void decode(string, char*);

int main()
{
  //Takes in a string from the user that has at least 1 valid character
  //Strips the input string down to just lower case characters
  string inString;
  cout << "Type in the word to use as the key: ";
  getline(cin, inString);
  while(!makeKey(inString))
  {
    cout << "Key must have at least 1 real letter." << endl;
    cout << "Type in the word to use as the key: " << endl;
    getline(cin, inString);
  }

  //Creates a character array pointer to feed into the cipher
  char* key;
  key = new char[inString.length()];
  for(int i = 0; i < static_cast<int>(inString.length()); i ++)
    {
      key[i] = inString[i];
    }

  //Loop that keeps the code running while the user doesn't want to quit
  string selection = "";
  while(selection != "e" && selection != "d" && selection != "q" && selection != "E" && selection != "D" && selection != "Q")
    {
      //Prints out the key and menu
      cout << endl << "Key: " << key << endl;
      printMenu();

      //Takes in input from the user
      cin >> selection;
      
      if(selection == "e" || selection == "E")
	{
	  encode(inString, key);
	  selection = "";
	}
      else if(selection == "d" || selection == "D")
	{
	  decode(inString, key);
	  selection = "";
	}
      else if(selection == "q" || selection == "Q")
	{
	  //Frees up memory
	  delete[] key;
	}
    }
}

/* makeKey */
//Takes in a string by reference and strips it down to just lower case letters
//Returns a boolean value so it will return false if there are no valid characters
bool makeKey(string &inString)
{
  string keyString;
  for(int i = 0; i < static_cast<int>(inString.length()); i ++)
    {
      if(isalpha(inString[i]))
	{
	  //Takes care of upper cases using ASCII values
	  if(inString[i] < 97 || inString[i] > 122)
	    {
	      keyString += static_cast<char>(inString[i] + 32);
	    }
	  else
	    {
	      keyString += inString[i];
	    }
	}
    }
  return keyString.length() != 0;
}

/* printMenu */
//Prints the menu
void printMenu()
{
  cout << "[e] encode with that key" << endl;
  cout << "[d] decode with that key" << endl;
  cout << "[q] quit" << endl;
}

/* encode */
//Takes in a string and a key and creates a Cipher object to encode a message
void encode(string inString, char* key)
{
  cout << "Enter what to encode: ";
  string encode;
  cin >> encode;
  Cipher cipher = Cipher(inString.length(), key);
  string result = cipher.encodeMessage(encode);
  cout << "result: " << result << endl;
}

/* decode */
//Takes in a string and a key and creates a Cipher object to decode a message
void decode(string inString, char* key)
{
  cout << "Enter what to decode: ";
  string decode;
  cin >> decode;
  Cipher cipher = Cipher(inString.length(), key);
  string result = cipher.decodeMessage(decode);
  cout << "result: " << result << endl;
}
