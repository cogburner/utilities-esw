// Copyright (c) 2018 Evan S Weinberg
// A reference piece of code which, given a file name,
// image size, and 32 bit pixel information, writes
// a bitmap file. This code does not provide any
// error checking: it assumes you want to override the
// file if it already exists, it assumes the pixel
// information is already allocated, all that good
// stuff. 

// This file assumes 'pixels' has the order 'rgba', 
// though for endianness reasons I actually need to write it out
// in 'bgra' order. I handle that internally.

#include <iostream>
#include <fstream>

using std::ios;
using std::ofstream;

#include "bitmap_writer.h"

void save_bitmap(const char* filename, int width, int height, unsigned char* pixels)
{
  // Pre-compute the image size.
  int image_size = width*height;

  // Open a binary file stream
  ofstream outBmp("test.bmp", ios::out | ios::binary);

  // The reference for the bmp file format can be found here:
  // http://www.dragonwins.com/domains/getteched/bmp/bmpfileformat.htm

  // Header for the bitmap file.
  unsigned char buffer[54]; 

  // bfType
  buffer[0] = 'B';
  buffer[1] = 'M';

  // bfSize: (54 for header) + (image_size) * (4 for 32 bit image)
  *((int*)(buffer+2)) = 54 + image_size*4;

  // bfReserved1, 2
  *((int*)(buffer+6)) = 0;

  // bfOffBits: offset of the start of the pixel data relative to the start
  // It's the size of the buffer.
  *((int*)(buffer+10)) = 54;

  // Image header.

  // biSize: header size, must be 40.
  *((int*)(buffer+14)) = 40;

  // biWidth: image width.
  *((int*)(buffer+18)) = width;

  // biHeight: image height
  *((int*)(buffer+22)) = height;

  // biPlanes: must be 1.
  *((short*)(buffer+26)) = 1;

  // biBitCount: bits per pixel. 32 here.
  *((short*)(buffer+28)) = 32;

  // biCompression: 0, no compression
  *((int*)(buffer+30)) = 0;

  // biSizeImage: image size, may be zero for uncompressed images.
  *((int*)(buffer+34)) = 0;

  // biXPelsPerMeter: preferred horizonal resolution of image in pixels per meter. 0 indicates no preference.
  *((int*)(buffer+38)) = 0;

  // biYPelsPerMeter: same as above, but vertical.
  *((int*)(buffer+42)) = 0;

  // biClrUsed: set to 0 because we're not using a color table.
  *((int*)(buffer+46)) = 0;

  // biClrImportant: set to 0 because all colors are important.
  *((int*)(buffer+50)) = 0;

  // Write the header.
  outBmp.write((const char*)buffer, 54);

  // Permute the pixel order from rgba to bgra.
  unsigned char* pixels_perm = new unsigned char[4*image_size];
  for (int i = 0; i < image_size; i++)
  {
    pixels_perm[4*i+0] = pixels[4*i+2];
    pixels_perm[4*i+1] = pixels[4*i+1];
    pixels_perm[4*i+2] = pixels[4*i+0];
    pixels_perm[4*i+3] = pixels[4*i+3];
  }

  // Write the permuted pixel data.
  outBmp.write((const char*)pixels_perm, 4*image_size);

  // Clean up.
  delete[] pixels_perm;  

  // Close out!
  outBmp.close();

}