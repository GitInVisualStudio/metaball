#ifndef WINDOW_H
#define WINDOW_H

#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Window{
    private:
        GLFWwindow* window;
        void processInput();
        void (*resize)(GLFWwindow* window, int width, int height);

    public:
        Window(const char* title, int width, int height, void(*resize)(GLFWwindow* window, int width, int height));
        bool isRunning();
        GLFWwindow* getWindow() const;
};

#endif