#include "header/metaballs.h"
#include <glm/gtc/random.hpp>
#include <glm/gtx/string_cast.hpp>
#include <ctime>

Metaballs::Metaballs(int width, int height, const char* fs_shader, float scale, float threshold, int length) {

    if (length > MAX_BALL_LENGTH) {
        throw std::invalid_argument("length should not be greater than MAX_BALL_LENGTH");
    }

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    const float vertices[] = { 
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    
    unsigned int VBO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    shader = new Shader("shader/framebuffer/shader.vs", fs_shader);
    shader->use();
    shader->setInt("screenTexture", 0);

    //set random seed
    srand(time(0));

    
    for (int i = 0; i < length; i++) {
        std::string index = "[" + std::to_string(i) + "]";
        balls.push_back(glm::circularRand(0.5));
        velocity.push_back(glm::circularRand(1.0));
        shader->setVec2("balls" + index, balls[i]);
        float r = rand() / (float)RAND_MAX; //random value between 0 and 1
        radius.push_back(0.3 + r * 0.5);
        shader->setFloat("radius" + index, radius[i]);
    }

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

    for (int i = 0; i < length; i++) {
        std::string index = current + "[" + std::to_string(i) + "]";
        shader->setVec2(index, balls[i]);
    }

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Metaballs::update(float dt) {
    for (int i = 0; i < balls.size(); i++) {
        //TODO: check if out of bound
        balls[i] += velocity[i] * dt / 5.0f;
        float r = radius[i] / scale;

        if (balls[i].x < -1 + r || balls[i].x > 1 - r) {
            velocity[i] = glm::vec2(-velocity[i].x, velocity[i].y);
        }

        if (balls[i].y < -1 + r || balls[i].y > 1 - r) {
            velocity[i] = glm::vec2(velocity[i].x, -velocity[i].y);
        }
    }
}