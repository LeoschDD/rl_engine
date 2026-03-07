#pragma once

#include "Nodes/Node.hpp"

namespace rle
{
    class Node2D : public Node
    {
    private:
        Vector2 position_{};
        float rotation_{0.0f};
        Vector2 scale_{1.0f, 1.0f};
        Vector2 global_position_{};
        float global_rotation_{0.0f};
        Vector2 global_scale_{1.0f, 1.0f};

        Vector2 right_{1.0f, 0.0f};
        Vector2 up_{0.0f, -1.0f};

    protected:
        void _Update(const float dt) override;
        virtual void _UpdateNode2D(const float dt) {}

    public:
        void UpdateGlobalTransform();

        void Translate(Vector2 offset) {position_ = Vector2Add(position_, offset);}
        void Rotate(float angle) {rotation_ += angle;}
        void LookAt(Vector2 target);

        void SetPosition(Vector2 position) {position_ = position;}
        void SetRotation(float rotation) {rotation_ = rotation;}
        void SetScale(Vector2 scale) {scale_ = scale;}
        Vector2 GetPosition() const {return position_;}
        float GetRotation() const {return rotation_;}
        Vector2 GetScale() const {return scale_;}
        Vector2 GetGlobalPosition() const {return global_position_;}
        float GetGlobalRotation() const {return global_rotation_;}
        Vector2 GetGlobalScale() const {return global_scale_;}

        Vector2 GetRight() const {return right_;}
        Vector2 GetUp() const {return up_;}
    };
}
