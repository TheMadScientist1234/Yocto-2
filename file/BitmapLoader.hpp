#ifndef BITMAP_LOADER_HPP
#define BITMAP_LOADER_HPP

#include <GL/gl.h>

#include <string>

typedef struct tagBITMAPFILEHEADER
{
    ushort bfType;
    uint bfSize;
    ushort bfReserved1;
    ushort bfReserved2;
    uint bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    uint biSize;
    long biWidth;
    long biHeight;
    ushort biPlanes;
    ushort biBitCount;
    uint biCompression;
    uint biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    uint biClrUsed;
    uint biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

class BitmapLoader
{
public:
    GLuint Load(std::string path);
};

#endif