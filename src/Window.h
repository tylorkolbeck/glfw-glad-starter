#pragma once

#include "InputCodes.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Window
{
  public:
    // Callback to handle window resize
    using ResizeCallbackFn = std::function<void(int width, int height)>;
    void SetResizeCallback(const ResizeCallbackFn &callback)
    {
        m_ResizeCallback = callback;
    };

    // Callback to handle input
    using InputCallbackFn = std::function<void(
        Engine::Key, int scancode, Engine::Action action, int mods)>;
    void SetInputCallback(const InputCallbackFn &callback)
    {
        m_InputCallback = callback;
    };

    void StartFrame();
    void EndFrame();

    void Quit();

  public:
    Window(int width, int height, const std::string &title);
    ~Window();

    int Init();
    GLFWwindow *GetHandle() const;
    bool ShouldClose() const;
    bool Running() const;
    int Height() const;
    int Width() const;

  private:
    GLFWwindow *m_window = nullptr;
    int m_width, m_height;
    const std::string m_title;

    static void framebuffer_size_callback(GLFWwindow *window, int width,
                                          int height);
    static void input_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods);

    ResizeCallbackFn m_ResizeCallback = nullptr;
    InputCallbackFn m_InputCallback = nullptr;
};
