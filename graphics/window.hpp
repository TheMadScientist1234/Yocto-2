#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <X11/Xlib.h>

#include <string>

class Window
{
public:
    Window(std::string title, int width, int height);

    void update();

    void destroy();
private:
    Display *m_display = nullptr;

    Screen *m_screen = nullptr;
    int m_screenId = 0;
    
    Window m_window;
    XEvent ev;
};

#endif