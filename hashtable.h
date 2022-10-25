/*********************
Name: Kevin Bryniak
Assignment: Hash Tables
A example implementation of a hash table.
**********************/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"
#include "linkedlist.h"
#include "string"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::string;


#define SIZE 15

class HashTable
{
private:
  int count;
  LinkedList table[SIZE];
  int hash(int);

public:
  HashTable();

  bool insertEntry(int, string *);
  bool removeEntry(int);
  bool getData(int, Data *);
  int getCount();
  void printTable();
};

#endif