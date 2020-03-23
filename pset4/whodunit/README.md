# Questions

## What's `stdint.h`?

the goal of this header file is to enhance the interoperability of program by specifiying integer data since their actual sizes are implementation defined and could vary for several reasons.
for example, you get exact-width integer types that are guaranteed to have the same number of bits across all implementations.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

regarding the previous answer, we can use these in a program to facilitate the cross platform work by guarantying the number of bits of the integer.
Note that unsigned bits and signed bits differ from each other since unsigned bits cannot be a negative number but can achieve larger positive values than the signed bits.
unsigned int have a defined behavior in overflow conditions and certains shift conditions contrary to signed int.
to sum up, int are system dependant.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

A BYTE is an 8-bit (1 bytes) unsigned value that corresponds to a single octet in a network protocol.

A DWORD is a 32-bit (4 bytes) unsigned integer (range: 0 through 4294967295 decimal). Because a DWORD is unsigned, its first bit (Most Significant Bit (MSB)) is not reserved for signing.

A LONG is a 32-bit (4 bytes) signed integer, in twos-complement format (range: –2147483648 through 2147483647 decimal). The first bit (Most Significant Bit (MSB)) is the signing bit.

A WORD is a 16-bit  (2 bytes) unsigned integer (range: 0 through 65535 decimal). Because a WORD is unsigned, its first bit (Most Significant Bit (MSB)) is not reserved for signing.



## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

the first two bytes of any bmp file are 0x42 and 0x4D in hexadecimal, BM in ASCII. they are typically used to ensure that the file is actually a BMP file and that it is not endommaged.

## What's the difference between `bfSize` and `biSize`?

bfSize: The size in bytes of the bitmap file. it is the same as biSizeImage (whole image size), to which you had the size of the two header files.
biSize: The number of bytes required by the structure of the BITMAPINFOHEADER, which has a fixed value.

## What does it mean if `biHeight` is negative?

it just means that the bitmap is a top-down DIB and its origin lies in the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

in case both files are inexistant or the os fail to open them.

## Why is the third argument to `fread` always `1` in our code?

cause we want the function to read only once the file

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

if bi.biwidth is three, 3

## What does `fseek` do?

allow to change the location of the pointer

## What is `SEEK_CUR`?

it allows to change the location of the pointer from its current location.
