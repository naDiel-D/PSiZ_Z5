/* Daniel Flis

PSiZ_Z5 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits>

using namespace std;

struct FileHeader 
{
    short Type;
    int Size;
    short Reserved1;
    short Reserved2;
    int OffBits;
} 
File;

struct ImageHeader 
{
    int headerSize;
    int width;
    int height;
    short int planes;
    short int bitPerPixel;
    int compresion;
    int imageSize;
    int xPelsPerMeter;
    int yPelsPerMeter;
    int colorUsed;
    int colorImportant;
} 
Pic;

struct coloursRGB 
{
    char R;
    char G;
    char B;
} 
Rgb;

