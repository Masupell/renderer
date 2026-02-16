#pragma once

#include <unordered_set>
#include <utility>

struct GLFWwindow;

class Input
{
    public:
        Input();

        void updateKeyState(int key, int action);
        void updateMouseButtonState(int button, int action);
        void updateMousePosition(double x, double y);

        void endFrame();

        bool isKeyHeld(int key) const;
        bool isKeyPressed(int key) const;
        bool isKeyReleased(int key) const;

        bool isMouseButtonHeld(int button) const;
        bool isMouseButtonPressed(int button) const;
        bool isMouseButtonReleased(int button) const;

        std::pair<double, double> getMousePosition() const;
    
    private:
        std::unordered_set<int> keysPressed;
        std::unordered_set<int> prevKeysPressed;

        std::unordered_set<int> mouseButtonsPressed;
        std::unordered_set<int> prevMouseButtonsPressed;

        double mouseX;
        double mouseY;
};