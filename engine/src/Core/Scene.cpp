#include "Core/Scene.hpp"

void rle::Scene::Input()
{
    root_node_->Input();
}

void rle::Scene::Update(const float dt)
{
    root_node_->Update(dt);
}

void rle::Scene::Render()
{
    if (active_camera3D_)
    {
        BeginMode3D(*active_camera3D_);
        root_node_->Render3D();
        EndMode3D();
    }
    if (active_camera2D_)
    {
        BeginMode2D(*active_camera2D_);
        root_node_->Render2D();
        EndMode2D();
    }
    root_node_->Render();
}

rle::Scene::Scene()
    : root_node_(std::make_unique<Node>())
{
    root_node_->scene_ = this;
    root_node_->SetName("Root");
    root_node_->EnterTree();
}

rle::Scene::~Scene()
{
    root_node_->ExitTree();
}

void rle::Scene::SetCamera3D(Camera3D camera)
{
    active_camera2D_.reset();
    active_camera3D_ = camera;
}

void rle::Scene::ResetCamera3D()
{
    active_camera3D_.reset();
}

void rle::Scene::SetCamera2D(Camera2D camera)
{
    active_camera3D_.reset();
    active_camera2D_ = camera;
}

void rle::Scene::ResetCamera2D()
{
    active_camera2D_.reset();
}

