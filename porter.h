/**********************************************************
  File:          porter.h                             
  Description:   Functions for applying the Porter 
                 transformation to a word.

                                                         
  Author:        Dana Vrajitoru  and Stuart J. Barr                      
  Organization:  IUSB                                    
  Date:          September 16, 2013
***********************************************************/

#ifndef PORTER_H
#define PORTER_H

#define KEYWORDSIZE 25
#define PREFIXES 1

#define BIG_KEYWORDSIZE (KEYWORDSIZE+20)

void toLowerCase(char *kwd);
void clean(char *kwd);

// The main porter function. It converts the word to lowercase and
// removes all non-alphabetic characters from the string. Next it
// removes prefixes like "kilo" and suffixes like "s" and "ing".
void stripAffixes (char *string);

// Removes prefixes like "kilo".
void stripPrefixes (char *string);

// Strips suffixes like "s" and "ing" to retain only the root of the
// word.
void stripSuffixes (char *string);

// Five steps done in this order by the previous function.
void step_1 (char *string);
void step_2 (char *string);
void step_3 (char *string);
void step_4 (char *string);
void step_5 (char *string);

// Other internal functions.
int isvalid(char l);
bool hasSuffix ( char *word, char *suffix, char *stem );
int measure ( char *stem );
bool containsVowel ( char *word );
bool cvc ( char *string );
bool vowel ( char ch, char prev );

#endif
