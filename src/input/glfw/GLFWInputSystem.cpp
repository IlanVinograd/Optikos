#include "input/glfw/GLFWInputSystem.hpp"

namespace Optikos {

GLFWInputSystem::GLFWInputSystem(GLFWwindow* window) : m_window(window) {
    glfwSetWindowUserPointer(m_window, this);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
}

GLFWInputSystem::~GLFWInputSystem() {
    if(m_window)
        glfwSetWindowUserPointer(m_window, nullptr);
}

Cursor GLFWInputSystem::getCursor() {
    return cursor;
}

void GLFWInputSystem::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    auto* self = static_cast<GLFWInputSystem*>(glfwGetWindowUserPointer(window));
    if (!self) {
        LOG_FATAL("pointer [self] inside GLFWInputSystem::cursor_position_callback is NULL", "log");
        return;
    }

    self->cursor.x = xpos;
    self->cursor.y = ypos;

    // std::cout << "x: " << self->cursor.x << " y: " << self->cursor.y << std::endl;  
}

} /* Optikos */