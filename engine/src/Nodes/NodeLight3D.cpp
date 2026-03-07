#include "Nodes/NodeLight3D.hpp"
#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

void rle::NodeLight3D::_ExitTree()
{
    light_.enabled = false;
}

void rle::NodeLight3D::_EnterTree()
{
    light_.enabled = true;
}

void rle::NodeLight3D::_UpdateNode3D(const float dt)
{
    light_.position = GetGlobalPosition();
    light_.target = Vector3Add(GetGlobalPosition(), GetForward());
    if (shader_) UpdateLightValues(*shader_, light_);
}

void rle::NodeLight3D::SetShader(Shader* shader)
{
    if (!shader) 
    {
        RLE_LOG_WARN("SetShader: shader is null");
        return;
    }
    shader_ = shader;
    light_ = CreateLight(LIGHT_POINT, GetGlobalPosition(), Vector3Add(GetGlobalPosition(), GetForward()), WHITE, *shader_);
}
