import sys
sys.path.append("..") 
import unittest
from app import *

class TestSum(unittest.TestCase):

    def test_1(self):
        create_task()
        self.assertEqual(1, 1, "Test 1 Passes")

    def test_2(self):
        self.assertEqual(1, 1, "Test 2 Passes")

if __name__ == '__main__':
    unittest.main()