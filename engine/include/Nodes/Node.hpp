#pragma once

#include "Core/Headers.hpp"

namespace rle
{
    class Scene;

    class Node
    {
    private:
        friend class Scene;

        Scene* scene_{nullptr};
        Node* parent_{nullptr};
        std::vector<std::unique_ptr<Node>> children_;
        bool active_{true};
        bool in_tree_{false};
        std::string name_;

    private:
        // Recursive lifecycle functions called by Scene that cascade through the tree.
        // Not meant to be called directly
        void EnterTree();
        void ExitTree();
        void Input();
        void Update(const float dt);
        void Render();
        void Render2D();
        void Render3D();

        [[nodiscard]] bool HasAncestor(const Node* ancestor) const;

    protected:
        // Engine-internal hooks, intended for built-in node types
        // Called before the user-facing On* hooks.
        virtual void _EnterTree() {}
        virtual void _ExitTree() {}
        virtual void _Input() {}
        virtual void _Update(const float dt) {}
        virtual void _Render() {}
        virtual void _Render2D() {}
        virtual void _Render3D() {}

    protected:
        // User-overridable lifecycle hooks.
        // Override these in your own node subclasses to add behaviour.
        virtual void OnEnterTree() {}
        virtual void OnExitTree() {}
        virtual void OnInput() {}
        virtual void OnUpdate(const float dt) {}
        virtual void OnRender() {}
        virtual void OnRender2D() {}
        virtual void OnRender3D() {}

    public:
        Node() = default;
        virtual ~Node() = default;

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node& operator=(Node&&) = delete;

        void SetParent(Node* parent);
        [[nodiscard]] Node* GetParent() const {return parent_;}

        void AddChild(std::unique_ptr<Node> child);
        std::unique_ptr<Node> DetachChild(Node* child);
        std::unique_ptr<Node> DetachSelf();
        void RemoveChild(Node* child);
        [[nodiscard]] Node* GetChild(const std::string& name) const;

        [[nodiscard]] const std::vector<std::unique_ptr<Node>>& GetChildren() const {return children_;}
        [[nodiscard]] bool IsActive() const {return active_;}
        [[nodiscard]] bool IsInTree() const {return in_tree_;}
        [[nodiscard]] const std::string& GetName() const {return name_;}

        void SetActive(bool active) {active_ = active;}
        void SetName(const std::string& name) {name_ = name;}
        Scene* GetScene() {return scene_;}
        const Scene* GetScene() const {return scene_;}
    };
}
