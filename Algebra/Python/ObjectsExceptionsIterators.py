""" Additional functionality that core Python supports:
Module random - generating random numbers
Module os - accessing operating system
Module pickle - data serialization
Modules gzip, zlib, zipfile - archiving files
Module csv - supporting csv file reading/writing

Additional functionality that core Python doesn't support out of the box:
Matplotlib - graphic library
Numpy - number crunching
Requests - HTTP requests, network communication
Pandas, Scikit-learn - tabular, data science
Seaborn - statistics, graphs
PILlow - Python Imaging Library, working with images
Tkinter, PyQt - creating GUI """

class Person():
    age = 10

    def __init__(self) -> None:
        self.name = "Luka"
        Person.age += 1
    
    @classmethod        # like a static method -> can be used on a type itself rather than on an instance of that type
    def getName(self):
        return self.name

    # dunder methods/attributes:
    def __str__(self) -> str:
        return f"This is how you print age {self.age} inside quotations"

    # also: __eq__() for comparisons; ne, lt, gt, le, ge -> !=, <, >, <=, >=,

#print(Person.getName())
#print(Person().__str__())
#print(Person.__dict__)      # returns all attributes and methods

# inheritance: super() accesses parent
class Employee(Person):
    def __init__(self) -> None:
        super().__init__()

    # no override keyword:
    def getName(self):
        return "Franjo"

### error handling ###############
a = [1,2]
try:
    print(a[-10])
except IndexError:
    print("Error")

### generators & iterators #################
def my_range(first=0, last=10, step=1):
    number = first
    while number < last:
        yield number        # generator: a return statement that continues on next time the function is called
        number += step

#for i in my_range():
#     print(i, end=" ")

class MyIterator:           # iterator: any class that has methods __iter__ and __next__
  def __init__(self, start, stop):
    self.current = start
    self.stop = stop
  
  def __iter__(self):
    return self
  
  def __next__(self):
    if self.current >= self.stop:
      raise StopIteration
    cur = self.current
    self.current += 1
    return cur

for i in MyIterator(0, 10):
  print(i, end=" ")

  
### inheritance #####################
class Parent():
    def __init__(self) -> None:
        self.name = "Parent"
    
    def __str__(self) -> str:
        return f"{self.name}"

class Child(Parent):
    def __init__(self, newName) -> None:
        super().__init__()
        self.name = newName
        self.age = 10
    
    def __str__(self) -> str:
        return super().__str__()

parent = Parent()
child = Child("Otto")
print(parent)
print(child)


