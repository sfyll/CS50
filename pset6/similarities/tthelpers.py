def lines(a, b):
    """Return lines in both a and b"""

    #1.takes in string input a and b
    file1 = open("FILE1.txt", "r")
    file2 = open("FILE2.txt", "r")
    lista = []
    listb = []

    #2. split each string into lines and appends them to their respective lists if they are not already present
    for lines in file1:
        if lines in lista:
            break
        elif lines not in lista:
            lista.append(file1.splitlines())
    for lines in file2:
        if lines in listb:
            break
        elif lines not in listb:
            listb.append(file1.splitlines())

    #check if matchs between lines
    listmatch = set(lista) & set(listb)
    #4. return the list of line present in a and b avoiding duplicate
    return [listmatch]


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    return []


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    return []
