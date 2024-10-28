#pragma once

#include "basic_shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Texture;

class Renderer2D
{
public:
    Renderer2D() = default;
    ~Renderer2D();

    bool Init(const char* vertexShaderPath, const char* fragmentShaderPath, const glm::mat4& projection);
    void drawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture> texture);

private:
    void initRenderData();

    unsigned int VAO, VBO, EBO;
    Shader m_shader;
};

