#include "Console.hpp"

#include <graphics/Font.hpp>
#include <freetype/freetype.h>
#include <ft2build.h>
#include <GLFW/glfw3.h>

#include <string>
#include <algorithm>

Console::Console() : m_rows(10)
{
    FT_Library ft;
    FT_Init_FreeType(&ft);

    FL_Init(ft, "YOCTO2.ttf", 64);

    currentRow = 0;
    m_rows[currentRow].text = "YOCTO 2";
    currentRow = 2;
    m_rows[currentRow].text = ">";
}

void Console::scrollUp(void)
{
	currentRow = currentRow - 1;
	std::rotate(m_rows.begin(), m_rows.begin() + 1, m_rows.end());
}

void Console::keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action != GLFW_PRESS)
	return;
    switch(key)
    {
        default:
	    if(isalnum(key))
            	m_rows[currentRow].text += key;
            break;
        case GLFW_KEY_SPACE:
            m_rows[currentRow].text += ' ';
            break;
        case GLFW_KEY_BACKSPACE:
            if(m_rows[currentRow].text.size() != 1)
                m_rows[currentRow].text = m_rows[currentRow].text.substr(0, m_rows[currentRow].text.size() - 1);
            break;
	case GLFW_KEY_ENTER:
	    currentRow++;
	    if(currentRow == 10)
		scrollUp();
	    m_rows[currentRow].text = ">";
	    break;
    }
}

void Console::draw()
{
    for(int i = 0; i < m_rows.size(); i++)
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
