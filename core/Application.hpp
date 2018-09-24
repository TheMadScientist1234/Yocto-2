#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GLFW/glfw3.h>

#define genericCallback(functionName)\
    [](GLFWwindow* window, auto... args) {\
        auto pointer = static_cast<MyGlWindow*>(glfwGetWindowUserPointer(window));\
        if (pointer->functionName) pointer->functionName(pointer, args...);\
    }

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