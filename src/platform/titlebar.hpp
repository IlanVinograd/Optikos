#pragma once

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
    #include <dwmapi.h>
    void set_title_bar(HWND hwnd);
#else
    struct GLFWwindow;
    void set_title_bar(GLFWwindow* window);
#endif