#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int width, int height, const char* title) : width(width), height(height)
{
    #ifdef __linux__
        if (std::getenv("WAYLAND_DISPLAY")) // Segmentation fault for some reason when exiting windows on wayland
        {
            glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
        }
    #endif

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create Window\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Fialed to initialize Glad\n";
        glfwTerminate();
    }
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffer()
{
    glfwSwapBuffers(window);
}

float Window::getWidth() const
{
    return (float)width;
}

float Window::getHeight() const
{
    return (float)height;
}

void Window::setResizeCallback(std::function<void(int, int)> callback)
{
    resizeCallback = callback;
}

void Window::updateSize(int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;

    if (resizeCallback)
    {
        resizeCallback(width, height);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win)
    {
        win->updateSize(width, height);
    }
}