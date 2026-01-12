#pragma once

struct Color { int r, g, b; };

namespace UIColors {
    inline const Color TitleBar{25, 25, 25};
}

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
    #include <dwmapi.h>

    void set_title_bar(HWND hwnd, Color color);
#else
    struct GLFWwindow;
    void set_title_bar(GLFWwindow* window, Color color);
#endif