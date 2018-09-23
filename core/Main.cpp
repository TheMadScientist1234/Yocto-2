#include <stdexcept>
#include <iostream>

#include "Application.hpp"
#include "../file/BitmapLoader.hpp"

#include <GL/gl.h>

#include <libpng16/png.h>

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

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Draw()
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2d(0, 0);
            glVertex2i(0, 0);

            glTexCoord2d(0, 1);
            glVertex2i(0, 64);

            glTexCoord2d(1, 1);
            glVertex2i(64, 64);

            glTexCoord2d(1, 0);
            glVertex2i(64, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);

        Application::Draw();
    }

    void Dispose()
    {
        Application::Dispose();
    }
private:
    GLuint texture = 0;
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
