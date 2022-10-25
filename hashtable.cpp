/*********************
Name: Kevin Bryniak
Assignment: Hash Tables
A example implementation of a hash table.
**********************/

#include "hashtable.h"

HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

int HashTable::hash(int id)
{
  return id % SIZE;
}

bool HashTable::insertEntry(int id, string *data)
{
  return true;
}

bool HashTable::removeEntry(int id)
{
  return true;
}

bool HashTable::getData(int id, Data *to)
{
  return true;
}

int HashTable::getCount()
{
  return 0;
}

void HashTable::printTable()
{  
  cout << left << "# -|-- Entry -----------------------------" << endl;
  for (int i = 0; i < SIZE; i++)
  {
    cout << setw(2) << i + 1 << " | ";
    table[i].printList();
  }
  cout << "------------------------------------------" << endl;
}