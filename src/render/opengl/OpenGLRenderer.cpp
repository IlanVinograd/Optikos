#include "OpenGLRenderer.hpp"

namespace Optikos
{
OpenGLRenderer::OpenGLRenderer(IWindow* window, UISystem* uiSystem, IShader* shader)
    : m_window(window), m_uiSystem(uiSystem), m_shader(shader)
{
    GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(m_window->native_handle());
    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("GLAD init failed");

    LOG_TRACE(reinterpret_cast<const char*>(glGetString(GL_VERSION)), "log");

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(OpenGLRenderer::messageCallback, this);
}

void OpenGLRenderer::swap_buffer()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(m_window->native_handle()));
}

void OpenGLRenderer::onWindowResize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::render()
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    auto data = m_uiSystem->accumulateWidgets();
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(data.vertices[0]),
                 data.vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(data.indices[0]),
                 data.indices.data(), GL_STATIC_DRAW);

    ShaderSouces source = m_shader->parseShader("res/shaders/shader.vert");
    unsigned int shader = m_shader->createShader(source.vertexSource, source.fragmentSource);

    glUseProgram(shader);
    unsigned int loc = glGetUniformLocation(shader, "uScreenSize");
    glUniform2f(loc, (GLfloat) m_window->getWidth(), (GLfloat) m_window->getHeight());

    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(data.indices.size()), GL_UNSIGNED_INT,
                   nullptr);
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