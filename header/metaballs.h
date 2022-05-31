#ifndef METABALLS_H
#define METABALLS_H

#include "shader.h"
#include <vector>

#define MAX_BALL_LENGTH 32

class Metaballs {

    private:
        unsigned int VAO;
        unsigned int RBO;
        int length;
        float scale;
        float threshold;
        Shader* shader;
        std::vector<float> radius; 
        std::vector<glm::vec2> balls;
        std::vector<glm::vec2> velocity;         
        void update(float dt);

    public:
        Metaballs(int width, int height, const char* fs_shader, float scale=10, float threshold=0.5, int length=5);
        ~Metaballs();
        void draw(float dt);
};

#endif