#include "header/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "header/shader.h"
#include "header/window.h"
#include "header/metaballs.h"

int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;

void processInput();
void window_resize(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void window_resize(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

int main(){
    Window window("test window", WINDOW_WIDTH, WINDOW_HEIGHT, window_resize);

    // must be on memory, so we can free it within this scope and terminate correctly
    Metaballs* metaballs = new Metaballs(WINDOW_WIDTH, WINDOW_HEIGHT, "shader/framebuffer/shader.fs", 10.0, 0.3, 10);

    float lastTime = glfwGetTime();
    float time = glfwGetTime();
    float deltaTime;
    int fps = 0;
    while(window.isRunning()){
        fps++;
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();
        if(glfwGetTime() - time > 1){
            std::cout << "FPS: " << fps << std::endl;
            time = glfwGetTime();
            fps = 0;
        }
        //handle user input
        processInput(window.getWindow());

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //TODO: draw something
        
        metaballs->draw(deltaTime);
    
        //swap drawing buffer
        glfwSwapBuffers(window.getWindow());
        //update every event
        glfwPollEvents();
    }

    // first delete all VBOs & RBOs
    delete metaballs;
    glfwTerminate();
    return EXIT_SUCCESS;
}
