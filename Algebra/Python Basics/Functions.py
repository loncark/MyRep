### placeholder function ###
def fun1():
    pass

# default parameter, null return value
def fun2(argument = 5):
    return None

# argument gathering operator
def person_data(name, surname, *args):
    print('Name: ', name)
    print('Surname: ', name)
    print('Other data:', args)

# keyword gathering operator
def print_kwargs(**kwargs):
  """ Documentation string """  
  print(kwargs)
print_kwargs(wine='merlot', entree='mutton', dessert='macaroon')
# Output: {'wine': 'merlot', 'entree': 'mutton', 'dessert': 'macaroon'}

# function annotations
def fun3(a: float, b: int) -> str:
    return "Number"

# lambda: no return, pass, annotations!
mylambda = lambda arg1, arg2: arg1*arg2
print(mylambda(3,4))

# filtering
my_list = [12, 65, 54, 39]
result = filter(lambda x: (x % 2 == 0), my_list)

""" Here are a few useful built-in functions:
abs(number) returns the absolute value of a number
pow(base, exponent) raises a number to the given exponent
min(container) returns the smallest value in the container
max(container) returns the largest value in the container
round(number, digits) rounds the number to the specified number of digits
format(text, specification) returns formatted text according to the given specification
- the function runs through the given text and replaces each placeholder with the given values
- curly brackets can contain placeholder names or indices, or can be empty (anonymous)
- if placeholders are not named (anonymous), they are used in ordinal manner 
startswith(letter) returns true if a string starts with the specified letter"""