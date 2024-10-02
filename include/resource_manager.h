#pragma once

#include "../core/render/basic_texture.h"

#include <memory>
#include <string>
#include <unordered_map>

/*
 * ResourseManager currently loads all the resourses from the assets/ folder into RAM.
 * TODO(Alex): Make assets automatically load and unload based on when they are used.
 */

class ResourceManager
{
public:
    ResourceManager();

    std::shared_ptr<Texture> GetTexturePtr(const std::string& name);
    Texture& GetTexture(const std::string& name);

private:
    /*
     * Loads all resources from assets folders.
     */
    void LoadResources();

    std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
};

