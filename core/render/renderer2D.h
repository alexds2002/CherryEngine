#pragma once

#include "basic_shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Texture;

class Renderer2D
{
public:
    Renderer2D(const char* vertexShaderPath, const char* fragmentShaderPath, const glm::mat4& projection);
    ~Renderer2D();

    void drawQuad(const glm::vec2& position, const glm::vec2& size, const Texture& texture);

private:
    unsigned int VAO, VBO, EBO;
    Shader shader;

    void initRenderData();
};

