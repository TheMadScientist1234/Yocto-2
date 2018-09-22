#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GLFW/glfw3.h>

class Application
{
public:
    int width = 640;
    int height = 480;

    void Create();
    void Draw();
    void Dispose();

    bool GetShouldClose();
private:
    GLFWwindow *m_window = nullptr;

    bool m_keys[65536];
};

#endif