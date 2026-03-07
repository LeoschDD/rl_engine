#include "Nodes/NodeSprite2D.hpp"

rle::NodeSprite2D::~NodeSprite2D()
{
    if (texture_.id != 0) UnloadTexture(texture_); 
}

void rle::NodeSprite2D::_Render2D()
{
    Rectangle destination_rectangle = {
        GetGlobalPosition().x, GetGlobalPosition().y, 
        source_rectangle_.width, source_rectangle_.height};

    DrawTexturePro(texture_, source_rectangle_, destination_rectangle, {0.0f, 0.0f}, GetGlobalRotation() * RAD2DEG, WHITE);
}