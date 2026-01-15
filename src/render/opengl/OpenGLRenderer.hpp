#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "render/IRenderer.hpp"
#include "platform/glfw/GLFWWindow.hpp"
#include "utilities/logger.hpp"

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Optikos {

class OpenGLRenderer : public IRenderer {
public:
    explicit OpenGLRenderer(IWindow* window, int minLvl, int maxLvl);
    ~OpenGLRenderer() override;

    void swap_buffer() override;

private:
    IWindow* m_window;

};

} /* Optikos */

#endif /* OPENGLRENDERER_H */