#include "Nodes/Node.hpp"

void rle::Node::EnterTree()
{
    if (parent_) scene_ = parent_->scene_;
    in_tree_ = true;
    _EnterTree();
    OnEnterTree();
    for (auto& child : children_)
    {
        child->EnterTree();
    }
}

void rle::Node::ExitTree()
{
    in_tree_ = false;
    _ExitTree();
    OnExitTree();
    for (auto& child : children_) 
    {
        child->ExitTree();
    }
}

void rle::Node::Input()
{
    if (!active_) return;
    _Input();
    OnInput();
    for (auto& child : children_) 
    {
        child->Input();
    }
}

void rle::Node::Update(const float dt)
{
    if (!active_) return;
    _Update(dt);
    OnUpdate(dt);
    for (auto& child : children_)
    {
        child->Update(dt);
    }
}

void rle::Node::Render()
{
    if (!active_) return;
    _Render();
    OnRender();
    for (auto& child : children_)
    {
        child->Render();
    }
}

void rle::Node::Render2D()
{
    if (!active_) return;
    _Render2D();
    OnRender2D();
    for (auto& child : children_)
    {
        child->Render2D();
    }
}

void rle::Node::Render3D()
{
    if (!active_) return;
    _Render3D();
    OnRender3D();
    for (auto& child : children_)
    {
        child->Render3D();
    }
}

bool rle::Node::HasAncestor(const Node* ancestor) const
{
    const Node* current = parent_;
    while (current != nullptr)
    {
        if (current == ancestor) return true;
        current = current->parent_;
    }
    return false;
}

void rle::Node::SetParent(Node* parent)
{
    if (parent == nullptr)
    { 
        RLE_LOG_ERROR("SetParent: parent must not be null"); 
        return; 
    }
    if (parent == this)
    {
        RLE_LOG_ERROR("SetParent: a node cannot be its own parent"); 
        return; 
    }
    if (parent->HasAncestor(this)) 
    { 
        RLE_LOG_ERROR("SetParent: circular hierarchy detected"); 
        return; 
    }
    if (parent_ == parent) return;

    if (!parent_)
    {
        RLE_LOG_ERROR("SetParent: node has no current parent, use AddChild() instead");
        return;
    }

    auto& siblings = parent_->children_;
    auto it = std::find_if(siblings.begin(), siblings.end(),
        [this](const auto& c) { return c.get() == this; });
    if (it == siblings.end())
    {
        RLE_LOG_ERROR("SetParent: node not found in current parent's children");
        return;
    }

    std::unique_ptr<Node> self = std::move(*it);
    siblings.erase(it);

    self->parent_ = parent;
    self->scene_  = parent->scene_;
    parent->children_.push_back(std::move(self));
}

void rle::Node::AddChild(std::unique_ptr<Node> child)
{
    if (!child)                        
    {
        RLE_LOG_ERROR("AddChild: child must not be null"); 
        return; 
    }
    if (child.get() == this)
    {
        RLE_LOG_ERROR("AddChild: a node cannot be its own child"); 
        return; 
    }
    if (child->HasAncestor(this))
    {
        RLE_LOG_ERROR("AddChild: circular hierarchy detected"); 
        return; 
    }
    child->parent_ = this;
    child->scene_ = scene_;
    children_.push_back(std::move(child));
    if (in_tree_)
        children_.back()->EnterTree();
}

void rle::Node::RemoveChild(Node* child)
{
    if (!child) 
    { 
        RLE_LOG_WARN("RemoveChild: child is null"); 
        return; 
    }
    auto it = std::find_if(children_.begin(), children_.end(),
        [child](const auto& c) { return c.get() == child; });

    if (it == children_.end()) 
    { 
        RLE_LOG_WARN("RemoveChild: node is not a child of this node"); 
        return; 
    }
    (*it)->ExitTree();
    children_.erase(it);
}

rle::Node* rle::Node::GetChild(const std::string& name) const
{
    for (const auto& child : children_)
    {
        if (child->name_ == name)
            return child.get();
    }
    return nullptr;
}
