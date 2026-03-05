#include <rlEngine.hpp>

static constexpr float TILE_W = 80.0f;
static constexpr float TILE_H = 110.0f;
static constexpr float GRAVITY = 900.0f;
static constexpr float JUMP_FORCE = -450.0f;
static constexpr float MOVE_SPEED = 250.0f;

static std::vector<Rectangle> g_platforms;

class Player : public rle::NodeSprite2D
{
private:
    float velocity_y_{0.0f};
    bool on_ground_{false};

protected:
    void OnUpdate(const float dt) override
    {
        Vector2 pos = GetPosition();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) pos.x -= MOVE_SPEED * dt;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) pos.x += MOVE_SPEED * dt;
        if (on_ground_ && IsKeyPressed(KEY_SPACE)) velocity_y_ = JUMP_FORCE;

        Rectangle rect = {pos.x, GetPosition().y, TILE_W, TILE_H};
        for (const auto& plat : g_platforms)
        {
            if (CheckCollisionRecs(rect, plat))
            {
                if (pos.x < GetPosition().x) pos.x = plat.x + plat.width;
                else pos.x = plat.x - TILE_W;
                rect.x = pos.x;
            }
        }

        velocity_y_ += GRAVITY * dt;
        pos.y += velocity_y_ * dt;

        on_ground_ = false;
        rect = {pos.x, pos.y, TILE_W, TILE_H};
        for (const auto& plat : g_platforms)
        {
            if (CheckCollisionRecs(rect, plat))
            {
                if (velocity_y_ > 0)
                {
                    pos.y = plat.y - TILE_H;
                    velocity_y_ = 0;
                    on_ground_ = true;
                }
                else
                {
                    pos.y = plat.y + plat.height;
                    velocity_y_ = 0;
                }
                rect.y = pos.y;
            }
        }

        SetPosition(pos);

        Camera2D* cam = GetScene()->GetCamera2D();
        if (cam) cam->target = {pos.x + TILE_W / 2.0f, pos.y + TILE_H / 2.0f};
    }
};

class PlatformRenderer : public rle::Node2D
{
protected:
    void OnRender2D() override
    {
        for (const auto& plat : g_platforms)
            DrawRectangleRec(plat, DARKGREEN);
    }
};

class GameScene : public rle::Scene
{
public:
    GameScene()
    {
        SetBackgroundColor(SKYBLUE);

        Camera2D cam{};
        cam.offset = {400.0f, 300.0f};
        cam.target = {400.0f, 300.0f};
        cam.zoom = 1.0f;
        SetCamera2D(cam);

        g_platforms = {
            {-200.0f, 500.0f, 1600.0f, 40.0f},
            {250.0f, 400.0f, 200.0f, 20.0f},
            {550.0f, 320.0f, 200.0f, 20.0f},
            {50.0f, 240.0f, 200.0f, 20.0f},
            {400.0f, 160.0f, 200.0f, 20.0f},
            {800.0f, 400.0f, 150.0f, 20.0f},
            {1000.0f, 300.0f, 200.0f, 20.0f},
        };

        auto platforms = std::make_unique<PlatformRenderer>();
        platforms->SetName("Platforms");
        GetRootNode()->AddChild(std::move(platforms));

        Texture2D tex = LoadTexture("../../application/resources/assets/player_tilesheet.png");
        auto player = std::make_unique<Player>();
        player->SetName("Player");
        player->SetTexture(tex);
        player->SetSourceRect({0.0f, 0.0f, TILE_W, TILE_H});
        player->SetPosition({100.0f, 380.0f});
        GetRootNode()->AddChild(std::move(player));
    }
};

int main()
{
    rle::ApplicationSpecification spec{"Platformer", 800, 600, 60};
    rle::Application app(spec);
    app.SetScene(std::make_unique<GameScene>());
    app.Run();
}
