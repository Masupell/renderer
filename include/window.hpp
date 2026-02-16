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

        void updateFPS();
        double getFPS() const;

        void setVSync(bool enable);
        void showFPSInTitle(bool show);

        float getWidth() const;
        float getHeight() const;

        void setResizeCallback(std::function<void(int, int)> callback);

    private:
        GLFWwindow* window; 
        int width;
        int height;
        std::string title;

        double currentFPS = 0;
        bool showFPS = false;

        std::function<void(int, int)> resizeCallback;
        void updateSize(int newWidth, int newHeight);

        friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};