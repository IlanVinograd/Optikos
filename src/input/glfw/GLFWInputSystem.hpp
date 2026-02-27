#ifndef GLFWINPUTSYSTEM_H
#define GLFWINPUTSYSTEM_H

#include <iostream>
#include <unordered_map>

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

    void bind(const std::string& action, int key, unsigned int state) override;
    void unbind(const std::string& action) override;
    void onAction(const std::string& action, std::function<void()> cb) override;
    void dispatch(int key, int action) override;

   private:
    GLFWwindow* m_window = nullptr;
    Cursor      cursor;

    std::unordered_map<std::string, Action> m_actions;

    int toGLFW(unsigned int s);

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_enter_callback(GLFWwindow* window, int entered);
    static void character_callback(GLFWwindow* window, unsigned int codepoint);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

}  // namespace Optikos

#endif /* GLFWINPUTSYSTEM_H */