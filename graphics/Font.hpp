#ifndef FONT_HPP
#define FONT_HPP

#include <math/Math.hpp>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <GL/glew.h>

#include <string>
#include <map>

struct Character
{
    GLuint textureID;
    Vector2i size;
    Vector2i bearing;
    GLint64 advance;
};

struct FontColor
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

static FT_Face fl_curface;
static int fl_font_size;
static FontColor fl_color;

static std::map<GLchar, Character> fl_characters;

void FL_Init(FT_Library ft, std::string path_to_font, int font_size);
void FL_Free();

void FL_ChangeColor(FontColor color);
void FL_DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scale);

#endif