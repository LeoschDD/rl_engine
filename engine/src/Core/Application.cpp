#include "Core/Application.hpp"

void rle::Application::Init(const ApplicationSpecification& app_spec)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(app_spec.screen_width, app_spec.screen_height, app_spec.name.c_str());
    if (app_spec.target_fps != 0) SetTargetFPS(app_spec.target_fps);
}

rle::Application::Application(const ApplicationSpecification& app_spec)
{
    Init(app_spec);
    resources_ = std::make_unique<ResourceManager>();
}

rle::Application::~Application()
{
    if (scene_) scene_->OnDetach();
    scene_.reset();
    resources_.reset();
    CloseWindow();
}

void rle::Application::Run()
{
    while (running_)
    {
        if (WindowShouldClose()) running_ = false;
        if (!scene_)
        {
            RLE_LOG_FATAL("Run: no active scene set");
            running_ = false;
            break;
        }
        const float dt = GetFrameTime();

        scene_->Input();
        scene_->Update(dt);

        BeginDrawing();
        ClearBackground(scene_->background_color_);
        scene_->Render();
        EndDrawing();
    }
}

void rle::Application::SetScene(std::unique_ptr<Scene> scene)
{
    if (scene_) scene_->OnDetach();
    scene_ = std::move(scene);

    if (scene_) 
    {
        scene_->application_ = this;
        scene_->OnAttach();
    }
}
