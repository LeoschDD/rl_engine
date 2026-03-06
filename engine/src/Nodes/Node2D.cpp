#include "Nodes/Node2D.hpp"

void rle::Node2D::_Update(const float dt)
{
    if (Node2D* parent = dynamic_cast<Node2D*>(GetParent()))
    {
        Vector2 scaled_pos = Vector2Multiply(position_, parent->GetGlobalScale());
        float cos = std::cos(parent->GetGlobalRotation());
        float sin = std::sin(parent->GetGlobalRotation());
        global_position_.x = parent->GetGlobalPosition().x + scaled_pos.x * cos - scaled_pos.y * sin;
        global_position_.y = parent->GetGlobalPosition().y + scaled_pos.x * sin + scaled_pos.y * cos;
        global_rotation_ = parent->GetGlobalRotation() + rotation_;
        global_scale_ = Vector2Multiply(parent->GetGlobalScale(), scale_);
    }
    else
    {
        global_position_ = position_;
        global_rotation_ = rotation_;
        global_scale_ = scale_;
    }

    forward_ = {std::cos(global_rotation_), std::sin(global_rotation_)};
    right_ = {std::sin(global_rotation_), -std::cos(global_rotation_)};
    _UpdateNode2D(dt);
}



