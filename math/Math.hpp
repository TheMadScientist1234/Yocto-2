#ifndef MATH_HPP
#define MATH_HPP

#include <GL/gl.h>

struct Vector2i
{
    GLint x;
    GLint y;
    
    Vector2i(GLint x, GLint y)
    {
        this->x = x;
        this->y = y;
    }
};

struct Vector2f
{
    GLfloat x;
    GLfloat y;
};

#endif