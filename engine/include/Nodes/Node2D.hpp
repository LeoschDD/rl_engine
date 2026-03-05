#pragma once

#include "Nodes/Node.hpp"

namespace rle
{
    class Node2D : public Node
    {
    private:
        Vector2 position_{};
        float rotation_{0.0f};
        Vector2 global_position_{};
        float global_rotation_{0.0f};

    protected:
        void _Update(const float dt) override;
        virtual void _UpdateNode2D(const float dt) {}

    public:
        void SetPosition(Vector2 pos) {position_ = pos;}
        void SetRotation(float rot) {rotation_ = rot;}
        Vector2 GetPosition() const {return position_;}
        float GetRotation() const {return rotation_;}
        Vector2 GetGlobalPosition() const {return global_position_;}
        float GetGlobalRotation() const {return global_rotation_;}
    };
}
