#include "Nodes/NodeCamera3D.hpp"
#include "Core/Scene.hpp"

void rle::NodeCamera3D::Activate()
{
    activate_on_enter_ = true;
    if (!GetScene()) return;
    GetScene()->SetCamera3D(&camera_);
}

void rle::NodeCamera3D::Deactivate()
{
    activate_on_enter_ = false;
    if (!GetScene()) return;
    GetScene()->SetCamera3D(nullptr);
}

void rle::NodeCamera3D::_EnterTree()
{
    if (activate_on_enter_) GetScene()->SetCamera3D(&camera_);
}

void rle::NodeCamera3D::_ExitTree()
{
    if (GetScene() && GetScene()->GetCamera3D() == &camera_)
    {
        GetScene()->SetCamera3D(nullptr);
    }
}

void rle::NodeCamera3D::_UpdateNode3D(const float dt)
{
    camera_.position = GetGlobalPosition();
    camera_.target = Vector3Add(GetGlobalPosition(), GetForward());
    camera_.up = GetUp();
}

rle::NodeCamera3D::NodeCamera3D()
{
    camera_.fovy = 70.0f;
    camera_.position = GetGlobalPosition();
    camera_.projection = CAMERA_PERSPECTIVE;
    camera_.target = Vector3Add(GetGlobalPosition(), GetForward());
    camera_.up = GetUp();
}