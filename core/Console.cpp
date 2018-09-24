#include "Console.hpp"

#include <graphics/FontRenderer.hpp>
#include <freetype/freetype.h>
#include <ft2build.h>
#include <GLFW/glfw3.h>

#include <string>

Console::Console()
{
    FT_Library ft;
    FT_Init_FreeType(&ft);

    fr = new FontRenderer(ft, "YOCTO2.ttf", 64);

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
                fr->changeColor(255, 255, 255, 255);
                break;
            case WARNING:
                fr->changeColor(255, 255, 0, 255);
                break;
            case ERROR:
                fr->changeColor(255, 0, 0, 255);
                break;
            default:
                fr->changeColor(255, 255, 255, 255);
                break;
        }

        fr->render(m_rows[i].text, 0, i * 32, 1.5f);
    }
}