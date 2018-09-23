#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/gl.h>

class Texture
{
private:
    void Draw(int x, int y);

    int Width();
    int Height();
private:
    GLuint m_id;

    int width;
    int height;
};

#endif