#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <iostream>

#include "platform/glfw/GLFWWindow.hpp"
#include "render/IRenderer.hpp"
#include "shader/IShader.hpp"
#include "utilities/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/* __debugbreak depeneds on MSVC TODO: add #ifdef for MSVC */
#define call(x) x;\
    if (error) __debugbreak();

namespace Optikos
{
class OpenGLRenderer : public IRenderer
{
   public:
    explicit OpenGLRenderer(IWindow* window, std::unique_ptr<UISystem> uiSystem, std::unique_ptr<IShader> shader);
    virtual ~OpenGLRenderer() override = default;

    void swap_buffer() override;
    void render() override;
    void onWindowResize(int width, int height) override;

    /* depended opengl 4.3+ */
    static void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

   private:
    IWindow*  m_window;
    std::unique_ptr<UISystem> m_uiSystem;
    std::unique_ptr<IShader> m_shader;
    bool error = false;
};

}  // namespace Optikos

#endif /* OPENGLRENDERER_H */