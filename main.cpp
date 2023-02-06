#include "main.h"

int main()
{
  // seed the rand function
  srand(time(NULL));

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

  // RANDOM TESTS
  cout << "> STARTING RANDOM TESTS" << endl
       << endl;
  // map to keep track of what's in the table
  map<int, TestEntry> inserted;
  for (int i = 0; i < testdatasize; i++)
  {
    inserted.insert(pair<int, TestEntry>(ids[i], {false, -1}));
  }

  int failureCount = 0;
  int count = 0;
  for (int i = 0; i < RANDOM_TEST_COUNT; i++)
  {
    TestOptions option = TestOptions(rand() % 2);
    int index = i % testdatasize;
    int id = ids[index];
    string *data = strs + index;

    bool entryWasInserted = false;
    bool entryWasRemoved = false;
    switch (option)
    {
    case ADD:
      entryWasInserted = table.insertEntry(id, data);
      cout << "(" << i << ") ADDING: " << id << endl;
      if (inserted[id].isInserted) // if item in table already, should not insert
      {
        ASSERT_PASSED(!entryWasInserted, "should not have inserted entry");
      }
      else if (id > 0 && data->length() > 0) // item not in table, should insert
      {
        ASSERT_PASSED(entryWasInserted, "inserting entry");
      }
      else // item has bad data
      {
        ASSERT_PASSED(!entryWasInserted, "should not have inserted malformed entry");
      }

      if (entryWasInserted)
      {
        count++;
      }
      break;

    case REMOVE:
      cout << "(" << i << ") REMOVING: " << id << endl;
      entryWasRemoved = table.removeEntry(id);
      if (!inserted[id].isInserted) // if item not in table, should not remove
      {
        ASSERT_PASSED(!entryWasRemoved, "should not have removed entry");
      }
      else if (id > 0) // item in table, should remove
      {
        ASSERT_PASSED(entryWasRemoved, "removing entry");
      }
      else // item has bad data and shouldn't have ever been added (so therefore can't be removed)
      {
        ASSERT_PASSED(!entryWasRemoved, "should not have removed malformed entry");
      }

      if (entryWasRemoved)
      {
        count--;
      }
      break;
    }
    ASSERT_PASSED(count == table.getCount(), "verifying counts match");

    Data *temp = new Data;

    if (entryWasInserted) // if a new entry was added
    {
      ASSERT_PASSED(table.getData(id, temp), "entry should have been found");
      ASSERT_PASSED(id == temp->id && *data == temp->data, "entry data should have matched passed data");
      inserted[id].isInserted = true;
      inserted[id].index = index;
    }
    else if (!entryWasRemoved && inserted[id].isInserted) // otherwise, if the entry was not removed and is not in the table
    {
      ASSERT_PASSED(table.getData(id, temp), "previously added entry should have been found");
      ASSERT_PASSED(ids[inserted[id].index] == temp->id && strs[inserted[id].index] == temp->data, "previously added entry data should have matched passed data");
    }
    else
    {
      ASSERT_PASSED(!table.getData(id, temp), "entry should not have been found");
      ASSERT_PASSED(temp->id == -1 && temp->data == "", "entry data should have matched default data");
      inserted[id].isInserted = false;
      inserted[id].index = -1;
    }

    delete temp;

  }

  cout << endl;
  cout << "DUMPING TABLE: " << endl;
  cout << "Count: " << table.getCount() << endl;
  table.printTable();
  cout << endl;

  cout << "Tests completed with " << failureCount << " failure(s)." << endl;

  return 0;
}
