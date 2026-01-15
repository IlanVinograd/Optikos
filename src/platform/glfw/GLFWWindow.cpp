#include "GLFWWindow.hpp"

namespace Optikos {

GLFWWindow::GLFWWindow(const int w, const int h, const char* title) {
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(w, h, title, NULL, NULL);

    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("window creation failed");
    }
    LOG_TRACE("Window opened", "log");

    glfwSetWindowUserPointer(m_window, this);
}

GLFWWindow::~GLFWWindow() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        LOG_TRACE("Window closed", "log");
    }
}

void GLFWWindow::setWindowTitleBar(Color color) {
    #ifdef PLATFORM_WINDOWS
        HWND hwnd = glfwGetWin32Window(m_window);
        BOOL useDark = TRUE;
        DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDark, sizeof(useDark));

        COLORREF captionColor = RGB(color.r, color.g, color.b);
        DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &captionColor, sizeof(captionColor));

    #else
        // linux

    #endif
}

void* GLFWWindow::native_handle() {
    return m_window;
}

void GLFWWindow::poll_events() {
    glfwPollEvents();
}

} /* Optikos */