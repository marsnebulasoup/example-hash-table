/*********************
Name: Kevin Bryniak
Assignment: Hash Tables
A example implementation of a hash table.
**********************/

#include "main.h"

int main()
{
  // seed the rand function
  srand(time(NULL));

  /*
   * This code makes test data of 6 - 25 entries
   * Note this guarantees at least one non unique id and one bad id
   * Do not modify this code from here to the next comment telling
   * you to "START HERE"
   */
  const int testdatasize = BASE + (rand() % OFFSET + 1);
  int ids[testdatasize];
  string strs[testdatasize];

  char buffer[BUFFERSIZE];
  for (int i = 0; i < testdatasize; i++)
  {
    ids[i] = rand() % MAXID + 1;
    for (int j = 0; j < BUFFERSIZE - 1; j++)
    {
      buffer[j] = 'a' + i;
    }
    buffer[BUFFERSIZE - 1] = '\0';
    strs[i] = buffer;
  }
  ids[testdatasize - 2] = ids[testdatasize - 3];
  strs[testdatasize - 2] = "known duplicate";
  ids[testdatasize - 1] = -1;
  strs[testdatasize - 1] = "known bad";

  /*
   * Show test data
   */
  cout << "Showing Test Data (" << testdatasize << " entries)..." << endl;
  for (int i = 0; i < testdatasize; i++)
  {
    cout << ids[i] << " : " << strs[i] << endl;
  }
  cout << endl;

  /*
   * Now you have two parallel arrays with ids and strings for test data.
   * START HERE and create your hash table and use the test data to show
   * it works.
   */

  // create your hash table object here
  HashTable table;

  // STATIC TESTS
  cout << "> STARTING STATIC TESTS" << endl
       << endl;

  cout << "Count: " << table.getCount() << endl;
  table.printTable();

  cout << endl
       << "Adding all the test data." << endl;
  for (int i = 0; i < testdatasize; i++)
  {
    cout << " attempting to add " << ids[i] << ": " << (table.insertEntry(ids[i], strs + i) ? "success" : "failure") << endl;
  }
  cout << endl;
  table.printTable();
  cout << "Count: " << table.getCount() << endl;
  cout << endl;

  cout << endl
       << "Getting all the test data." << endl;
  for (int i = 0; i < testdatasize; i++)
  {
    Data *data = new Data;
    cout << " attempting to get " << ids[i] << ": " << (table.getData(ids[i], data) ? "success" : "failure") << " --> " << data->id << " has '" << data->data << "'" << endl;
    delete data;
  }
  cout << endl;
  table.printTable();
  cout << "Count: " << table.getCount() << endl;
  cout << endl;

  cout << endl
       << "Removing all the test data." << endl;
  for (int i = 0; i < testdatasize; i++)
  {
    cout << " attempting to remove " << ids[i] << ": " << (table.removeEntry(ids[i]) ? "success" : "failure") << endl;
  }
  cout << endl;
  table.printTable();
  cout << "Count: " << table.getCount() << endl;
  cout << endl;

    // continue using and testing your table, add and remove data,
    // do whatever it takes to full test your object and prove it
    // is robust and can handle all use cases.

    
    
    
    
    return 0;
}
