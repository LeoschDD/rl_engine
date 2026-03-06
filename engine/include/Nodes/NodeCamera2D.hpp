#pragma once

#include "Nodes/Node2D.hpp"
#include "Core/Scene.hpp"

namespace rle
{
    class NodeCamera2D : public Node2D
    {
    private:
        Camera2D camera_{};
        bool activate_on_enter_{false};

    protected:
        void _UpdateNode2D(const float dt) override;
        void _EnterTree() override;
        void _ExitTree() override;

    public:
        NodeCamera2D();

        void Activate();
        void Deactivate();

        void SetZoom(float zoom) {camera_.zoom = zoom;}
        float GetZoom() {return camera_.zoom;}
        Camera2D& GetCamera() {return camera_;}
    };
}