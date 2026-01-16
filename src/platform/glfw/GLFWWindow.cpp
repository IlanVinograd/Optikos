#include "GLFWWindow.hpp"

namespace Optikos {

GLFWWindow::GLFWWindow(const int w, const int h, const char* title, GraphicsConfig config) : m_config(config) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    if (m_config.api == GraphicsAPI::OpenGL) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_config.versionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_config.versionMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    } else
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(w, h, title, NULL, NULL);

    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("window creation failed");
    }
    LOG_TRACE("Window opened", "log");

    if (m_config.api == GraphicsAPI::OpenGL) {
        glfwMakeContextCurrent(m_window);
    }

    glfwSetWindowUserPointer(m_window, this);
}

GLFWWindow::~GLFWWindow() {
    if (m_window) {

        if(m_config.api == GraphicsAPI::OpenGL)
            glfwMakeContextCurrent(nullptr);

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

bool GLFWWindow::should_close() const {
    return glfwWindowShouldClose(m_window);
}

void GLFWWindow::error_callback(int error, const char* description) {
    fprintf(stderr, "Error [%d]: %s\n", error, description);
}

} /* Optikos */