#include "BitmapLoader.hpp"

#include <GL/gl.h>

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

GLuint BitmapLoader::Load(std::string path)
{
    uint8_t* datBuff[2] = {nullptr, nullptr};

    uint8_t* pixels = nullptr;

    BITMAPFILEHEADER* bmpHeader = nullptr;
    BITMAPINFOHEADER* bmpInfo = nullptr;

    std::ifstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("[YCT2] Failed to load file!");
    
    datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
    datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];

    file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
    file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

    bmpHeader = (BITMAPFILEHEADER*) datBuff[0];
    bmpInfo = (BITMAPINFOHEADER*) datBuff[1];

    if(bmpHeader->bfType != 0x4D42)
        throw std::runtime_error("[YCT2] Failed to load file!");
    
    pixels = new uint8_t[bmpInfo->biSizeImage];

    file.seekg(bmpHeader->bfOffBits);
    file.read((char*)pixels, bmpInfo->biSizeImage);

    uint8_t tmpRGB = 0;
    for(ulong i = 0; i < bmpInfo->biSizeImage; i++)
    {
        tmpRGB = pixels[i];
        pixels[i] = pixels[i+2];
        pixels[i+2] = tmpRGB;
    }

    GLuint w = bmpInfo->biWidth;
    GLuint h = bmpInfo->biHeight;

    GLuint texture = 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] datBuff[0];
    delete[] datBuff[1];
    delete[] pixels;

    return texture;
}