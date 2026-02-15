#pragma once

struct GLFWwindow;

class Window
{
    public:
        Window(int width, int height, const char* title);
        ~Window();

        bool shouldClose() const;
        
        void pollEvents();
        void swapBuffer();

        int getWidth() const;
        int getHeight() const;

    private:
        GLFWwindow* window;
        int width;
        int height;
};