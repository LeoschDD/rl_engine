#pragma once

#include "Nodes/Node3D.hpp"
#include "Core/Scene.hpp"

namespace rle
{
    class NodeCamera3D : public Node3D
    {
    private:
        Camera3D camera_{};
        bool activate_on_enter_{false};

    protected:
        void _UpdateNode3D(const float dt) override;
        void _EnterTree() override;
        void _ExitTree() override;

    public:
        NodeCamera3D();

        void Activate();
        void Deactivate();

        void SetFov(float fov) {camera_.fovy = fov;}
        float GetFov() {return camera_.fovy;}
        Camera3D& GetCamera() {return camera_;}
    };
}