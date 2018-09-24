#include "FontRenderer.hpp"

#include <ft2build.h>
#include <freetype/freetype.h>
#include <GL/gl.h>

#include <string>

FontRenderer::FontRenderer(FT_Library ft, std::string font_path, int size)
{
    FT_New_Face(ft, font_path.c_str(), 0, &m_font);
    FT_Set_Pixel_Sizes(m_font, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for(GLubyte c = 0; c < 128; c++)
    {
        FT_Load_Char(m_font, c, FT_LOAD_RENDER);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        GLubyte newbuffer[m_font->glyph->bitmap.width * m_font->glyph->bitmap.rows * 4];
        for(int i = 0; i < (sizeof(newbuffer) / sizeof(char)) / 4; i++)
        {
            newbuffer[(i * 4)] = m_font->glyph->bitmap.buffer[i];
            newbuffer[(i * 4) + 1] = m_font->glyph->bitmap.buffer[i];
            newbuffer[(i * 4) + 2] = m_font->glyph->bitmap.buffer[i];
            newbuffer[(i * 4) + 3] = m_font->glyph->bitmap.buffer[i];
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            m_font->glyph->bitmap.width,
            m_font->glyph->bitmap.rows,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            newbuffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);

        Character character;
        character.textureID = texture;
        character.width = m_font->glyph->bitmap.width;
        character.height = m_font->glyph->bitmap.rows;

        m_textures[c] = character;
    }

    m_fontHeight = size;
}

void FontRenderer::render(std::string text, int x, int y, float s)
{
    for(int i = 0; i < text.length(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_textures[text[i]].textureID);

        glBegin(GL_QUADS);
            glTexCoord2i(0, 0);
            glVertex2f(x + (i * (m_textures[text[i]].width) * s), y);

            glTexCoord2i(0, 1);
            glVertex2f(x + (i * (m_textures[text[i]].width) * s), y + m_textures[text[i]].height);

            glTexCoord2i(1, 1);
            glVertex2f(x + (i * (m_textures[text[i]].width) * s) + m_textures[text[i]].width, y + m_textures[text[i]].height);

            glTexCoord2i(1, 0);
            glVertex2f(x + ((i * m_textures[text[i]].width) * s) + m_textures[text[i]].width, y);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void FontRenderer::changeColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
    for(GLubyte c = 0; c < 128; c++)
    {
        FT_Load_Char(m_font, c, FT_LOAD_RENDER);

        glBindTexture(GL_TEXTURE_2D, m_textures[c].textureID);

        GLubyte newbuf[m_font->glyph->bitmap.width * m_font->glyph->bitmap.rows * 4];
        for(int i = 0; i < sizeof(newbuf) / sizeof(GLubyte) / 4; i++)
        {
            newbuf[(i * 4)] = r;
            newbuf[(i * 4) + 1] = g;
            newbuf[(i * 4) + 2] = b;

            if(m_font->glyph->bitmap.buffer[i] == 255)
                newbuf[(i * 4) + 3] = a;
            else
                newbuf[(i * 4) + 3] = 0;
        }

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            m_font->glyph->bitmap.width,
            m_font->glyph->bitmap.rows,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            newbuf
        );

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

int FontRenderer::getFontHeight() { return m_fontHeight; }
