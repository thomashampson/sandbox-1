# ------------------------------------------------------------------------------
# Imports
# ------------------------------------------------------------------------------
import unittest

from extract_ref import do_something, global_store
from extract_ref import (DataService, Workspace, Workspace2D,
                         WorkspaceFactory)

# ------------------------------------------------------------------------------
# Class
# ------------------------------------------------------------------------------

class DataServiceTest(unittest.TestCase):

  def test_global_store_exists(self):
      self.assertTrue(isinstance(global_store, DataService))

  def xtest_add(self):
      data = WorkspaceFactory.create()
      self.assertTrue(isinstance(data, Workspace))

      # Store it globally
      global_store.add("test", data)
      print "Before clear"
      global_store.clear()
      print "After clear"
      print data.name()
      print "Before del"
      del data
      print "After del"

  def xtest_add_2(self):
      data = WorkspaceFactory.create()
      self.assertTrue(isinstance(data, Workspace))

      # Store it globally
      global_store.add("test", data)
      print "Before del"
      del data
      print "After del"
      print "Before clear"
      global_store.clear()
      print "After clear"

  def test_get(self):
      data = WorkspaceFactory.create()
      self.assertTrue(isinstance(data, Workspace))
      self.assertTrue(isinstance(data, Workspace2D))

      # Store it globally
      global_store.add("test", data)
      del data

      weak_data_ptr = global_store.get("test")
      self.assertTrue(isinstance(weak_data_ptr, Workspace))
      self.assertTrue(isinstance(weak_data_ptr, Workspace2D))

      global_store.add("test2", weak_data_ptr)
      global_store.remove("test")
      do_something(global_store)

# ------------------------------------------------------------------------------
# Main
# ------------------------------------------------------------------------------
if __name__ == '__main__':
    unittest.main(buffer=False)
