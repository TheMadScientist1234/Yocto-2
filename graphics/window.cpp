#include "window.hpp"

#include <X11/Xlib.h>

#include <string>
#include <stdexcept>

YWindow::YWindow(std::string title, int width, int height)
{
    m_display = XOpenDisplay(NULL);
    if(m_display == nullptr)
        throw std::runtime_error("[X11] Failed to open display!");
    
    m_screen = XDefaultScreenOfDisplay(m_display);
    m_screenId = XDefaultScreen(m_display);

    m_window = XCreateSimpleWindow(m_display, XRootWindowOfScreen(m_screen), 0, 0, width, height, 1, BlackPixel(m_display, m_screenId), WhitePixel(m_display, m_screenId));

    XStoreName(m_display, m_window, title.c_str());

    XSelectInput(m_display, m_window, KeyPressMask | KeyReleaseMask | KeymapStateMask | ExposureMask);

    XClearWindow(m_display, m_window);
    XMapRaised(m_display, m_window);
}

void YWindow::update()
{
    XNextEvent(m_display, &ev);
}

void YWindow::destroy()
{
    XDestroyWindow(m_display, m_window);
    XFree(m_screen);
    XCloseDisplay(m_display);
}