/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     WordCounter.cc
  Last updated:  September 16, 2013

  Description:   Implementation of the class WordCounter.
**********************************************************************/

#include "WordCounter.h"

// Constructor with default values for both parameters. By default if
// we don't specify how many occurences of a word we have, we'll
// assume that we have at least one, otherwise we wouldn't need to
// store the word at all.
WordCounter::WordCounter(string s, int n)  
    : word(s), count(n)
{ ; } // WordCounter::WordCounter()

// Constructor with the word specified as a regular array of
// characters (c string).
WordCounter::WordCounter (char *s, int n)
    : word(s), count(n)
{ ; } // WordCounter::WordCounter()

// If we need to reset these values later.
// Set the word using a string object.
void WordCounter::setWord(string s)
{
    word = s;
} // WordCounter::setWord()

// set the word using a C-style string
void WordCounter::setWord(char *s)
{
    word = s;
} // WordCounter::setWord()

// Set the count
void WordCounter::setCount(int n)
{
    count = n;
} // WordCounter::setCount()

// Verify if the word stored in this object is equal to that string.
bool WordCounter::contains(char *s)
{
    return word == string(s);
} // WordCounter::contains()

// Verify if the word stored in this object is equal to that string.
bool WordCounter::contains(string s)
{
    return word==s;
} // WordCounter::contains()
  
// Add 1 to the count.
void WordCounter::increment()
{
    ++count;
} // WordCounter::increment()

// If we want to compare two word counters. These will compare the
// two strings (words) alphabetically.
int WordCounter :: operator< (const WordCounter &y)
{
    return (this->word < y.word);
} // WordCounter :: operator<

// in alphabetic order
int WordCounter :: operator<= (const WordCounter &y)
{
   return (this->word <= y.word);
} // WordCounter :: operator<=

// in alphabetic order
int WordCounter :: operator> (const WordCounter &y)
{
    return (this->word > y.word);
} // WordCounter :: operator>

// in alphabetic order
int WordCounter :: operator>= (const WordCounter &y)
{
    return (this->word >= y.word);
} // WordCounter :: operator>=

// To be used in a table.
string key (const WordCounter & x)
{
    return x.word;
} // key ()

// Easy output of the word counter.
ostream & operator<< (ostream & output, const WordCounter & x)
{
    output << x.word << " " << x.count;
    return output;
} // operator<< 


// Comparison operators.
bool WordCounter::operator== (const WordCounter &y) const
{
    return (count == y.count &&
            word == y.word);
} // WordCounter::operator==

// the opposite of the above
bool WordCounter::operator!= (const WordCounter &y) const
{
  return !((*this) == y);
} // WordCounter::operator!=
