#ifndef PYTHONOBJECTTEST_H
#define PYTHONOBJECTTEST_H

#include "cxxtest/TestSuite.h"
#include "cxxtest/GlobalFixture.h"

#include <Python.h>

/**
 * The cxxtest code ensures that the setup/tearDownWorld methods
 * are called exactly once per test-process. We use this
 * to initialize/shutdown the python interpreter
 */
class PythonProcessHandler : CxxTest::GlobalFixture {
public:
  bool setUpWorld() override {
    Py_Initialize();
    return Py_IsInitialized();
  }

  bool tearDownWorld() override {
    Py_Finalize();
    return true;
  }
};

// From the cxxtest manual:
//
// We can rely on this file being included exactly once
// and declare this global variable in the header file.
//
static PythonProcessHandler pythonProcessHandler;

class PythonObjectTest : public CxxTest::TestSuite {
public:
  static PythonObjectTest *createSuite() { return new PythonObjectTest; }
  static void destroySuite(PythonObjectTest *suite) { delete suite; }

  void test_Default_Constructor_Gives_None() { TS_FAIL("Add a test"); }
};

#endif // PYTHONOBJECTTEST_H
