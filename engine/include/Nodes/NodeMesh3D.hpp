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
        ~NodeMesh3D();

        void SetMesh(const Mesh& mesh) {UnloadMesh(mesh_); mesh_ = mesh;}
        void SetMaterial(const Material& material) {RL_FREE(material_.maps); material_ = material;}
        Mesh& GetMesh() {return mesh_;}
        Material& GetMaterial() {return material_;}
    };
}