/*************************************************************
  Author:       Dana Vrajitoru 
  Class:        C243 Data Structures
  Date:         October 1, 2014
  File:         main.cc                             
  Description:  A test program for the Porter transformation. 
                It reads one word at a time from the console 
                and outputs the transformed word until the 
                input ends by an eof - a CTRL-D under a Linux 
                terminal or the end of the file in case or 
                redirection.

***************************************************************/

#include <fstream>
#include <iostream>
using namespace std;
#include <cstdlib>
#include "porter.h"
#include "HashTable.h"

void readStopList(HashTable &stopList);
void indexWords(HashTable &stopList, HashTable &indexing);
void increment(HashTable &indexing, string word);

// Main function: create the stopList, call the function reading the
// words and indexing them, and then printing out the result.
int main()
{
    HashTable stopList, indexing;
    readStopList(stopList);
    stopList.statistic();
    indexWords(stopList, indexing);
    cout << "Here is the indexing of your text" << endl;
    indexing.print();
    return 0;
} // main()

// Inputs the stopList and stores it in the table.
void readStopList(HashTable &stopList)
{
    char word[KEYWORDSIZE];
    ifstream fin("stopWords");
    if (!fin.good())
    {
        cout << "error reading the stop list file" << endl;
        exit(1);
    }
    WordCounter wordc;
    do 
    {
        fin >> word;
        if (!fin.eof()) 
        {
            wordc.setWord(word);
            stopList.insert(wordc);
        }
    } while (!fin.eof());
    fin.close();
} // readStopList()

// Reads a word at a time from the console, verifies that it's not in
// the stopList, and if it's not, it applies the Porter transform to
// it, then it indexes it in the table indexing.
void indexWords(HashTable &stopList, HashTable &indexing)
{
    char word[KEYWORDSIZE];
    WordCounter wordc;
    cout << "Enter words separated by spaces or new lines.\n"
         << "The program will output the Porter transform of the words.\n"
         << "End the input with Ctrl-D." << endl;
    while (!cin.eof()) 
    {
        cin >> word;
        if (!cin.eof()) 
        {
            toLowerCase(word);
            clean(word);
            // For the student to add: the following 2 instructions must be
            // executed only if the word is not in the table stopList.
            
            if (!stopList.access(wordc, word)) // if our word is not in stopList
                {
                    stripAffixes(word); // porter transform it to the root
                    increment(indexing, word); // increment
                }
        }
    }
    cout << endl;
} // indexWords()

// It should increment the indexing of the given word in the
// table. This means that if the word can't be found in the table,
// then it should insert it with a count of 1. Otherwise it should
// remove the word from the table, increment the count of the object
// that has been removed, then insert it back with the new number.
void increment(HashTable &indexing, string word)
{
    WordCounter wordc(word); // create a word counter
    if (!indexing.access(wordc, word)) // look for duplicate word
        indexing.insert(wordc); // if no duplicate, insert it
    else
    {
        indexing.remove(wordc, word); // if there is duplicate, remove it
        wordc.increment(); // increment the counter
        indexing.insert(wordc); // insert it
    }    
  // Code to be implemented by the student.
} // increment()