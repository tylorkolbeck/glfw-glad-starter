#include "GlCommon.h"
#include "Window.h"
#include "glad/glad.h"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const std::string APP_NAME = "Game Engine";

// const char *vertexShaderSource =
//     "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
//
// const char *fragmentShaderSource = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//     "}\n\0";
//

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);

    if (window.Init() != 0)
        return -1;

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    window.SetResizeCallback([](int width, int height)
                             { glViewport(0, 0, width, height); });
    window.SetInputCallback(
        [&window](Engine::Key key, int scancode, Engine::Action action,
                  int mods)
        {
            if (key == Engine::Key::Escape && action == Engine::Action::Press)
            {
                window.Quit();
            }
        });

    // Scale the actual viewport size on startup
    glViewport(0, 0, window.Width(), window.Height());

    GLfloat verts[] = {0.0f, 0.0f,  1.0f,  1.0f, -1.0f,
                       1.0f, -1.0f, -1.0f, 1.0f, -1.0f};

    GLushort indices[] = {0, 1, 2, 0, 3, 4};

    // unsigned int vertexShader;
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);
    // int success;
    // char infoLog[512];
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
    //               << infoLog << std::endl;
    // }
    //
    // unsigned int fragmentShader;
    // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);
    //
    // unsigned int shaderProgram;
    // shaderProgram = glCreateProgram();
    //
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram);
    //
    // // glUseProgram(shaderProgram);
    //
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    // Create the buffer
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // Bind the buffer to the array buffer binding point
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the data down to the array buffer which has myBuffer assisgned to
    // it; sends it to the graphics card
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    // Create element buffer
    GLuint indexBufferId;
    glGenBuffers(1, &indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Describe the data to opengl
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    while (window.Running())
    {
        window.StartFrame();

        // Render pass
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // glfw: swap buffers and poll IO

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        // End render pass
        window.EndFrame();
    }

    return 0;
}
