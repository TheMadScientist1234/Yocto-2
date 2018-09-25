#include "Console.hpp"

#include <graphics/Font.hpp>
#include <freetype/freetype.h>
#include <ft2build.h>
#include <GLFW/glfw3.h>

#include <string>

Console::Console()
{
    FT_Library ft;
    FT_Init_FreeType(&ft);

    FL_Init(ft, "YOCTO2.ttf", 64);

    m_rows[0].text = "YOCTO 2";
    m_rows[2].text = ">";
}

void Console::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(key)
    {
        default:
            if(action == GLFW_PRESS)
                m_rows[2].text += key;
            break;
        case GLFW_KEY_BACKSPACE:
            if(action == GLFW_PRESS && m_rows[2].text.size() != 1)
                m_rows[2].text = m_rows[2].text.substr(0, m_rows[2].text.size() - 1);
            break;
    }
}

void Console::draw()
{
    for(int i = 0; i < sizeof(m_rows) / sizeof(ConsoleRow); i++)
    {
        switch(m_rows[i].type)
        {
            case NORMAL:
                break;
            case WARNING:
                break;
            case ERROR:
                break;
            default:
                break;
        }

        FL_DrawText(m_rows[i].text, 0, i * 32, 1);
    }
}