#include "Console.hpp"

#include <graphics/Font.hpp>
#include <freetype/freetype.h>
#include <ft2build.h>
#include <GLFW/glfw3.h>
#include <core/lua.hpp>

#include <string>
#include <algorithm>
#include <iostream>

Console::Console() : m_rows(10)
{
    FT_Library ft;
    FT_Init_FreeType(&ft);

    FL_Init(ft, "YOCTO2.ttf", 64);

    currentRow = 0;
    m_rows[currentRow].text = "YOCTO 2";
    m_rows[currentRow].type = WARNING;
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
	    if(isalnum(key) && mods == 0)
            	m_rows[currentRow].text += key;
            break;
        case GLFW_KEY_9:
            if(mods == GLFW_MOD_SHIFT)
                m_rows[currentRow].text += '(';
            break;
        case GLFW_KEY_0:
            if(mods == GLFW_MOD_SHIFT)
                m_rows[currentRow].text += ')';
            break;
        case GLFW_KEY_APOSTROPHE:
            if(mods == GLFW_MOD_SHIFT)
                m_rows[currentRow].text += '"';
            break;
        case GLFW_KEY_SPACE:
            m_rows[currentRow].text += ' ';
            break;
        case GLFW_KEY_BACKSPACE:
            if(m_rows[currentRow].text.size() != 1)
                m_rows[currentRow].text = m_rows[currentRow].text.substr(0, m_rows[currentRow].text.size() - 1);
            break;
	case GLFW_KEY_ENTER:
        callFunction(m_rows[currentRow].text);
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
                FL_ChangeColor(1.0, 1.0, 1.0);
                break;
            case WARNING:
                FL_ChangeColor(1.0, 1.0, 0.0);
                break;
            case ERROR:
                FL_ChangeColor(1.0, 0.0, 0.0);
                break;
            default:
                FL_ChangeColor(1.0, 1.0, 1.0);
                break;
        }

        FL_DrawText(m_rows[i].text, 0, i * 32, 1);
    }
}

void Console::callFunction(std::string function)
{
    std::string finalstr = function.substr(1, function.length());

    bool readfun = true;
    std::string funstr = "";
    std::string argstr = "";
    for(int i = 0; i < finalstr.length(); i++)
    {
        if(finalstr.at(i) != '(' && readfun)
            funstr += finalstr.at(i);
        else
        {
            readfun = false;
            argstr += finalstr.at(i);
        }
    }

    std::cout << funstr << std::endl;
    std::cout << argstr << std::endl;
}
