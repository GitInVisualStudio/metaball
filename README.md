# About

This repo is simple approche to draw metaballs with the help of OpenGL. Nothing special and purely educational.

<img src="https://i.imgur.com/J2LQ3Fn.png" alt="preview" width="300"/>

You can change the number of balls and other factors easily in ```main.cpp:34``` 

```c++
Metaballs* metaballs = new Metaballs(
    WINDOW_WIDTH, WINDOW_HEIGHT, "./shader/shader.fs",
    10.0,   //scale
    0.2,    //threshold determines the line width
    10      //number of balls
);
```

If you want to change the gradient displayed, you'll need to change the vertex color data in ```metaballs.cpp:24```.

```c++
/**
 * first 2 values are the vertices, following 3 values is the color at that point
 */
const float vertices[] = { 
    -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
};
```
# Setup

First install all the necessary dependencies: 
```make install```

This should install everything, now you can simple run:
```make run```
to compile and run the project.

# Sources

Checkout [Reducible](https://www.youtube.com/watch?v=6oMZb3yP_H8) for his amazing explanation about implicit functions and metaballs.

If you want to better understand the OpenGL code written in this repo, checkout [Joey de Vries](https://learnopengl.com/) blog about OpenGL, it's truly amazing and helped me alot.
