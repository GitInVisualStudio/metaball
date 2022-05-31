#ifndef SHADER_H
#define SHADER_H

#include "glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        void use();
        void setBool(const std::string &name, bool value) const;
        void setFloat(const std::string &name, float value) const;
        void setInt(const std::string &name, int value) const;
        void setMat4(const std::string &name, glm::mat4 &mat4) const;
        void setVec3(const std::string &name, glm::vec3 vec3) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec2(const std::string &name, glm::vec2 vec2) const;
};

#endif

