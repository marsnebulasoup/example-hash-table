#ifndef HASHTABLE_MACROS_H
#define HASHTABLE_MACROS_H

#define ASSERT_PASSED(expression, message) \
  if (!(expression))                       \
  {                                        \
    cout << "Failed: " << message << endl; \
    failureCount++;                        \
  }

#endif