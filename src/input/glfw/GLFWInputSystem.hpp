#ifndef GLFWINPUTSYSTEM_H
#define GLFWINPUTSYSTEM_H

#include "input/IInputSystem.hpp"
#include "utilities/logger.hpp"

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Optikos {

class GLFWInputSystem : public IInputSystem {
public:
    GLFWInputSystem(GLFWwindow* window);
    ~GLFWInputSystem() override;

    Cursor getCursor() override;
private:
    GLFWwindow* m_window;
    Cursor cursor;

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
};

} /* Optikos */


#endif /* GLFWINPUTSYSTEM_H */