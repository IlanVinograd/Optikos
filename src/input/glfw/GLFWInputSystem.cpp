#include "input/glfw/GLFWInputSystem.hpp"

#include "platform/glfw/GLFWWindow.hpp"

namespace Optikos
{
GLFWInputSystem::GLFWInputSystem(GLFWwindow* window) : m_window(window)
{
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
}

Cursor GLFWInputSystem::getCursor()
{
    return cursor;
}

void GLFWInputSystem::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto* glfwWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    if (!glfwWindow)
    {
        LOG_FATAL("pointer [glfwWindow] inside GLFWInputSystem::cursor_position_callback is NULL",
                  "log");
        return;
    }

    auto* self = static_cast<GLFWInputSystem*>(glfwWindow->getInputSystem());
    if (!self)
    {
        LOG_FATAL("pointer [self] inside GLFWInputSystem::cursor_position_callback is NULL", "log");
        return;
    }

    self->cursor.x = xpos;
    self->cursor.y = ypos;

    // std::cout << "x: " << self->cursor.x << " y: " << self->cursor.y << std::endl;
}

void GLFWInputSystem::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    (void) mods;
    auto* glfwWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    if (!glfwWindow)
    {
        // LOG_FATAL("pointer [glfwWindow] inside GLFWInputSystem::cursor_position_callback is NULL",
        //           "log");
        return;
    }

    auto* self = static_cast<GLFWInputSystem*>(glfwWindow->getInputSystem());
    if (!self)
    {
        //LOG_FATAL("pointer [self] inside GLFWInputSystem::cursor_position_callback is NULL", "log");
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "x: " << self->cursor.x << " y: " << self->cursor.y << std::endl;
    }
}

}  // namespace Optikos