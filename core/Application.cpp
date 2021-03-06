#include "Application.hpp"

#include <stdexcept>

Application::Application() {}

void Application::Create()
{
    if(!glfwInit())
        throw std::runtime_error("[GLFW] Failed to initialize!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    glfwWindowHint(GLFW_RESIZABLE, false);

    m_window = glfwCreateWindow(width, height, "Yocto-2", nullptr, nullptr);
    if(m_window == nullptr)
        throw std::runtime_error("[GLFW] Failed to create window!");

    glfwMakeContextCurrent(m_window);

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("[GLEW] Failed to initialize!");
}

void Application::Draw()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Application::Dispose()
{
    glfwDestroyWindow(m_window);

    glfwTerminate();
}

bool Application::GetShouldClose()
{
    return glfwWindowShouldClose(m_window);
}