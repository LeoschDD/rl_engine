#include <rlEngine.hpp>
#include <Nodes/NodeCamera3D.hpp>
#include <rlgl.h>

class CubeNode : public rle::Node3D
{
    float size_;
    Color color_;

protected:
    void OnRender3D() override
    {
        Vector3 pos = GetGlobalPosition();
        Quaternion rot = GetGlobalRotation();
        Vector3 scl = GetGlobalScale();

        Vector3 axis;
        float angle;
        QuaternionToAxisAngle(rot, &axis, &angle);

        rlPushMatrix();
            rlTranslatef(pos.x, pos.y, pos.z);
            rlRotatef(angle * RAD2DEG, axis.x, axis.y, axis.z);
            rlScalef(scl.x, scl.y, scl.z);
            DrawCube({0, 0, 0}, size_, size_, size_, color_);
            DrawCubeWires({0, 0, 0}, size_, size_, size_, BLACK);
        rlPopMatrix();
    }

public:
    CubeNode(float size, Color color) : size_(size), color_(color) {}
};

class RotatingParent : public CubeNode
{
    float speed_;

protected:
    void OnUpdate(const float dt) override
    {
        Rotate({0, 1, 0}, speed_ * dt);
    }

public:
    RotatingParent(float size, Color color, float speed)
        : CubeNode(size, color), speed_(speed) {}
};

int main()
{
    rle::Application app({"3D Cubes", 1280, 720, 60});
    auto scene = std::make_unique<rle::Scene>();
    scene->SetBackgroundColor(DARKGRAY);

    // Camera: look from (0,5,10) toward the origin
    auto camera = std::make_unique<rle::NodeCamera3D>();
    camera->SetName("Camera");
    camera->SetPosition({0, 5, 10});

    camera->Rotate({1, 0, 0}, -0.46f);
    camera->Activate();

    // Parent cube: rotating at origin
    auto parent = std::make_unique<RotatingParent>(1.5f, RED, 1.5f);
    parent->SetName("Parent");

    // Child cube: offset from parent
    auto child = std::make_unique<CubeNode>(1.0f, BLUE);
    child->SetName("Child");
    child->SetPosition({4, 0, 0});

    parent->AddChild(std::move(child));

    scene->GetRootNode()->AddChild(std::move(camera));
    scene->GetRootNode()->AddChild(std::move(parent));

    app.SetScene(std::move(scene));
    app.Run();
}
