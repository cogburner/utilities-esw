// Copyright (c) 2018 Evan S Weinberg
// Header file for code which, given a file name,
// image size, and 32 bit pixel information, writes
// a bitmap file.

// Writes a bitmap. Note: pixels are left to right, bottom to top.
// Pixel color order is 'rgba'
void save_bitmap(const char* filename, int width, int height, unsigned char* pixels);

