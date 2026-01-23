#ifndef GLFWINPUTSYSTEM_H
#define GLFWINPUTSYSTEM_H

#include <iostream>

#include "input/IInputSystem.hpp"
#include "utilities/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Optikos
{
class GLFWInputSystem : public IInputSystem
{
   public:
    GLFWInputSystem(GLFWwindow* window);
    ~GLFWInputSystem() override = default;

    Cursor getCursor() override;

   private:
    GLFWwindow* m_window = nullptr;
    Cursor      cursor;

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

}  // namespace Optikos

#endif /* GLFWINPUTSYSTEM_H */