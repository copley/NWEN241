#!/usr/bin/env python3

import sys

def test_num(x,y):
    try:
        numA = int(x)
        numB = int(y)
    except:
        print('Error, please enter 2 positive integer')
    if numA < 0 or numB < 0:
        print('Invalid value, please enter 2 positive integers')
        return
    else:
        print('{a} and {b}'.format(a=numA,b=numB))

inputA = input('Enter the first positive integer')
inputB = input('Enter the second positive integer')

test_num(inputA, inputB)



