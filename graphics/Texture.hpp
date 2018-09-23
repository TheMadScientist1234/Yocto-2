#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/gl.h>

#include <string>

class Texture
{
public:
    Texture(std::string path);

    void draw(int x, int y);

    int getWidth();
    int getHeight();
private:
    GLuint m_id;

    int m_width;
    int m_height;
};

#endif