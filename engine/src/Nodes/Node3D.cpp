#include "Node3D.hpp"

void rle::Node3D::_Update(const float dt)
{
    if (Node3D* parent = dynamic_cast<Node3D*>(GetParent()))
    {
        Vector3 scaled_pos = Vector3Multiply(position_, parent->GetGlobalScale());
        global_position_ = Vector3Add(Vector3RotateByQuaternion(scaled_pos, parent->GetGlobalRotation()), parent->GetGlobalPosition());
        global_rotation_ = QuaternionMultiply(parent->global_rotation_, rotation_);
        global_scale_ = Vector3Multiply(parent->GetGlobalScale(), scale_);
    }
    else
    {
        global_position_ = position_;
        global_rotation_ = rotation_;
        global_scale_ = scale_;
    }

    forward_ = Vector3RotateByQuaternion({1.0f, 0.0f, 0.0f}, global_rotation_);
    right_ = Vector3RotateByQuaternion({0.0f, 0.0f, 1.0f}, global_rotation_);
    up_ = Vector3RotateByQuaternion({0.0f, 1.0f, 0.0f}, global_rotation_);
    _UpdateNode3D(dt);
}