#include <stdexcept>
#include <iostream>

#include "Application.hpp"

#include <GL/gl.h>

class TestApp : public Application
{
public:
    void Create()
    {
        Application::Create();
    }

    void Draw()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        Application::Draw();
    }

    void Dispose()
    {
        Application::Dispose();
    }
};

int main()
{
    TestApp app;

    app.Create();

    while(!app.GetShouldClose())
    {
        app.Draw();
    }

    app.Dispose();

    return 0;
}