#include "OpenGLRenderer.hpp"

namespace Optikos
{
OpenGLRenderer::OpenGLRenderer(IWindow* window, std::unique_ptr<IShader> shader)
    : m_window(window), m_shader(std::move(shader))
{
    m_window->makeContextCurrent();

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("GLAD init failed");

    LOG_TRACE(reinterpret_cast<const char*>(glGetString(GL_VERSION)), "log");

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpenGLRenderer::messageCallback, this);

    ShaderSouces source = m_shader->parseShader("res/shaders/shader.vert");
    m_defaultShader     = m_shader->createShader(source.vertexSource, source.fragmentSource);

    initializeBatch(m_currentBatch);
}

OpenGLRenderer::~OpenGLRenderer()
{
    if (m_currentBatch.VAO) glDeleteVertexArrays(1, &m_currentBatch.VAO);
    if (m_currentBatch.VBO) glDeleteBuffers(1, &m_currentBatch.VBO);
    if (m_currentBatch.IBO) glDeleteBuffers(1, &m_currentBatch.IBO);

    for (auto& [name, id] : m_shaderCache)
    {
        glDeleteProgram(id);
    }
    if (m_defaultShader) glDeleteProgram(m_defaultShader);
}

void OpenGLRenderer::initializeBatch(Batch& batch)
{
    glGenVertexArrays(1, &batch.VAO);
    glBindVertexArray(batch.VAO);

    glGenBuffers(1, &batch.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);

    glGenBuffers(1, &batch.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.IBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void OpenGLRenderer::beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_renderQueue.clear();
}

void OpenGLRenderer::submit(const DrawCommand&& command)
{
    m_renderQueue.submit(std::move(command));
}

void OpenGLRenderer::flush()
{
    const auto& commands = m_renderQueue.getCommands();

    // TODO: sort by shader idx to lower draw calls (probably will neede BTS + tree created in start
    // of program and not here).

    for (const auto& cmd : commands)
    {
        unsigned int shaderId = cmd.shaderId != 0 ? cmd.shaderId : m_defaultShader;

        if (m_currentBatch.shaderId != 0 && m_currentBatch.shaderId != shaderId)
        {
            renderBatch(m_currentBatch);
            m_currentBatch.clear();
        }

        m_currentBatch.shaderId = shaderId;

        unsigned int vertexOffset = static_cast<unsigned int>(m_currentBatch.vertices.size()) / 6;
        m_currentBatch.vertices.insert(m_currentBatch.vertices.end(), cmd.vertices.begin(),
                                       cmd.vertices.end());

        for (auto idx : cmd.indices)
        {
            m_currentBatch.indices.push_back(idx + vertexOffset);
        }
    }

    if (!m_currentBatch.vertices.empty())
    {
        renderBatch(m_currentBatch);
        m_currentBatch.clear();
    }
}

void OpenGLRenderer::renderBatch(const Batch& batch)
{
    glBindVertexArray(batch.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);
    glBufferData(GL_ARRAY_BUFFER, batch.vertices.size() * sizeof(float), batch.vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch.indices.size() * sizeof(unsigned int),
                 batch.indices.data(), GL_STATIC_DRAW);

    glUseProgram(batch.shaderId);

    unsigned int loc = glGetUniformLocation(batch.shaderId, "uScreenSize");
    glUniform2f(loc, static_cast<float>(m_window->getWidth()),
                static_cast<float>(m_window->getHeight()));

    glDrawElements(GL_TRIANGLES, static_cast<int>(batch.indices.size()), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::endFrame()
{
    flush();
}

void OpenGLRenderer::swap_buffer()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_window->native_handle())); /* Used for glfw window*/
}

void OpenGLRenderer::onWindowResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

IRenderQueue& OpenGLRenderer::getRenderQueue()
{
    return m_renderQueue;
}

void GLAPIENTRY OpenGLRenderer::messageCallback(GLenum source, GLenum type, GLuint id,
                                                GLenum severity, GLsizei length,
                                                const GLchar* message, const void* userParam)
{
    (void) source;
    (void) type;
    (void) length;
    (void) userParam;
    (void) id;

    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        return;
    }

    LOG_ERROR(std::string("OpenGL: ") + message, "log");
}

}  // namespace Optikos