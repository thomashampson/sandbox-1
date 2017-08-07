#ifndef PYTHONOBJECTTEST_H
#define PYTHONOBJECTTEST_H

#include "cxxtest/TestSuite.h"
#include "cxxtest/GlobalFixture.h"

#include "PythonObject.h"

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

  void test_Default_Constructor_Gives_None() {
    Python::PythonObject obj;
    TSM_ASSERT("Default object should be None", obj.isNone())
  }

  void test_Construction_With_New_Reference_Does_Not_Alter_Ref_Count() {
    // Use something with heap allocation so we know it's a new object
    Python::PythonObject obj(Python::NewRef(PyList_New(1)));
    TSM_ASSERT_EQUALS("Reference count should not have changed on"
                      "construction ",
                      1, obj.refCount());
  }

  void test_Copy_Construction_Increases_Ref_Count_By_One() {
    // Use something with heap allocation so we know it's a new object
    Python::PythonObject original(Python::NewRef(PyList_New(1)));
    Python::PythonObject copy(original);
    TSM_ASSERT_EQUALS("Copy should reference the same object", original, copy);
    TSM_ASSERT_EQUALS("Copied object should have ref count of 2", 2,
                      copy.refCount());
    TSM_ASSERT_EQUALS("Original object should have ref count of 2", 2,
                      original.refCount());
  }

  void test_Copy_Assignment_Increases_Ref_Count_By_One() {
    // Use something with heap allocation so we know it's a new object
    Python::PythonObject original(Python::NewRef(PyList_New(1)));
    Python::PythonObject copy;
    copy = original;
    TSM_ASSERT_EQUALS("Copy should equal orignal", original, copy);
    TSM_ASSERT_EQUALS("Copied object should have ref count of 2", 2,
                      copy.refCount());
    TSM_ASSERT_EQUALS("Original object should have ref count of 2", 2,
                      original.refCount());
  }

  void test_Equality_Operator() {
    Python::PythonObject original(Python::NewRef(PyList_New(1)));
    TSM_ASSERT_EQUALS("Objects should equal each other", original, original);
    Python::PythonObject other(Python::NewRef(PyList_New(1)));
    TSM_ASSERT_DIFFERS(
        "Different underlying objects should not equal each other", original,
        other);
  }
};

#endif // PYTHONOBJECTTEST_H
