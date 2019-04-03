#!env/bin/python
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import sys
import unittest
from google.protobuf.json_format import MessageToJson
import transport_pb2

class TestSum(unittest.TestCase):

    def test_1(self):
        trans = transport_pb2.Transport()
        trans.string_values['key'] = 'value'
        trans.int_values['key1'] = 1
        emp_string = MessageToJson(trans)
        print(emp_string)
        self.assertEqual(1, 1, "Test 1 Passes")

    def test_2(self):
        self.assertEqual(1, 1, "Test 2 Passes")

if __name__ == '__main__':
    unittest.main()