#include "renderer2D.h"
#include "basic_texture.h"

// IMPORTANT define: This tells the compiler to include the implementation of stb_image
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>

Renderer2D::Renderer2D(const char* vertexShaderPath, const char* fragmentShaderPath, const glm::mat4& projection)
    : shader(vertexShaderPath, fragmentShaderPath)
{
    // Initialize the shader and set projection matrix
    shader.use();
    shader.setMat4("uProjection", projection);
    initRenderData();
}

Renderer2D::~Renderer2D()
{
    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer2D::initRenderData()
{
    // Define quad vertices and texture coordinates
    float vertices[] = {
        // positions   // texture coords
         0.5f,  0.5f,  1.0f, 1.0f, // top right
         0.5f, -0.5f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
        -0.5f,  0.5f,  0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Generate and bind VAO, VBO, and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Texture& texture)
{
    // Activate the shader
    shader.use();

    // Model matrix for the quad
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    shader.setMat4("uModel", model);

    // Bind texture using the Texture class
    texture.bind();

    // Render the quad
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
