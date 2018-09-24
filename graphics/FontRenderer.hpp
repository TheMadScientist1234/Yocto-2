#ifndef FONT_RENDERER_HPP
#define FONT_RENDERER_HPP

#include <ft2build.h>
#include <freetype/freetype.h>
#include <GL/gl.h>

#include <string>
#include <map>

struct Character
{
    GLuint textureID;
    int width;
    int height;
};

class FontRenderer
{
public:
    FontRenderer(FT_Library ft, std::string font_path, int size);
    void render(std::string text, int x, int y, float s);

    void changeColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

    int getFontHeight();
private:
    FT_Face m_font;
    std::map<GLchar, Character> m_textures;

    int m_fontHeight;
};

#endif