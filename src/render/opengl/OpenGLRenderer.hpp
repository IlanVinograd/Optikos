#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <iostream>

#include "platform/IWindow.hpp"
#include "render/IRenderer.hpp"
#include "render/RenderQueue.hpp"
#include "shader/IShader.hpp"

#include "utilities/logger.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/* __debugbreak depeneds on MSVC TODO: add #ifdef for MSVC */
#define call(x) \
    x;          \
    if (error) __debugbreak();

namespace Optikos
{
class OpenGLRenderer : public IRenderer
{
   public:
    explicit OpenGLRenderer(IWindow* window, std::unique_ptr<IShader> shader);
    ~OpenGLRenderer() override;

    void onWindowResize(int width, int height) override;
    void beginFrame() override;
    void endFrame() override;
    void submit(const DrawCommand&& command) override;
    void flush() override;
    void swap_buffer() override;

    IRenderQueue& getRenderQueue() override;

   private:
    struct Batch
    {
        unsigned int              VAO      = 0;
        unsigned int              VBO      = 0;
        unsigned int              IBO      = 0;
        unsigned int              shaderId = 0;
        std::vector<float>        vertices;
        std::vector<unsigned int> indices;

        void clear()
        {
            vertices.clear();
            indices.clear();
        }
    };

    /* depended opengl 4.3+ */
    static void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                           GLsizei length, const GLchar* message,
                                           const void* userParam);

    void initializeBatch(Batch& batch);
    void renderBatch(const Batch& batch);

    IWindow*                 m_window;
    std::unique_ptr<IShader> m_shader;
    RenderQueue              m_renderQueue;

    std::unordered_map<std::string, unsigned int> m_shaderCache;
    unsigned int                                  m_defaultShader = 0;

    Batch m_currentBatch;
};

}  // namespace Optikos

#endif /* OPENGLRENDERER_H */