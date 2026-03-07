#include "Core/ResourceManager.hpp"

void rle::ResourceManager::InitDefaultShaders()
{
    // Load and setup lighting shader
    auto lighting_shader = this->LoadShader("rle_lighting", 
        TextFormat(RESOURCE_DIR "/shaders/lighting.vs"), 
        TextFormat(RESOURCE_DIR "/shaders/lighting.fs"));

    lighting_shader->locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(*lighting_shader, "viewPos");
    int ambient_location = GetShaderLocation(*lighting_shader, "ambient");
    float ambient_value[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    SetShaderValue(*lighting_shader, ambient_location, ambient_value, SHADER_UNIFORM_VEC4);
}

rle::ResourceManager::ResourceManager() 
{
    InitDefaultShaders();
}

rle::ResourceManager::~ResourceManager()
{
    UnloadAll();
}

Shader* rle::ResourceManager::LoadShader(const std::string& name, const char* vsPath, const char* fsPath)
{
    auto it = shaders_.find(name);
    if (it != shaders_.end())
    {
        RLE_LOG_WARN("LoadShader: shader '%s' already loaded, returning existing", name.c_str());
        return it->second.get();
    }
    Shader shader = ::LoadShader(vsPath, fsPath);
    auto [inserted, success] = shaders_.emplace(name, std::make_unique<Shader>(shader));
    return inserted->second.get();
}

Shader* rle::ResourceManager::GetShader(const std::string& name)
{
    auto it = shaders_.find(name);
    if (it == shaders_.end())
    {
        RLE_LOG_FATAL("GetShader: shader '%s' not found", name.c_str());
        return nullptr;
    }
    return it->second.get();
}

bool rle::ResourceManager::HasShader(const std::string& name) const
{
    return shaders_.contains(name);
}

void rle::ResourceManager::UnloadAll()
{
    for (auto& [name, shader] : shaders_)
    {
        ::UnloadShader(*shader);
    }
    shaders_.clear();
}
