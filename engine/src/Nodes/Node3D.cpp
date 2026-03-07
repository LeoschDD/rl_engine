#include "Nodes/Node3D.hpp"

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
    global_rotation_ = QuaternionNormalize(global_rotation_);
    
    forward_ = Vector3RotateByQuaternion({0.0f, 0.0f, -1.0f}, global_rotation_);
    right_ = Vector3RotateByQuaternion({1.0f, 0.0f, 0.0f}, global_rotation_);
    up_ = Vector3RotateByQuaternion({0.0f, 1.0f, 0.0f}, global_rotation_);
    _UpdateNode3D(dt);
}

void rle::Node3D::LookAt(Vector3 target, Vector3 up)
{
    Vector3 dir = Vector3Subtract(target, position_);
    if (Vector3Length(dir) < 0.0001f) return;
    dir = Vector3Normalize(dir);
    Vector3 back = Vector3Negate(dir);
    Vector3 right = Vector3CrossProduct(up, back);
    if (Vector3Length(right) < 0.0001f) return;
    right = Vector3Normalize(right);
    Vector3 orthogonal_up = Vector3CrossProduct(back, right);

    Matrix m = {
        right.x, orthogonal_up.x, back.x, 0,
        right.y, orthogonal_up.y, back.y, 0,
        right.z, orthogonal_up.z, back.z, 0,
        0,       0,               0,      1
    };
    rotation_ = QuaternionFromMatrix(m);
}

Matrix rle::Node3D::GetGlobalTransformMatrix()
{
    Matrix transform = MatrixIdentity();
    transform = MatrixMultiply(transform, MatrixScale(GetGlobalScale().x, GetGlobalScale().y, GetGlobalScale().z));
    transform = MatrixMultiply(transform, QuaternionToMatrix(GetGlobalRotation()));
    transform = MatrixMultiply(transform, MatrixTranslate(GetGlobalPosition().x, GetGlobalPosition().y, GetGlobalPosition().z));
    return transform;
}