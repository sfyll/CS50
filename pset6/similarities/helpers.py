from nltk.tokenize import sent_tokenize
from nltk.tokenize import word_tokenize
import itertools
import argparse
import re
import sys

def lines(a, b):
    """Return lines in both a and b"""
    lista = set(a.split("\n"))
    listb = set(b.split("\n"))

    return lista & listb


def sentences(a, b):
    """Return sentences in both a and b"""

    #1. Takes in string input a and b and 2. split each string into sentences

    lista = sent_tokenize(a)
    listb = sent_tokenize(b)
    #3. Compute list of all sentences appearing in both a and b

    listmatch = (set(lista) & set(listb))
    #4. return the list

    return listmatch


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    lista = []
    listb = []
    listasub = []
    listbsub = []
    # take in input a, b, and substring lenght n

    lista = word_tokenize(a)
    print(lista)
    listb = word_tokenize(b)
    # split each string into all substring of lenght n

    # compute a list of all substring appearing in both a and b by:
    #loop in each word of the lists
    for y in range(len(lista)):
        #loop in each sequence of letter of the string equal to n and append them to the final list to compare
        for i in range(len(lista[y]) + 1 - n):
            listasub.append(lista[y][i:i+n])
    for z in range(len(listb)):
        for j in range(len(listb[z]) + 1 - n):
            listbsub.append(listb[z][j:j+n])
    print(listasub)
    print(listbsub)
    print(set(listasub) & set(listbsub))

    listmatch = (set(listasub) & set(listbsub))

    # return a list
    return listmatch
