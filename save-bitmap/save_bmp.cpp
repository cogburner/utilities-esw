// Copyright (c) 2018 Evan S Weinberg
// A test file which demonstrates
// how to use the "save_bitmap" function declared
// in "bitmap_writer.h". This code creates an
// image of a circle. 

#include "bitmap_writer.h"

int main(int argc, char** argv)
{

  unsigned int width = 500;
  unsigned int height = 500;
  const unsigned int image_size = width*height;

  // Allocate a pixel buffer.
  unsigned char* image = new unsigned char[4*image_size];

  // Green background, dark blue circle of radius 100.
  unsigned int circle_radius = 100;
  for (int i = 0; i < image_size; i++)
  {
    int x = i % width;
    int y = i / width;
    int ox = x - width/2;
    int oy = y - height/2;
    if (ox*ox+oy*oy < circle_radius*circle_radius) // inside circle
    {
      image[4*i] = 0; // red
      image[4*i+1] = 0; // green
      image[4*i+2] = 96; // blue
      image[4*i+3] = 255; // alpha---just set to 255, I don't
                          // know how many editors will respect it.
    }
    else // outside
    {
      image[4*i] = 0; // red
      image[4*i+1] = 255; // green
      image[4*i+2] = 0; // blue
      image[4*i+3] = 255; // alpha
    }
  }

  // Save the image.
  save_bitmap("test_circle.bmp", width, height, image);

  // Clean up
  delete[] image;

  // We did it!
  return 0;
}