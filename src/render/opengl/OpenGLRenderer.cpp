#include "OpenGLRenderer.hpp"

namespace Optikos
{
OpenGLRenderer::OpenGLRenderer(IWindow* window, UISystem* uiSystem)
    : m_window(window), m_uiSystem(uiSystem)
{
    GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(m_window->native_handle());
    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("GLAD init failed");
}

void OpenGLRenderer::swap_buffer()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_window->native_handle()));
}

void OpenGLRenderer::onWindowResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

}  // namespace Optikos