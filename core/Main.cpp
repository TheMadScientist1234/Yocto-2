#include <stdexcept>
#include <iostream>

#include "Application.hpp"
#include "../graphics/Texture.hpp"

#include <GL/gl.h>
#include <SOIL/SOIL.h>

class TestApp : public Application
{
public:
    void Create()
    {
        Application::Create();

        glViewport(0, 0, width, height);

        glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, width, height, 0, 0.0f, 1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        texture = new Texture("test.png");
    }

    void Draw()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texture->draw(0, 0);

        Application::Draw();
    }

    void Dispose()
    {
        Application::Dispose();
    }
private:
    Texture* texture = nullptr;
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
