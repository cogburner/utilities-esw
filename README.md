# Utility Functions

This repo contains various reference single-file utilities for timing, saving bitmaps, dense eigenvalue calculations, etc.

## C++ Timing using \<chrono>

A reference on how to use timing routines within the C++ \<chrono> header to time blocks of code. It's only four lines total, two to find the current time, one to compute the difference, and one to convert the difference to seconds. The hard part was figuring out the right four lines.

## Creating ".bmp" files from data arrays

Reference code for creating and saving bitmap files to disk. The C++ file defines a sufficient implementation of the bmp file format, based on the documentation at [http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm](http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm) . This can be included in your code via a single function call:

```
save_bitmap(const char* filename, int width, int height, unsigned char* image);
```

Where the image is given in an un-padded 32-bit binary format (no null delimiter at the end---it's not a string) with the order 'rgba', though the 'a' just gets passed 255. The data order is the bottom row, left to right, second-to-bottom row, left to right, etc up to the top row.

## Computing the entire eigenspectrum of a dense matrix using Eigen

Reference code on how to take matrix elements of sparse matrices, with the purpose of converting it to a dense matrix, and then using the Eigen library computes the full spectrum. Examples exist for real and complex matrices, separately for both symmetric/Hermitian and indefinite matrices.


