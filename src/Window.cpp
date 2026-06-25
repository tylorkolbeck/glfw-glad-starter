#include "Window.h"

#include "InputCodes.h"
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(int w, int h, const std::string &t)
    : m_width(w), m_height(h), m_title(t)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window()
{
    if (m_window)
    {
        std::cout << "Destroying window and terminating glfw\n";
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}

bool Window::Running() const { return !ShouldClose(); }

bool Window::ShouldClose() const { return glfwWindowShouldClose(m_window); }

int Window::Init()
{
    std::cout << "Initializing window\n";
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(m_window);

    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, Window::framebuffer_size_callback);
    glfwSetKeyCallback(m_window, Window::input_callback);

    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    m_width = width;
    m_height = height;

    return 0;
}

GLFWwindow *Window::GetHandle() const { return m_window; }

void Window::framebuffer_size_callback(GLFWwindow *window, int width,
                                       int height)
{
    Window *instance = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (instance)
    {
        instance->m_width = width;
        instance->m_height = height;

        if (instance->m_ResizeCallback)
        {
            instance->m_ResizeCallback(width, height);
        }
    }
}

void Window::input_callback(GLFWwindow *window, int key, int scancode,
                            int action, int mods)
{
    Window *instance = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (instance && instance->m_InputCallback)
    {
        Engine::Key mappedKey = static_cast<Engine::Key>(key);
        Engine::Action mappedAction = static_cast<Engine::Action>(action);

        instance->m_InputCallback(mappedKey, scancode, mappedAction, mods);
    }
}
void Window::Quit() { glfwSetWindowShouldClose(m_window, true); }
int Window::Width() const { return m_width; }
int Window::Height() const { return m_height; }
void Window::StartFrame() {}
void Window::EndFrame()
{

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}
