#include <stdexcept>
#include <cstring>
#include <iostream>

#include "Application.hpp"

#include <GL/gl.h>
#include <SOIL/SOIL.h>


static unsigned char testImage[64*64*4];
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

#if 0
        int width, height;
        unsigned char* image = SOIL_load_image("test.png", &width, &height, 0, SOIL_LOAD_RGB);
#else
#define width 64
#define height 64
	std::memset(testImage, 0xFF, 64*64*4);
	unsigned char *image = testImage;
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

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
