/*********************************************************************
  Author:        Chad Parnin
  Class:         C243 Data Structures
  File name:     HashTable.cc
  Last updated:  October 1, 2014
  Description:   Implementation of a hash table.
**********************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "HashTable.h"

// Constructor with given initial capacity.
HashTable::HashTable(int size) // default = 200
    : storage(size) // vector
{
    capacity = size;
    numObjects = 0;
} // HashTable::HashTable()

// Destructor: call the function makeEmpty instead, then deallocate
// the memory inside the storage vector
HashTable::~HashTable()
{
    makeEmpty();
    storage.clear(); // vector storage
} // HashTable::~HashTable()

// Delete all the objects without deleting the storage.
void HashTable::makeEmpty()
{
    for(int i=0; i<capacity; i++)
        storage[i].clear(); // delete all the nodes in the list
    numObjects = 0;
} // HashTable::makeEmpty()

// Checks if the access to a given position is safe in the
// storage. This means if the position is smaller than the capacity
// and non negative.
bool HashTable::isValid(int position)
{
    return (position >= 0 && position < capacity);
}

// Prints all the objects in the table.
void HashTable::print()
{
    ListIter iter;
    int i;
    
    cout << "The table has " << numObjects << " objects." << endl;
    if (numObjects) 
    {
        cout << "Here are the objects:" << endl;
        for (i=0; i<capacity; i++)
            if (storage[i].size()) 
                // traverse the list at index i
                for (iter=storage[i].begin(); iter!=storage[i].end(); ++iter)
                    cout << *iter << endl;
    }
} // HashTable::print()

// Increases the capacity of the array up to the given position.
bool HashTable::increase(int position)
{
    if (position >= 0)
        if (position > capacity) 
        {
            ListWordC emptyList;
            for (int i=capacity; i<= position; i++)
                storage.push_back(emptyList);
            capacity = position + 1;
            return true;
        }
    return false; 
} // HashTable::increase()

// This private function inserts an object in the table when we
// already know what position we want it to be inserted at. It is
// declared as private because the user should not be able to call
// it. It is designed to be called internally by the public insertion
// function after getting the position from the hashing table.
bool HashTable::insert(WordCounter &wordc, int position)
{
    if (position >=0) 
    {
        if (!isValid(position))
            increase(position);
        storage[position].push_back(wordc);
        numObjects++;
        return true;
    }
    else
        return false;
} // HashTable::insert()

// This private function removes the word counter object from the list
// at the given position. It is also intended to be called internally
// because public remove function should determine the position based
// on the hash function before it calls this one. They key is used to
// locate the object which is copied to the object wordc before it is
// erased.
bool HashTable::remove(WordCounter &wordc, string k, int position)
{
    if (!isValid(position))
        return false;
    else 
    {
        ListIter iter = storage[position].begin();
        while (iter != storage[position].end() && 
               key(*iter) != k) // string
            ++iter;
        if (iter == storage[position].end())
            return false;
        else 
        {
            wordc = *iter;
            storage[position].erase(iter);
            numObjects--;
            return true;
        }
    }
} // HashTable::remove()

// Private functions to be implemented by the student.  *****************

// This private function should find if the string k has been used as
// a key to insert an object in the list at the given position. If
// yes, then it should copy that object into the object wordc and
// return true. If not, it should return false.
bool HashTable::find(WordCounter &wordc, string k, int position)
{
    if (!isValid(position))
        return false;
    else
    {
        ListIter iter = storage[position].begin(); // start at beginning
        while (iter != storage[position].end() &&
               key(*iter) != k) // while not at end && no word match
            ++iter; // increment
        if (iter == storage[position].end()) // we didn't find the word
            return false;
        else
        {
            wordc = *iter; // we found the word, copy it to the WordCounter
            return true;
        }
    }
    //Code to be provided by the student.
} // HashTable::find()

// The most important function of the class. This function takes a
// string (a key) and determines the index in the storage array where
// an object with that key should go.

int HashTable::hashing(string s)
{
    int hash_val = 0;
    for (int i = 0; s[i] != '\0'; i++) // traverse vector
        hash_val = (hash_val * 37 + int(s[i])) % capacity; // compute hash value to assign
    return hash_val;
} // HashTable::hashing()

// Public functions to be implemented by the student.  *****************

// This function should first get the hash index for the key of that
// object, then find out if the key has been inserted in the list at
// that index, and if not, then it should insert the object in that
// list and return true. If the key has already been used in the
// table, it should return false.
bool HashTable::insert(WordCounter &wordc)
{
    string word = key(wordc); // get the key of word
    int hash = hashing(word); // pass it to the hash function
    
    if (!find(wordc, word, hash)) // if we don't find a match, insert it
    {
        insert(wordc, hash);
        return true;
    }
    else
        return false;
    //Code to be provided by the student.
} // HashTable::insert()

// This function should first get the hash index for the string, then
// find out if the string has been used as a key to insert an object in
// the list at that index. If yes, it should copy that object into the
// object wordc and return true, and if not, it should just return false.
bool HashTable::access(WordCounter &wordc, string s)
{
    int hash = hashing(s); // get hash index
    if (find(wordc, s, hash)) // if we found the word, great
        return true;
    else
        return false;
    //Code to be provided by the student.
} // HashTable::access()

// This function should first get the hash index for the string, then
// find out if the string has been used as a key to insert an object in
// the list at that index. If yes, it should copy that object into the
// object wordc, remove the object from that list, and return true. If
// not, it should just return false.
bool HashTable::remove(WordCounter &wordc, string s)
{
    int hash = hashing(s); // get hash index for the word
    if (find(wordc, s, hash)) // look for the word, if found, remove it
    {
        remove(wordc, s, hash);
        return true;
    }
    else
        return false;
    //Code to be provided by the student.
} // HashTable::remove()

// This function should print a statistic of usage of each index in
// the table (number of objects stored at each index).  Note: you
// should only need one loop in this function, and no iterator. Use
// the method capacity() for each element of the vector to print the
// number of nodes in that list.sa
void HashTable::statistic()
{
    for (int i=0; i<capacity; i++) // traverse the vector
    {
        if (storage[i].size()) // if we have something, print how many
        {
            cout << "Index " << i << " has ";
            cout << storage[i].size() << " objects\n";
        }
    }
    //Code to be provided by the student.
} // HashTable::statistic()
