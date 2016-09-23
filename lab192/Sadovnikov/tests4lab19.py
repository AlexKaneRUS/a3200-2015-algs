__author__ = 'alexkane'

import unittest
import lab19

class TestPoly(unittest.TestCase):

    def test1(self):
        res = lab19.execute('yabacrty')
        expected = 'yabay'
        self.assertEqual(expected, res)

    def test2(self):
        res = lab19.execute('babcad')
        expected = 'bab'
        self.assertEqual(expected, res)

    def test3(self):
        res = lab19.execute('aaaaa')
        expected = 'aaaaa'
        self.assertEqual(expected, res)