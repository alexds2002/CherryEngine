#include "basic_texture.h"

#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::string& path)
    : ID(0), width(0), height(0), nrChannels(0), filePath(path)
{
    // Load the texture from file
    if (!loadFromFile(path))
    {
        std::cerr << "Failed to load texture from file: " << path << std::endl;
    }
}

Texture::~Texture()
{
    // Delete the OpenGL texture
    glDeleteTextures(1, &ID);
}

bool Texture::loadFromFile(const std::string& path)
{
    // Generate the texture object in OpenGL
    glGenTextures(1, &ID);

    // Load the image data using stb_image
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, ID);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload the texture data to the GPU
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Generate mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the image data after uploading it to the GPU
        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        return false;
    }

    return true;
}

void Texture::bind(unsigned int unit) const
{
    // Activate the texture unit before binding
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::generate()
{
    // This method is optional. It's typically used when generating a blank texture or for procedural textures.
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Allocate space for the texture, this can be useful if you plan on dynamically filling it later
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    // Set texture parameters here as well
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
