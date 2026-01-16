#include "OpenGLRenderer.hpp"

namespace Optikos {

OpenGLRenderer::OpenGLRenderer(IWindow* window) : m_window(window) {
    if (!gladLoadGL())
        throw std::runtime_error("GLAD init failed");
}

void OpenGLRenderer::swap_buffer() {
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_window->native_handle()));
}

} /* Optikos */