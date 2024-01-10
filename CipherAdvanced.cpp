/* File Name: CipherAdvanced.cpp
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Source code for CipherAdvanced object
 * Decrypts secret messages that consist of 3+ letter words and are encrypted by a key that is a word in the dictionary
 */

#include "CipherAdvanced.h" //Source file needs own header file
#include <iostream> //Needed to print out final results
#include <iomanip> //Needed to format final results

/* Constructor */
//Fills a dictionary vector with all non special character 3+ letter words
CipherAdvanced::CipherAdvanced()
{  
  //Variable intialization
  string word = "";
  bool hasSpecialCharacter = false;
  string intoDictionary = "";
  int length = 0;
  dictionary.open("/usr/share/dict/words");
  //Iterates through every word
  while(dictionary >> word)
    {
      hasSpecialCharacter = false;
      intoDictionary = "";
      length = word.length();
      //Iterates through each character of the word
      for(int i = 0; i < length; i ++)
	{
	  //Creates a lowercase string of non special characters
	  if(isalpha(word[i]))
	    {
	      if(word[i] < 97 || word[i] > 122)
		{
		  intoDictionary += static_cast<char>(word[i] + 32);
		}
	      else
		{
		  intoDictionary += word[i];
		}
	    }
	  //Sets this boolean to true and exits the loop if there's a special character
	  else
	    {
	      hasSpecialCharacter = true;
	      i = length;
	    }
	}
      //If it's more than 3 letters and has special characters
      if(static_cast<int>(intoDictionary.length()) >= 3 && !hasSpecialCharacter)
	{
	  //The value gets pushed into the dictionary vector
	  dictionaryVector.push_back(intoDictionary);
	}
    }
  dictionary.close();
}

//Initialization for q array, contains all letters followed by a 'q' except for 'u'
const string CipherAdvanced::qArray[] {"qa", "qb", "qc", "qd", "qe", "qf", "qg", "qh", "qi", "qj", "qk", "ql", "qm", "qn", "qo", "qp", "qq", "qr", "qs", "qt", "qv", "qw", "qx", "qy", "qz"};

//Went through dictionary in separate program and found every single two letter combination that did not exist in a word
const string CipherAdvanced::invalidTwoLetterCombos[] {"bq", "bx", "bz", "cj", "cw", "cx", "dx", "fq", "fv", "fx", "fz", "gv", "gx", "hx", "jb", "jc", "jd", "jg", "jh", "jj", "jl", "jm", "jn", "jp", "jq", "jt", "jv", "jw", "jx", "jy", "jz", "kq", "kv", "kx", "kz", "lx", "mj", "mx", "mz", "pq", "pv", "px", "sx", "tq","tx", "vc", "vf", "vj", "vk", "vm", "vp", "vq", "vw", "vx", "vz", "wj", "wq", "wv", "wx", "xd", "xj", "xk", "xr", "zf", "zj", "zx"};

/* unknownMultiWordScramble */
//Takes in a scramble and unscrambles it using every possible word in the dictionary
void CipherAdvanced::unknownMultiWordScramble(string scramble)
{  
  //Variable intialization
  int dictSize = dictionaryVector.size();
  string word;
  string key;
  int length;
  string unscrambled;
  vector<string> outputs;
  //Iterates through the dictionary
  for(int i = 0; i < dictSize; i ++)
    {
      //Makes a key array out of the dictionary word to feed to set cipher
      key = dictionaryVector[i];
      length = key.length();
      char keyArray[length];
      for(int j = 0; j < length; j ++)
	{
	  keyArray[j] = key[j];
	}
      setCipher(length, keyArray);
      
      //Unscrambles it
      unscrambled = decodeMessage(scramble);
      
      //hasWord checks if the unscramble contains words
      if(hasWords(unscrambled))
	{
	  outputs.push_back(unscrambled);
	  outputs.push_back(key);
	}
    }
  
  //Outputs the results
  if(outputs.size() == 0)
    {
      cout << "NO POSSIBILITIES EXIST" << endl;
    }
  else
    {
      cout << setw(15) << left << "message" << "key" << endl;
      for(int i = 0; i < static_cast<int>(outputs.size()) / 2; i += 2)
	{
	  cout << outputs[i] << "\t" << outputs[i + 1] << endl;
	}
    }
}

