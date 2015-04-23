#!/usr/bin/python

# formatting text
print('text to print {a} and {b} {a}'.format(a='apple', b='pears'))

# formatting numbers
print('rounding up numbers: {:.2f}'.format(4.3039480394482039823029384023))

# formatting pretty text
for i in range(4):
    print('some spaces between some {:10} and some other {:10}'.format(i,i))

# counting occurences in a string
some_string = 'some text occuring in here'
print('Occurences of letter o in the above text is {}'.format(some_string.count('o')))

# str.find(sub[, start[, end]]) Return the lowest index in the string where substring sub is found
print(some_string.find('tex'))

# str.split(sep=None, maxsplit=-1) Return a list of the words in the string, using sep as the delimiter string.
print(some_string.split())
# a useful version of split is splitlines
print("some text \n with \n many lines \n here and \n there".splitlines())

# regular expressions
import re
string = 'some string with some number 23455'
match = re.search(r'\d\d\d', string)
print(match.group())

# use re with findall
f = open('somefile.txt', mode='r')
emails = re.findall(r'([\w]+)@([\w.]+)', f.read())
print(emails)


