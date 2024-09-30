#pragma once

#include "basic_shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer2D {
public:
    Renderer2D(const char* vertexShaderPath, const char* fragmentShaderPath, const glm::mat4& projection);
    ~Renderer2D();

    void drawQuad(const glm::vec2& position, const glm::vec2& size, unsigned int textureID);
    void loadTexture(const char* texturePath);
    unsigned int loadTextureFromFile(const char* path);

private:
    unsigned int VAO, VBO, EBO;
    Shader shader;
    unsigned int texture;

    void initRenderData();
};

