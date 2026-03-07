#include <rlEngine.hpp>

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

class CubeNode : public rle::NodeMesh3D
{
private:
    float scale_{};
    Color color_{};
public:
    CubeNode(float scale, Color color)
    {
        scale_ = scale;
        color_ = color;
    }
    void OnEnterTree() override
    {
        this->SetScale({scale_, scale_, scale_});
        GetMaterial().maps->color = color_;
        GetMaterial().shader = *(GetScene()->Resources()->GetShader(rle::default_lighting_shader));
    }
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

class NodeGrid : public rle::Node3D
{
protected:
    void OnRender3D() override
    {
        DrawGrid(1000, 2.0f);
    }
};

class GameScene : public rle::Scene
{
public:
    GameScene() = default;

    void OnAttach() override
    {
        auto light = std::make_unique<rle::NodeLight3D>();
        light->SetShader(Resources()->GetShader(rle::default_lighting_shader));
        light->SetPosition({10.0f, 10.0f, 10.0f});

        auto camera = std::make_unique<MainCamera>();
        
        auto parent = std::make_unique<RotatingParent>(1.5f, RED, 1.5f);
        parent->SetName("Parent");

        auto child = std::make_unique<CubeNode>(1.0f, BLUE);
        child->SetName("Child");
        child->SetPosition({4, 0, 0});

        camera->target = (rle::Node3D*)child.get();
        parent->AddChild(std::move(child));

        this->GetRootNode()->AddChild(std::move(light));
        this->GetRootNode()->AddChild(std::make_unique<BackgroundControler>());
        this->GetRootNode()->AddChild(std::move(camera));
        this->GetRootNode()->AddChild(std::move(parent));
        this->GetRootNode()->AddChild(std::make_unique<NodeGrid>());
    }
};

int main()
{
    rle::Application app({"3D Cubes", 1280, 720, 60});
    app.SetScene(std::make_unique<GameScene>());
    app.Run();
}