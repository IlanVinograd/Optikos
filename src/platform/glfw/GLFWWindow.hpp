#ifndef GLFWWINDOW_H
#define GLFWWINDOW_H

#include "platform/IWindow.hpp"
#include "utilities/logger.hpp"

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
    #include <dwmapi.h>

    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#else
    // linux includes
    
#endif

namespace Optikos {

class GLFWWindow : public IWindow {
public:
    explicit GLFWWindow(const int w, const int h, const char* title, GraphicsConfig config);
    ~GLFWWindow() override;

    void setWindowTitleBar(Color color) override;
    void* native_handle() override;
    void poll_events() override;
    bool should_close() const override;

private:
    GLFWwindow* m_window;
    GraphicsConfig m_config;

};

} /* Optikos */

#endif /* GLFWWINDOW_H */