#include "Font.hpp"

#include <math/Math.hpp>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <GL/gl.h>

#include <string>
#include <map>

void FL_Init(FT_Library ft, std::string path_to_font, int font_size)
{
    FT_New_Face(ft, path_to_font.c_str(), 0, &fl_curface);
    FT_Set_Pixel_Sizes(fl_curface, 0, font_size);

    fl_color = {255, 255, 255};

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

void FL_ChangeColor(FontColor color)
{
    fl_color = color;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(GLubyte c = 0; c < 128; c++)
    {
        FT_Load_Char(fl_curface, c, FT_LOAD_RENDER);

        GLubyte* newbuf = new GLubyte[fl_curface->glyph->bitmap.width * fl_curface->glyph->bitmap.rows * 4];
        for(int i = 0; i < sizeof(newbuf) / sizeof(GLubyte) / 4; i++)
        {
            newbuf[(i*4)] = color.r;
            newbuf[(i*4)+1] = color.g;
            newbuf[(i*4)+2] = color.b;

            if(fl_curface->glyph->bitmap.buffer[i] == 255)
                newbuf[(i*4)+3] = 255;
            else
                newbuf[(i*4)+3] = 0;
        }

        GLuint texture = fl_characters[c].textureID;
        glDeleteTextures(1, &texture);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            fl_curface->glyph->bitmap.width,
            fl_curface->glyph->bitmap.rows,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            newbuf
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        fl_characters[c].textureID = texture;
    }
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
            glTexCoord2f(0, 0);
            glVertex2f(xpos, ypos);

            glTexCoord2f(0, 1);
            glVertex2f(xpos, ypos + h);

            glTexCoord2f(1, 1);
            glVertex2f(xpos + w, ypos + h);

            glTexCoord2f(1, 0);
            glVertex2f(xpos + w, ypos);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);

        x += (ch.advance >> 6) * scale;
    }
}