#pragma once

#include <functional>
#include <string>

struct GLFWwindow;

class Window
{
    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool shouldClose() const;
        
        void pollEvents();
        void swapBuffer();

        float getWidth() const;
        float getHeight() const;

        void setResizeCallback(std::function<void(int, int)> callback);

    private:
        GLFWwindow* window; 
        int width;
        int height;

        std::function<void(int, int)> resizeCallback;
        void updateSize(int newWidth, int newHeight);

        friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};