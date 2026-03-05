#include "Nodes/Node2D.hpp"

void rle::Node2D::_Update(const float dt)
{
    if (Node2D* parent = dynamic_cast<Node2D*>(GetParent()))
    {
        float cos = std::cos(parent->global_rotation_);
        float sin = std::sin(parent->global_rotation_);
        global_position_.x = parent->global_position_.x + position_.x * cos - position_.y * sin;
        global_position_.y = parent->global_position_.y + position_.x * sin + position_.y * cos;
        global_rotation_ = parent->global_rotation_ + rotation_;
    }
    else 
    {
        global_position_ = position_;
        global_rotation_ = rotation_;
    }
    _UpdateNode2D(dt);
}



