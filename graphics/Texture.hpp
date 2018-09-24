#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/gl.h>

#include <string>

struct Rect
{
    GLint x;
    GLint y;
    GLint w;
    GLint h;
};

struct FRect
{
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

class Texture
{
public:
    Texture(std::string path);

    void draw(int x, int y);
    
    void setRegion(int x, int y, int w, int h);
    void setRegion(Rect rect);
    Rect getRegion();

    int getWidth();
    int getHeight();

    GLuint getID();
private:
    GLuint m_id;

    int m_width;
    int m_height;

    Rect m_region;
};

#endif