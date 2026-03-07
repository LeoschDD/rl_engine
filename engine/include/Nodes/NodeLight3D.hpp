#pragma once

#include "Nodes/Node3D.hpp"
#include "rlights.h"

namespace rle
{
    class NodeLight3D : public Node3D
    {
    private:
        Light light_{};
        Shader* shader_{nullptr};

    protected:
        void _ExitTree() override;
        void _EnterTree() override;
        void _UpdateNode3D(const float dt) override;

    public:
        void SetShader(Shader* shader);

        void SetType(LightType type) {light_.type = type;}
        void SetColor(Color color) {light_.color = color;}
        void SetEnabled(bool enabled) {light_.enabled = enabled;}
        LightType GetType() {return static_cast<LightType>(light_.type);}
        Color GetColor() {return light_.color;}
        bool IsEnabled() {return light_.enabled;}
    };
}
