#include <stdexcept>
#include <iostream>

#include <core/Application.hpp>
#include <graphics/Texture.hpp>
#include <core/Console.hpp>

#include <GL/glew.h>

Console* console = nullptr;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    console->keyPressed(window, key, scancode, action, mods);
}

class TestApp : public Application
{
public:
    TestApp()
    {
        width = 800;
        height = 600;
    }

    void Create()
    {
        Application::Create();

        glViewport(0, 0, width, height);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, width, height, 0, 0.0f, 1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        texture = new Texture("test.png");
        texture->setRegion(0, 0, 32, 32);
        x = 0;
        y = 0;
        xdir = 0;
        ydir = 0;
        
        console = new Console();
        glfwSetKeyCallback(m_window, key_callback);
    }

    void Draw()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(xdir == 0)
            x += 2;
        if(xdir == 1)
            x -= 2;
        if(ydir == 0)
            y += 2;
        if(ydir == 1)
            y -= 2;
        
        if(x + texture->getWidth() == width)
            xdir = 1;
        if(x < 0)
            xdir = 0;
        if(y + texture->getHeight() == height)
            ydir = 1;
        if(y < 0)
            ydir = 0;

        texture->draw(x, y);

        console->draw();

        Application::Draw();
    }

    void Dispose()
    {
        Application::Dispose();
    }
private:
    Texture* texture = nullptr;
    int x, y;
    int xdir, ydir;
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
