#include "header/metaballs.h"
#include <glm/gtc/random.hpp>
#include <glm/gtx/string_cast.hpp>
#include <ctime>

Metaballs::Metaballs(int width, int height, const char* fs_shader, float scale, float threshold, int length) {

    if (length > MAX_BALL_LENGTH) {
        throw std::invalid_argument("length should not be greater than MAX_BALL_LENGTH");
    }
    
    /**
     * create Render Buffer Object and Vertex Buffer Object
     */
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


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
    
    unsigned int VBO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /**
     * load the data in the GPU
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /**
     * load the data according to our shader format, first location is our position, which consists of 2 float values
     */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    /**
     * now load the color data correctly
     */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    shader = new Shader("shader/shader.vs", fs_shader);
    shader->use();

    //set random seed
    srand(time(0));
    
    /**
     * initiate all the arrays and push em into the shader
     */
    for (int i = 0; i < length; i++) {
        std::string index = "[" + std::to_string(i) + "]";

        // ball have a random starting position
        balls.push_back(glm::circularRand(0.5));

        //random velocity per ball, magnitude 1
        velocity.push_back(glm::circularRand(1.0));
        shader->setVec2("balls" + index, balls[i]);

        //random radius per ball
        float r = rand() / (float)RAND_MAX; //random value between 0 and 1
        radius.push_back(0.3 + r * 0.5);
        shader->setFloat("radius" + index, radius[i]);
    }

    /**
     * load the current constants into the shader
     */
    shader->setFloat("scale", scale);
    shader->setFloat("threshold", threshold);
    shader->setFloat("ball_length", length);

    this->scale = scale;
    this->threshold = threshold;
    this->length = length;
}

Metaballs::~Metaballs() {
    delete this->shader;
    glDeleteRenderbuffers(1, &RBO);
    glDeleteVertexArrays(1, &VAO);
}

void Metaballs::draw(float dt) {
    update(dt);
    shader->use();

    std::string current = "balls";

    /**
     * push the new ball positions to the shader
     */
    for (int i = 0; i < length; i++) {
        std::string index = current + "[" + std::to_string(i) + "]";
        shader->setVec2(index, balls[i]);
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Metaballs::update(float dt) {
    /**
     * update the balls position, check for boundaries 
     */
    for (int i = 0; i < balls.size(); i++) {
        // update position at constant rate 
        balls[i] += velocity[i] * dt / 5.0f;
        // scale the radius
        float r = radius[i] / scale;

        //TODO: check if out of bound and revers the velocity if so
        if (balls[i].x < -1 + r || balls[i].x > 1 - r) {
            velocity[i] = glm::vec2(-velocity[i].x, velocity[i].y);
        }

        if (balls[i].y < -1 + r || balls[i].y > 1 - r) {
            velocity[i] = glm::vec2(velocity[i].x, -velocity[i].y);
        }
    }
}