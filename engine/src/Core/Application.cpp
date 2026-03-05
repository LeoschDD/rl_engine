#include "Core/Application.hpp"

void rle::Application::Init(const ApplicationSpecification& app_spec)
{
    InitWindow(app_spec.screen_width, app_spec.screen_height, app_spec.name.c_str());
    InitAudioDevice();
    if (app_spec.target_fps != 0) SetTargetFPS(app_spec.target_fps);
}

rle::Application::Application(const ApplicationSpecification& app_spec)
{
    Init(app_spec);
}

rle::Application::~Application()
{
    scene_.reset();
    CloseAudioDevice();
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
