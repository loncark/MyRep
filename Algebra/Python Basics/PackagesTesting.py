# packages -> folders that contain python modules
# ways of importing same function:
"""import pkg.mod 
print(pkg.mod.some_fn())

from pkg import mod 
print(mod.some_fn())

from pkg.mod import *   # imports all publicly available functions
print(some_fn())"""

# packages can contain __init__.py where hidden methods are marked
# PyPI = Python Package Index; before usage do: pip install pillow

### TESTING ###
s = 6

# unit testing: checking for code errors in algorithms, data and syntax
def test():
    assert s == 6, "Should be 6"    # writes te message if the result is false
test()

# built-in:
import unittest

class Test(unittest.TestCase):      # necessary inheritance
    def test_sum(self):
        self.assertEqual(sum([1,2,3]), 6, "Should be 6")

    def setUp(self):
        print("Started testing")
        
    def tearDown(self):
        print("Testing done")

# also: assertNotEqual, assertTrue, assertIs(a,b), assertGreater,
# assertGreaterEqual(a,b), assertListEqual(a,b), assertLess(a,b)...

# running unit tests: python -m unittest test module.TestClass

unittest.main(argv=[''], verbosity=2, exit=False)

# unit test for a specific function:

def full_name(first_name, last_name):
    """
    Returns a capitalized full name
    """
    full_name = first_name + " " + last_name
    return full_name.title()

class FullNameUnitTests(unittest.TestCase):
    def test_full_name(self):
        res = full_name('john', 'smith')
        self.assertEqual(res, 'John Smith')
        
# unit test for checking answers:

class Question():
    """Represents a question for the questionnaire"""
    def __init__(self, question_text):
        """Initialization"""
        self.question_text = question_text
        self.answers = []
        
    def show_question(self):
        """Show question"""
        print(self.question_text)
        
    def store_answer(self, answer_text):
        """Store answer"""
        self.answers.append(answer_text)
        
    def show_answers(self):
        """Show answers"""
        print("Answers:")
        for answer in self.answers:
            print('- ' + answer)

class TestQuestion(unittest.TestCase):
    def test_store_answer(self):
        """Check if storing an answer is valid"""
        my_question = Question("Select data types that is valid in Python")
        my_question.store_answer("text")
        my_question.store_answer("pool")
        my_question.store_answer("float")
        my_question.store_answer("real")

        for answer in ["pool", "text", "float", "real"]:
            self.assertIn(answer, my_question.answers)