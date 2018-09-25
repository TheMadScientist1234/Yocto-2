#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <GLFW/glfw3.h>

#include <string>

enum RowType
{
    NORMAL,
    WARNING,
    ERROR
};

struct ConsoleRow
{
    std::string text = "";
    RowType type = NORMAL;
};

class Console
{
public:
    Console();

    void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

    void draw();
private:

    ConsoleRow m_rows[10];
};

#endif