#include "Nodes/NodeMesh3D.hpp"

void rle::NodeMesh3D::_Render3D()
{
    auto transform = this->GetGlobalTransformMatrix();
    DrawMesh(mesh_, material_, transform);
}

rle::NodeMesh3D::~NodeMesh3D()
{
    RL_FREE(material_.maps);
    UnloadMesh(mesh_);
}
