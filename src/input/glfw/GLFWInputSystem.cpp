#include "input/glfw/GLFWInputSystem.hpp"

#include "platform/glfw/GLFWWindow.hpp"

namespace Optikos
{
GLFWInputSystem::GLFWInputSystem(GLFWwindow* window) : m_window(window)
{
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetCursorEnterCallback(m_window, cursor_enter_callback);
    glfwSetCharCallback(m_window, character_callback);
    glfwSetKeyCallback(m_window, key_callback);
}

Cursor GLFWInputSystem::getCursor()
{
    return cursor;
}

void GLFWInputSystem::bind(const std::string& action, int key, unsigned int state = Pressed)
{
    m_actions[action].bindings.push_back({key, toGLFW(state), state});
}

void GLFWInputSystem::unbind(const std::string& action)
{
    m_actions.erase(action);
}

void GLFWInputSystem::onAction(const std::string& action, std::function<void()> cb)
{
    m_actions[action].callback = cb;
}

void GLFWInputSystem::dispatch(int key, int action)
{
    for (auto& [name, glfwAction] : m_actions)
    {
        for (auto& b : glfwAction.bindings)
        {
            if (b.key == key && b.action == action)
                if (glfwAction.callback) glfwAction.callback();
        }
    }
}

int GLFWInputSystem::toGLFW(unsigned int s)
{
    switch (s)
    {
        case Pressed:
            return GLFW_PRESS;
        case Release:
            return GLFW_RELEASE;
        case Held:
            return GLFW_REPEAT;
        default:
            return -1;
    }
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

    glfwWindow->getUiSystem()->checkIfHover(xpos, ypos);

    // std::cout << "x: " << self->cursor.x << " y: " << self->cursor.y << std::endl;
}

void GLFWInputSystem::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    (void) mods;
    auto* glfwWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    if (!glfwWindow)
    {
        LOG_FATAL("pointer [glfwWindow] inside GLFWInputSystem::mouse_button_callback is NULL",
                  "log");
        return;
    }

    auto* self = static_cast<GLFWInputSystem*>(glfwWindow->getInputSystem());
    if (!self)
    {
        LOG_FATAL("pointer [self] inside GLFWInputSystem::mouse_button_callback is NULL", "log");
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && (action == GLFW_PRESS || action == GLFW_RELEASE))
    {
        glfwWindow->getUiSystem()->checkIfClicked(self->cursor.x, self->cursor.y, action);
    }
}

void GLFWInputSystem::cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (!entered)
    {
        auto* glfwWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        if (!glfwWindow)
        {
            LOG_FATAL("pointer [glfwWindow] inside GLFWInputSystem::mouse_button_callback is NULL",
                      "log");
            return;
        }
        glfwWindow->getUiSystem()->checkIfHover(0, 0);
    }
}

void GLFWInputSystem::character_callback(GLFWwindow* window, unsigned int codepoint)
{
    auto* glfwWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    if (!glfwWindow)
    {
        LOG_FATAL("pointer [glfwWindow] inside GLFWInputSystem::key_callback is NULL", "log");
        return;
    }
    glfwWindow->getUiSystem()->passInput(codepoint);
}

void GLFWInputSystem::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* glfwWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
    if (!glfwWindow)
    {
        LOG_FATAL("pointer [glfwWindow] inside GLFWInputSystem::key_callback is NULL", "log");
        return;
    }
    (void) scancode;
    (void) mods;
    if ((key == GLFW_KEY_BACKSPACE || key == GLFW_KEY_DELETE) &&
        (action == GLFW_PRESS || action == GLFW_REPEAT))
        glfwWindow->getUiSystem()->passInput(key);

    if ((key == GLFW_KEY_RIGHT || key == GLFW_KEY_LEFT) &&
        (action == GLFW_PRESS || action == GLFW_REPEAT))
        glfwWindow->getUiSystem()->passInput(key);

    glfwWindow->getInputSystem()->dispatch(key, action);
}

}  // namespace Optikos