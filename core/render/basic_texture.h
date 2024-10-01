#pragma once

#include <glad/gl.h>
#include <string>

class Texture
{
public:
    unsigned int ID;           // OpenGL texture ID
    int width, height;         // Texture dimensions
    int nrChannels;            // Number of channels (RGB/RGBA)
    std::string filePath;      // Path to the texture file

    // Constructor to load and create a texture from a file
    Texture(const std::string& path);
    ~Texture();

    // Binds the texture
    void bind(unsigned int unit = 0) const;

private:
    bool loadFromFile(const std::string& path);
    void generate();
};
