#include "Nodes/NodeMesh3D.hpp"

void rle::NodeMesh3D::_Render3D()
{
    auto transform = this->GetGlobalTransformMatrix();
    DrawMesh(mesh_, material_, transform);
}
