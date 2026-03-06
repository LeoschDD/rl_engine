#include "Core/ResourceManager.hpp"

rle::ResourceManager::~ResourceManager()
{
    UnloadAll();
}

Shader& rle::ResourceManager::LoadShader(const std::string& name, const char* vsPath, const char* fsPath)
{
    auto it = shaders_.find(name);
    if (it != shaders_.end())
    {
        RLE_LOG_WARN("LoadShader: shader '%s' already loaded, returning existing", name.c_str());
        return it->second;
    }
    Shader shader = ::LoadShader(vsPath, fsPath);
    auto [inserted, success] = shaders_.emplace(name, shader);
    return inserted->second;
}

Shader& rle::ResourceManager::GetShader(const std::string& name)
{
    auto it = shaders_.find(name);
    if (it == shaders_.end())
    {
        RLE_LOG_FATAL("GetShader: shader '%s' not found", name.c_str());
        static Shader fallback{};
        return fallback;
    }
    return it->second;
}

bool rle::ResourceManager::HasShader(const std::string& name) const
{
    return shaders_.contains(name);
}

void rle::ResourceManager::UnloadAll()
{
    for (auto& [name, shader] : shaders_)
    {
        ::UnloadShader(shader);
    }
    shaders_.clear();
}
