#include <iostream>
#include <stdexcept>

#include "graphics/window.hpp"

int main()
{
    YWindow *window = nullptr;
    try {
        window = new YWindow("Yocto-2", 800, 600);
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    while(true)
    {
        window->update();
    }

    window->destroy();

    return 0;
}