#include <rlEngine.hpp>
#include <Nodes/NodeCamera3D.hpp>
#include <rlgl.h>

class MainCamera : public rle::NodeCamera3D
{
protected:
    void OnUpdate(const float dt) override
    {
        if (target) LookAt(target->GetGlobalPosition(), {0.0f, 1.0f, 0.0f});
    }

public:
    MainCamera()
    {
        this->SetName("MainCamera");
        this->SetPosition({0.0f, 5.0f, 10.0f});
        this->Activate();
    }
    rle::Node3D* target{nullptr};
};

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

class BackgroundControler : public rle::Node
{
private:
    Color bg_color{BLUE};

protected:
    void OnEnterTree() override
    {
        GetScene()->SetBackgroundColor(bg_color);
    }

    void OnUpdate(const float dt) override
    {
        bg_color.b += 1;
        bg_color.r += 2;

        bg_color.b %= 254;
        bg_color.r %= 254;

        GetScene()->SetBackgroundColor(bg_color);
    }

public:
    BackgroundControler()
    {
        this->SetName("BackgroundControler");
    }
};

class GameScene : public rle::Scene
{
public:
    GameScene()
    {
        this->GetRootNode()->AddChild(std::make_unique<BackgroundControler>());
        auto camera = std::make_unique<MainCamera>();

        auto parent = std::make_unique<RotatingParent>(1.5f, RED, 1.5f);
        parent->SetName("Parent");

        auto child = std::make_unique<CubeNode>(1.0f, BLUE);
        child->SetName("Child");
        child->SetPosition({4, 0, 0});

        camera->target = (rle::Node3D*)child.get();
        parent->AddChild(std::move(child));

        this->GetRootNode()->AddChild(std::move(camera));
        this->GetRootNode()->AddChild(std::move(parent));
    }
};

int main()
{
    rle::Application app({"3D Cubes", 1280, 720, 60});
    app.SetScene(std::make_unique<GameScene>());
    app.Run();
}
