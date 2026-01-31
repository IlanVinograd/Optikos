#include "OpenGLRenderer.hpp"

#include "ui/text/TextFont.hpp"

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    for (auto& [name, id] : m_textureCache)
    {
        glDeleteTextures(1, &id);
    }
}

void OpenGLRenderer::initializeBatch(Batch& batch)
{
    glGenVertexArrays(1, &batch.VAO);
    glBindVertexArray(batch.VAO);

    glGenBuffers(1, &batch.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, batch.VBO);

    glGenBuffers(1, &batch.IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.IBO);

    glVertexAttribPointer(0, POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
                          (void*) (POSITION_POS * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, COLOR_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
                          (void*) (COLOR_POS * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, UV_SIZE, GL_FLOAT, GL_FALSE, VERTEX_SIZE * sizeof(float),
                          (void*) (UV_POS * sizeof(float)));
    glEnableVertexAttribArray(2);
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

    // TODO: sort by texture idx and then by shader idx to lower draw calls (probably will neede BTS
    // + tree created in start of program and not here).

    for (const auto& cmd : commands)
    {
        unsigned int shaderId  = cmd.shaderId != DEFAULT_SHADER ? cmd.shaderId : m_defaultShader;
        unsigned int textureId = cmd.textureId != NO_TEXTURE ? cmd.textureId : NO_TEXTURE;

        if ((m_currentBatch.shaderId != DEFAULT_SHADER || m_currentBatch.textureId != NO_TEXTURE) &&
            (m_currentBatch.shaderId != shaderId || m_currentBatch.textureId != textureId))
        {
            renderBatch(m_currentBatch);
            m_currentBatch.clear();
        }

        m_currentBatch.shaderId  = shaderId;
        m_currentBatch.textureId = textureId;

        unsigned int vertexOffset =
            static_cast<unsigned int>(m_currentBatch.vertices.size()) / VERTEX_SIZE;
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

    bool hasTexture = false;
    if (batch.textureId != NO_TEXTURE)
    {
        hasTexture = true;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, batch.textureId);

        int texLoc = glGetUniformLocation(batch.shaderId, "uTexture");
        if (texLoc != -1) glUniform1i(texLoc, DEFAULT_TEXTURE_UNIT);
    }

    int toggleLoc = glGetUniformLocation(batch.shaderId, "uHasTexture");
    if (toggleLoc != -1) glUniform1i(toggleLoc, hasTexture);

    // TODO: unsigned int loc but is should be int [Shader] because if we get error it will be -1.
    int screenLoc = glGetUniformLocation(batch.shaderId, "uScreenSize");
    glUniform2f(screenLoc, (float) m_window->getWidth(), (float) m_window->getHeight());

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

void OpenGLRenderer::loadTexture(const std::vector<unsigned char>& data, int width, int height)
{
    auto& font = TextFont::getInstance();

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    font.setAtlasTextureId(textureId);
}

}  // namespace Optikos