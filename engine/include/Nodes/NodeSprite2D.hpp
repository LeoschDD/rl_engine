#pragma once

#include "Nodes/Node2D.hpp"

namespace rle
{
    class NodeSprite2D : public Node2D
    {
    private:
        Texture2D texture_{};
        Rectangle source_rectangle_{};

    public:
        ~NodeSprite2D() override { if (texture_.id != 0) UnloadTexture(texture_); }

        void SetTexture(Texture2D texture) {texture_ = texture;}
        void SetSourceRect(Rectangle rect) {source_rectangle_ = rect;}
        Texture2D GetTexture() const {return texture_;}

    protected:
        void _Render2D() override;
    };
}
