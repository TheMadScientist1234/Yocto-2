#include "Font.hpp"

#include <math/Math.hpp>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <GL/glew.h>

#include <string>
#include <map>

void FL_Init(FT_Library ft, std::string path_to_font, int font_size)
{
    FT_New_Face(ft, path_to_font.c_str(), 0, &fl_curface);
    FT_Set_Pixel_Sizes(fl_curface, 0, font_size);

    fl_color = {1.0, 1.0, 1.0};

    fl_font_size = font_size;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(GLubyte c = 0; c < 128; c++)
    {
        FT_Load_Char(fl_curface, c, FT_LOAD_RENDER);

        GLuint texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            fl_curface->glyph->bitmap.width,
            fl_curface->glyph->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            fl_curface->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        Character character = {
            texture,
            Vector2i(fl_curface->glyph->bitmap.width, fl_curface->glyph->bitmap.rows),
            Vector2i(fl_curface->glyph->bitmap_left, fl_curface->glyph->bitmap_top),
            fl_curface->glyph->advance.x
        };

        fl_characters.insert(std::pair<GLchar, Character>(c, character));

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void FL_ChangeColor(GLfloat r, GLfloat g, GLfloat b)
{
    fl_color.r = r;
    fl_color.g = g;
    fl_color.b = b;
}

void FL_DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scale)
{
    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++)
    {
        Character ch = fl_characters[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y + (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBegin(GL_QUADS);
            glColor3f(fl_color.r, fl_color.g, fl_color.b);
            glTexCoord2f(0, 0);
            glVertex2f(xpos, ypos);

            glColor3f(fl_color.r, fl_color.g, fl_color.b);
            glTexCoord2f(0, 1);
            glVertex2f(xpos, ypos + h);

            glColor3f(fl_color.r, fl_color.g, fl_color.b);
            glTexCoord2f(1, 1);
            glVertex2f(xpos + w, ypos + h);

            glColor3f(fl_color.r, fl_color.g, fl_color.b);
            glTexCoord2f(1, 0);
            glVertex2f(xpos + w, ypos);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);

        x += (ch.advance >> 6) * scale;
    }
}