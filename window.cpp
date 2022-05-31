#include "header/window.h"

Window::Window(const char* title, int width, int height, void(*resize)(GLFWwindow* window, int width, int height)){

    glfwInit();
    //setting the context version, because we use version 3.3 (default is 1)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //we only want to use core functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //create window and context
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == NULL){
        std::cout << "failed to create GLFW window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    //hinde the mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    //set the viewport of the context to know where to render
    glViewport(0, 0, width, height);

    //set the size callback function
    glfwSetWindowSizeCallback(window, resize);
}

bool Window::isRunning(){
    return !glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() const {
    return this->window;
}