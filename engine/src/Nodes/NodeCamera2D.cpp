#include "Nodes/NodeCamera2D.hpp"
#include "Core/Scene.hpp"

void rle::NodeCamera2D::Activate()
{
    activate_on_enter_ = true;
    if (!GetScene()) return;
    GetScene()->SetCamera2D(&camera_);
}

void rle::NodeCamera2D::Deactivate()
{
    activate_on_enter_ = false;
    if (!GetScene()) return;
    GetScene()->SetCamera2D(nullptr);
}

void rle::NodeCamera2D::_EnterTree()
{
    if (activate_on_enter_) GetScene()->SetCamera2D(&camera_);
}

void rle::NodeCamera2D::_ExitTree()
{
    if (GetScene() && GetScene()->GetCamera2D() == &camera_) 
    {
        GetScene()->SetCamera2D(nullptr);
    }
}

void rle::NodeCamera2D::_UpdateNode2D(const float dt)
{
    camera_.offset = {GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f};
    camera_.rotation = GetGlobalRotation() * RAD2DEG;
    camera_.target = GetGlobalPosition();
}

rle::NodeCamera2D::NodeCamera2D()
{
    camera_.offset = {GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f};
    camera_.rotation = GetGlobalRotation() * RAD2DEG;
    camera_.target = GetGlobalPosition();
    camera_.zoom = 1.0f;
}