#pragma once

#include "Nodes/Node3D.hpp"

namespace rle
{
    class NodeMesh3D : public Node3D
    {
    private:
        Mesh mesh_{GenMeshCube(1.0f, 1.0f, 1.0f)};
        Material material_{LoadMaterialDefault()};
        
    protected:
        void _Render3D() override;

    public:
        void SetMesh(const Mesh& mesh) {mesh_ = mesh;}
        void SetMaterial(const Material& material) {material_ = material;}
    };
}