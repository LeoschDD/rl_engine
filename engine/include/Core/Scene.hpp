#pragma once

#include "Nodes/Node.hpp"

namespace rle
{
    class Application;
    class ResourceManager;

    class Scene
    {
    private:
        friend class Application;

        Application* application_{nullptr};
        std::unique_ptr<Node> root_node_;
        Color background_color_{WHITE};

        Camera3D* active_camera3D_{nullptr};
        Camera2D* active_camera2D_{nullptr};

    private:
        void Input();
        void Update(const float dt);
        void Render();

    protected:
        virtual void OnAttach() {}
        virtual void OnDetach() {}

    public:
        Scene();
        virtual ~Scene();

        [[nodiscard]] Node* GetRootNode() {return root_node_.get();}
        void SetBackgroundColor(Color color) {background_color_ = color;}

        Camera3D* GetCamera3D() {return active_camera3D_;}
        Camera2D* GetCamera2D() {return active_camera2D_;}
        void SetCamera3D(Camera3D* camera);
        void SetCamera2D(Camera2D* camera);

        ResourceManager* Resources();
    };
}
