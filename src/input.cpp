#include "input.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Input::Input() {}

void Input::updateKeyState(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        keysPressed.insert(key);
    }
    else if (action == GLFW_RELEASE)
    {
        keysPressed.erase(key);
    }
}

void Input::updateMouseButtonState(int button, int action)
{
    if (action == GLFW_PRESS)
    {
        mouseButtonsPressed.insert(button);
    }
    else if (action == GLFW_RELEASE)
    {
        mouseButtonsPressed.erase(button);
    }
}

void Input::updateMousePosition(double x, double y)
{
    mouseX = x;
    mouseY = y;
}

void Input::endFrame()
{
    prevKeysPressed = keysPressed;
    prevMouseButtonsPressed = mouseButtonsPressed;
}


bool Input::isKeyHeld(int key) const
{
    return keysPressed.contains(key);
}

bool Input::isKeyPressed(int key) const
{
    return keysPressed.contains(key) && !prevKeysPressed.contains(key);
}

bool Input::isKeyReleased(int key) const
{
    return !keysPressed.contains(key) && prevKeysPressed.contains(key);
}


bool Input::isMouseButtonHeld(int button) const
{
    return mouseButtonsPressed.contains(button);
}

bool Input::isMouseButtonPressed(int button) const
{
    return mouseButtonsPressed.contains(button) && !prevMouseButtonsPressed.contains(button);
}

bool Input::isMouseButtonReleased(int button) const
{
    return !mouseButtonsPressed.contains(button) && prevMouseButtonsPressed.contains(button);
}

std::pair<double, double> Input::getMousePosition() const
{
    return {mouseX, mouseY};
}