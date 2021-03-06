#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
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
    void scrollUp();
private:
    void callFunction(std::string function);

    int currentRow;
    std::vector<ConsoleRow> m_rows;
};

#endif
