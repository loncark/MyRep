
#modules 
from random import randint, choice

a = randint(1,100)
arr = ["win", "lose", "draw"]
b = choice(arr)
print(a, b)

#conversions
a = int("2")
b = chr(4)
c = float("3.0")

#word in sentence
sentence = "Fox jumps over a gray fence."
word1 = "top"
word2 = "over"

if word1 in sentence or word2 in sentence:
  print("At least one of these words found")

#sentence into array of strings
sentence = "Please enter the sentence"
print(sentence.split())

#reverse string/array
text = [1,2,3]
print(text[::-1])

#ascii value of a letter
print(ord('c'))

#swapping variables
a = 1
b = 2
b,a = a,b

#range(min, max, step)
#for i in range(0, 11, 3):
  #print(i, end = ' ')

#random number
import random
x = random.randint(0, 100)

### list #########################################
marxes = ['Groucho', 'Chico', 'Harpo']
marxes.append('Zeppo')
marxes.insert(2, 'Dumbo')
others = ['Gummo', 'Karl']
marxes = marxes + others
marxes.sort()
#print("\n", marxes)
del marxes[-1]
del marxes[1:3]
#print(marxes)
marxes.remove('Gummo')
marxes.pop()
#print(marxes, len(marxes))

### dictionary ###
items = {
  1: "The first item",
  2: "The second item",
  "three": "And the third item?",
  False: "Fourth... yes, that's right?"
}
if 2 in items:
    items[2]="New second"
items2 = items.copy()
#print("\n", items2, "\n")

#list to dictionary
stuff = [ ['1', 'a'], ['2', 'b'], ['3', 'c'] ]
dict1 = dict(stuff)
#print(dict1.keys())
#print(dict1.values())

keysList = ["Key1", True, False]
valuesList = [3, 4, True]
zipped = dict(zip(keysList, valuesList))
#print(zipped)

### tuple -> immutable ###
marx_tuple = 'Groucho', 'Chico', 'Harpo'

# Unpacking a tuple
marx_a, marx_b, marx_c = marx_tuple

### set -> immutable ###
even_numbers = {0, 2, 4}
odd_numbers = {1, 3, 5}
all_numbers = even_numbers.union(odd_numbers)

