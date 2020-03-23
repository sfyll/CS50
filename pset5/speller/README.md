# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

the longest word in the dictionnary

## According to its man page, what does `getrusage` do?

The function getrusage and the data type struct rusage are used to examine the resource usage of a process. They are declared in sys/resource.h.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 and possibly more

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

For each letter in the file until the end of file is reached :
    first, nest another loop that checks if characters are alphabetical or apostrophes
        if it is the case, it ads the letter to a word in construction and increment the index for another check loop (see line below)
            then it checks if the word is too long to be a word, as we know the size of the biggest longuest word in the dictionnary, at which case it consumes the word looping going into the next one;
    if the character are figures, it again consumes the remainder of the "word" and reset the index for calculating word size and checking that it is below the limit of longuest word
    then, if word is below the limit and composed only of alphabetical characters and/or apostrophes, it is a whole word, we can then terminate it and add to the word counter, check the spelling,

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf will read subsequent characters until a white space is found, hence causing trouble for words beind directly followed by some sort of punctuations, moreover we would have trouble in allocating memory for a "string" using the fscanf function.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

to remains sure that no garbage value was present at that location
