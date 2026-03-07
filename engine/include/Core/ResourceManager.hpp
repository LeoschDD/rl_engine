#pragma once

#include "Core/Headers.hpp"

namespace rle
{
    class ResourceManager
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<Shader>> shaders_;

    private:
        void InitDefaultShaders();

    public:
        ResourceManager();
        ~ResourceManager();

        Shader* LoadShader(const std::string& name, const char* vsPath, const char* fsPath);
        Shader* GetShader(const std::string& name);
        bool HasShader(const std::string& name) const;
        void UnloadAll();
    };
}
