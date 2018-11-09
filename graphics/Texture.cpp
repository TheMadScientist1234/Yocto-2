#include "Texture.hpp"

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include <string>

Texture::Texture(std::string path)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    int width, height;
    unsigned char* pixels = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    m_width = width;
    m_height = height;

    m_region.x = 0;
    m_region.y = 0;
    m_region.w = width;
    m_region.h = height;
}

void Texture::draw(int x, int y)
{
    // Get the texture coordinates for the region
    GLfloat reg_left = (GLfloat) m_region.x / (GLfloat) m_width;
    GLfloat reg_right = ((GLfloat) m_region.x + (GLfloat) m_region.w) / (GLfloat) m_width;
    GLfloat reg_top = (GLfloat) m_region.y / (GLfloat) m_height;
    GLfloat reg_bottom = ((GLfloat) m_region.y + (GLfloat) m_region.h) / (GLfloat) m_height;

    glBindTexture(GL_TEXTURE_2D, m_id);
    glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(reg_left, reg_top);
        glVertex2i(x, y);

        glTexCoord2f(reg_left, reg_bottom);
        glVertex2i(x, y + m_region.h);

        glTexCoord2f(reg_right, reg_bottom);
        glVertex2i(x + m_region.w, y + m_region.h);

        glTexCoord2f(reg_right, reg_top);
        glVertex2i(x + m_region.w, y);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setRegion(int x, int y, int w, int h)
{
    m_region.x = x;
    m_region.y = y;
    m_region.w = w;
    m_region.h = h;
}

void Texture::setRegion(Rect rect)
{
    m_region = rect;
}

Rect Texture::getRegion()
{
    return m_region;
}

int Texture::getWidth() { return m_width; }
int Texture::getHeight() { return m_height; }

GLuint Texture::getID() { return m_id; }