/* hasWords */
//Takes in a string and checks that each character in the string is part of a word
bool CipherAdvanced::hasWords(string inString)
{
  int length = inString.length();
  //Checks if the string has any 'q' followed by not a 'u' and returns false if it does
  for(int i = 0; i < 25; i ++)
    {
      if(findString(qArray[i], inString) != -1)
	{
	  return false;
	}
    }
  
  //Creates 2 strings containing the first and last 3 letters of the string
  string firstThree = "";
  for(int i = 0; i < 3; i ++)
    {
      firstThree += inString[i];
    }
  string lastThree = "";
  for(int i = length - 3; i < length; i ++)
    {
      lastThree += inString[i];
    }

  //All three characters in both string MUST be part of the same word, so it checks if there are any non existent 2 letter combos in them
  for(int i = 0; i < 66; i ++)
    {
      string invalidTwoLetterCombo = invalidTwoLetterCombos[i];
      if(findString(invalidTwoLetterCombo, firstThree) != -1 || findString(invalidTwoLetterCombo, lastThree) != -1)
        {
          return false;
        }
    }

  bool checkedCharacters[length];
  //Sets the flags for the checkeed characters all to false
  for(int i = 0; i < length; i ++)
    {
      checkedCharacters[i] = false;
    }

  int foundIndex = 0;
  int dictSize = dictionaryVector.size();
  //Starts iterating through the dictionary to flag characters
  for(int i = 0; i < dictSize; i ++)
    {
      foundIndex = -1;
      //Sets the index to the index the dictionary word is found in the string, -1 else wise
      foundIndex = findString(dictionaryVector[i], inString);
      //If something is found...
      if(foundIndex != -1)
        {
	  //Flag the respective checkedCharacters boolean array as true
          for(int j = foundIndex; j < static_cast<int>(dictionaryVector[i].length()) + foundIndex; j ++)
            {
              checkedCharacters[j] = true;
            }
        }
    }

  //Counts the number of flagged characters
  int counter = 0;
  
  for(int i = 0; i < length; i ++)
    {
      if(checkedCharacters[i] == true)
        {
          counter ++;
        }
    }

  //Returns true if at least 90% of the characters in the string were flagged to be words
  return counter >= length - length / 10;
}

/* findString */
// Returns the first index of a substring inside of a main string and -1 otherwise
int CipherAdvanced::findString(string const &insideString, string const &mainString)
{
  int insideStringLength = insideString.length();
  int mainStringLength = mainString.length();

  //Initial check for strings that are too big or exactly the same
  if(insideStringLength >= mainStringLength)
    {
      if(insideString == mainString)
	{
	  return 0;
	}
      else
	{
	  return -1;
	}
    }

  int shift = 0;
  int indexI;
  int indexM;

  //While there is string to search through...
  while(shift <= mainStringLength - insideStringLength)
    {
      //indexI is the index of the insideString
      indexI = insideStringLength - 1;
      //indexM is the index of the mainString, it's shifted to compare all of it's characters to the insideString
      indexM = shift + indexI;

      //Iterates through each value in the insideString
      while(indexI >= 0)
        {
	  //This if statement checks if the iteration is at the end and it all matches
          if(indexI == 0 && mainString[indexM] == insideString[indexI])
            {
              return indexM;
            }
          else
            {
	      //If there's not a match, it will exit the while loop and increase shift by one to begin the next comparison
              if(insideString[indexI] != mainString[indexM])
                {
                  shift += 1;
                  indexI = -1;
                }
	      //Otherwise, it will keep going down the index's of both words to compare
              else
                {
                  indexM --;
                  indexI --;
                }
            }
        }
    }
  //If a match is never found, it will return -1
  return -1;
}
