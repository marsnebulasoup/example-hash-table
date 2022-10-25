/*********************
Name: Kevin Bryniak
Assignment: Hash Tables
A example implementation of a hash table.
**********************/

#include "hashtable.h"

HashTable::HashTable()
{
  count = 0;
}

int HashTable::hash(int id)
{
  return id % SIZE;
}

bool HashTable::insertEntry(int id, string *data)
{
  bool wasInserted = false;
  if (id > 0 && data && data->length() > 0)
  {
    wasInserted = table[hash(id)].addNode(id, data);
    count += wasInserted;
  }
  return wasInserted;
}

bool HashTable::removeEntry(int id)
{
  bool wasRemoved = false;
  if (id > 0)
  {
    wasRemoved = table[hash(id)].deleteNode(id);
    count -= wasRemoved;
  }
  return wasRemoved;
}

bool HashTable::getData(int id, Data *to)
{
  bool wasFound = false;
  if (id > 0)
  {
    table[hash(id)].getNode(id, to);
  }
  return wasFound;
}

int HashTable::getCount()
{
  return count;
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