#pragma once

#include "Nodes/Node.hpp"

namespace rle
{
    class Node3D : public Node
    {
    private:
        Vector3 position_{};
        Quaternion rotation_{QuaternionIdentity()};
        Vector3 scale_{1.0f, 1.0f, 1.0f};
        Vector3 global_position_{};
        Quaternion global_rotation_{QuaternionIdentity()};
        Vector3 global_scale_{1.0f, 1.0f, 1.0f};

        Vector3 forward_{0.0f, 0.0f, -1.0f};
        Vector3 right_{1.0f, 0.0f, 0.0f};
        Vector3 up_{0.0f, 1.0f, 0.0f};

    protected:
        void _Update(const float dt) override;
        virtual void _UpdateNode3D(const float dt) {}

    public:
        void Translate(Vector3 offset) {position_ = Vector3Add(position_, offset);}
        void Rotate(Quaternion rotation) {rotation_ = QuaternionNormalize(QuaternionMultiply(rotation, rotation_));}
        void Rotate(Vector3 axis, float angle) {Rotate(QuaternionFromAxisAngle(axis, angle));}
        void RotateLocal(Quaternion rotation) {rotation_ = QuaternionNormalize(QuaternionMultiply(rotation_, rotation));}
        void RotateLocal(Vector3 axis, float angle) {RotateLocal(QuaternionFromAxisAngle(axis, angle));}

        void SetPosition(Vector3 position) {position_ = position;}
        void SetRotation(Quaternion rotation) {rotation_ = rotation;}
        void SetScale(Vector3 scale) {scale_ = scale;}
        Vector3 GetPosition() const {return position_;}
        Quaternion GetRotation() const {return rotation_;}
        Vector3 GetScale() const {return scale_;}
        Vector3 GetGlobalPosition() const {return global_position_;}
        Quaternion GetGlobalRotation() const {return global_rotation_;}
        Vector3 GetGlobalScale() const {return global_scale_;}

        Vector3 GetForward() const {return forward_;}
        Vector3 GetRight() const {return right_;}
        Vector3 GetUp() const {return up_;}
    };
} 
