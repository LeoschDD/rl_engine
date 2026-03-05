#pragma once

#include "Nodes/Node.hpp"
#include <optional>

namespace rle
{
    class Application;

    class Scene
    {
    private:
        friend class Application;

        std::unique_ptr<Node> root_node_;
        Color background_color_{WHITE};

        std::optional<Camera3D> active_camera3D_;
        std::optional<Camera2D> active_camera2D_;

    private:
        void Input();
        void Update(const float dt);
        void Render();

    protected:
        Scene();

    public:
        virtual ~Scene();

        [[nodiscard]] Node* GetRootNode() {return root_node_.get();}
        void SetBackgroundColor(Color color) {background_color_ = color;}

        Camera3D* GetCamera3D() {return active_camera3D_ ? &*active_camera3D_ : nullptr;}
        void SetCamera3D(Camera3D camera);
        void ResetCamera3D();
        Camera2D* GetCamera2D() {return active_camera2D_ ? &*active_camera2D_ : nullptr;}
        void SetCamera2D(Camera2D camera);
        void ResetCamera2D();
    };
}
