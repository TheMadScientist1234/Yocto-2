#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application
{
public:
    Application();

    int width = 640;
    int height = 480;

    void Create();
    void Draw();
    void Dispose();

    bool GetShouldClose();
    
    GLFWwindow *m_window = nullptr;

    bool m_keys[65536];
};

#endif