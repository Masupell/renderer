#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

Window::Window(int width, int height, const char* title) : width(width), height(height), title(title), windowedWidth(width), windowedHeight(height)
{
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    window = nullptr;
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

void Window::updateFPS()
{
    static double lastTime = glfwGetTime();
    static int frameCount = 0;
    
    double currentTime = glfwGetTime();
    frameCount++;
    
    if (currentTime - lastTime >= 1.0)
    {
        currentFPS = frameCount / (currentTime - lastTime);
        
        if (showFPS)
        {
            std::string newTitle = title + " - FPS: " + std::to_string((int)currentFPS);
            glfwSetWindowTitle(window, newTitle.c_str());
        }
        
        frameCount = 0;
        lastTime = currentTime;
    }
}

double Window::getFPS() const
{
    return currentFPS;
}

void Window::showFPSInTitle(bool show)
{
    showFPS = show;
    if (!show)
    {
        glfwSetWindowTitle(window, title.c_str());
    }
}

void Window::setVSync(bool enable)
{
    glfwSwapInterval(enable ? 1 : 0);
}

void Window::toggleFullScreen()
{
    // fullscreen = !fullscreen;
    setFullScreen(!fullscreen);
}

void Window::setFullScreen(bool fs)
{
    if (fs == fullscreen) return;

    if (fs)
    {
        glfwGetWindowPos(window, &windowedPosX, &windowedPosY);
        glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // Sets it to fullscreen
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

        width = mode->width;
        height = mode->height;
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, windowedPosX, windowedPosY, windowedWidth, windowedHeight, 0);
        width = windowedWidth;
        height = windowedHeight;
    }

    fullscreen = fs;

    if (resizeCallback)
    {
        resizeCallback(width, height);
    }
}

bool Window::isFullScreen() const
{
    return fullscreen;
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

Input& Window::getInput()
{
    return input;
}

void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (win)
    {
        win->input.updateKeyState(key, action);
    }
}

void mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (win)
    {
        win->input.updateMouseButtonState(button, action);
    }
}

void cursor_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos)
{
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (win)
    {
        win->input.updateMousePosition(xpos, ypos);
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