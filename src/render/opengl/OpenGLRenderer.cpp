#include "OpenGLRenderer.hpp"

namespace Optikos {

OpenGLRenderer::OpenGLRenderer(IWindow* window, int minLvl, int maxLvl) : m_window(window) {
    auto glfwWin = static_cast<GLFWwindow*>(m_window->native_handle());

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, minLvl);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, maxLvl);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(glfwWin);

    if (!gladLoadGL())
        throw std::runtime_error("GLAD init failed");
}

OpenGLRenderer::~OpenGLRenderer() {
    glfwMakeContextCurrent(nullptr);
}

void OpenGLRenderer::swap_buffer() {
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_window->native_handle()));
}

} /* Optikos */