#include "Texture.hpp"

#include <GL/gl.h>
#include <SOIL/SOIL.h>

#include <string>

Texture::Texture(std::string path)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    int width, height;
    unsigned char* pixels = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::draw(int x, int y)
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0);
        glVertex2i(x, y);

        glTexCoord2i(0, 1);
        glVertex2i(x, y + m_height);

        glTexCoord2i(1, 1);
        glVertex2i(x + m_width, y + m_height);

        glTexCoord2i(1, 0);
        glVertex2i(x + m_width, y);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() { return m_width; }
int Texture::getHeight() { return m_height; }