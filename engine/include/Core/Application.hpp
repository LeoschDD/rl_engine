#pragma once

#include "Core/Headers.hpp"
#include "Core/Scene.hpp"
#include "Core/ResourceManager.hpp"

namespace rle
{
    struct ApplicationSpecification
    {
        std::string name;
        int screen_width;
        int screen_height;
        int target_fps{60};
    };

    class Application
    {
    private:
        bool running_{true};
        std::unique_ptr<Scene> scene_;
        std::unique_ptr<ResourceManager> resources_;

    private:
        void Init(const ApplicationSpecification& app_spec);

    public:
        Application(const ApplicationSpecification& app_spec);
        ~Application();

        void Run();

        [[nodiscard]] Scene* GetScene() {return scene_.get();}
        void SetScene(std::unique_ptr<Scene> scene);
        ResourceManager* Resources() {return resources_.get();}
    };
}
