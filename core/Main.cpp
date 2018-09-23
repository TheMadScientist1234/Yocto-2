#include <stdexcept>
#include <iostream>

#include <core/Application.hpp>
#include <graphics/Texture.hpp>
#include <graphics/FontRenderer.hpp>

#include <GL/gl.h>
#include <ft2build.h>
#include <freetype/freetype.h>

class TestApp : public Application
{
public:
    TestApp(){}

    void Create()
    {
        Application::Create();

        FT_Init_FreeType(&ft);

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
        x = 0;
        y = 0;
        xdir = 0;
        ydir = 0;

        fonttest = new FontRenderer(ft, "PICO-8.ttf", 16);
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
        fonttest->render("Hey this iS a long bit of text.", 0, 0, 1.5);

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

    FT_Library ft;
    FontRenderer* fonttest = nullptr;
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
