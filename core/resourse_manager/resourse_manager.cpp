#include <resource_manager.h>
#include "../render/basic_texture.h"

#include <filesystem>
#include <iostream>

ResourceManager::ResourceManager()
{
}

// Loads all resources from the assets folder
// Currently supports only texutres
void ResourceManager::LoadResources()
{
    // The path to the assets folder
    std::string path_to_data = "../assets";

    for(const auto& cur_path : std::filesystem::recursive_directory_iterator(path_to_data))
    {
        // skip folder names
        if(std::filesystem::is_directory(cur_path)) { continue; }

        std::shared_ptr<Texture> texture = std::make_shared<Texture>("../assets/" + cur_path.path().filename().string());
        if(m_textures.count(cur_path.path().filename().string()) == 0)
        {
            // TODO(Alex): asssosiate the textures with a key different then their name
            m_textures[cur_path.path().filename().string()] = texture;
        }
    }
}

std::shared_ptr<Texture> ResourceManager::GetTexturePtr(const std::string& name)
{
    if (m_textures.count(name) == 0)
    {
        std::cerr << "Error: Texture " << name << " not found in resource manager." << std::endl;
        return nullptr;  // Return empty shared_ptr
    }
    return m_textures[name];
}

Texture& ResourceManager::GetTexture(const std::string& name)
{
    return *(m_textures[name].get());
}
