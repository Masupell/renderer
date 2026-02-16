#pragma once

#include <functional>
#include <string>
#include "input.hpp"

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

        void toggleFullScreen();
        void setFullScreen(bool fullscreen);
        bool isFullScreen() const;

        void setVSync(bool enable);
        void showFPSInTitle(bool show);

        float getWidth() const;
        float getHeight() const;

        void setResizeCallback(std::function<void(int, int)> callback);

        Input& getInput();

    private:
        GLFWwindow* window; 
        int width;
        int height;
        std::string title;

        bool fullscreen;
        int windowedWidth;
        int windowedHeight;
        int windowedPosX;
        int windowedPosY;

        double currentFPS = 0;
        bool showFPS = false;

        Input input;
        friend void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
        friend void mouse_button_callback(GLFWwindow*, int button, int action, int mods);
        friend void cursor_position_callback(GLFWwindow*, double xPos, double yPos);

        std::function<void(int, int)> resizeCallback;
        void updateSize(int newWidth, int newHeight);

        friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};