/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     HashTable.h
  Last updated:  October 1, 2014
  Description:   Definition of a hash table.
**********************************************************************/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <string>

#include "WordCounter.h"

// Default capacity if the table is created with the default constructor.
const int DEF_CAPACITY = 200;

typedef list<WordCounter> ListWordC;
typedef ListWordC::iterator ListIter;

class HashTable {
private:
    vector<ListWordC> storage;
    int capacity;
    int numObjects;
    
    // Checks if the access to a given position is safe in the
    // storage. This means if the position is smaller than the capacity and
    // non negative.
    bool isValid(int position);
    // Increases the capacity of the array up to the given position.
    bool increase(int position);
    
    // This function inserts an object in the table when we already know
    // what position we want it to be inserted at. It is declared as
    // private because the user should not be able to call it. It is
    // designed to be called internally by the public insertion function
    // after getting the position from the hashing function.
    bool insert(WordCounter &wordc, int position);
    
    // This function removes the word counter object from the list at
    // the given position. The key k is a separate parameter from the
    // object because we don't know what the object is yet. It is also
    // intended to be called internally because public remove function
    // should determine the position based on the hash function before
    // it calls this one.
    bool remove(WordCounter &wordc, string k, int position);
    
    // Private functions to be implemented by the student.
    
    // This function should find if the string k has been used as a key
    // to insert an object in the list at the given position. If yes,
    // then it should copy that object into the object wordc and return
    // true. If not, it should return false.
    bool find(WordCounter &wordc, string k, int position);
    
    // The most important function of the class. This function takes a
    // string (a key) and determines the index in the storage array
    // where a object with that key should go.
    int hashing(string k);
    
public:
    // Constructor with given initial capacity.
    HashTable(int size = DEF_CAPACITY);
    // Destructor.
    ~HashTable();
    // Delete all the objects without deleting the storage array.
    void makeEmpty();
    
    // Prints all the objects in the table.
    void print();
    
    // Public functions to be implemented by the student.
    
    // This function should first get the hash index for the key of that
    // object, then find out if the key has been inserted in the list at
    // that index, and if not, then it should insert the object in that
    // list and return true. If the key has already been used in the
    // table, it should return false.
    bool insert(WordCounter &wordc);
    
    // This function should first get the hash index for the string,
    // then find out if the string has been used as a key to insert an
    // object in the list at that index. If yes, it should copy that
    // object into the wordc and return true, and if not, it should just
    // return false.
    bool access(WordCounter &wordc, string k);
    
    // This function should first get the hash index for the string k,
    // then find out if the string has already been used as a key to
    // insert an object in the list at that index. If yes, it should
    // copy that object into the wordc, remove the object from that
    // list, and return true. If not, it should just return false.
    bool remove(WordCounter &wordc, string k);
    
    // This function should print a statistic of usage of each index in
    // the table (number of objects stored at each index).
    void statistic();
};

#endif
