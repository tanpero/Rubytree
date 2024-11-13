#ifndef _RUBYTREE_HH_
#define _RUBYTREE_HH_

#include <memory>

enum class Color { RED, BLACK };

template <typename T>
class RubyTree {
private:
    struct NodeObject {
        T value;
        Color color;
        std::shared_ptr<NodeObject> left, right, parent;

        explicit NodeObject(T value)
            : value(value), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    using Node = std::shared_ptr<NodeObject>;

    Node root;

    void leftRotate(Node x);
    void rightRotate(Node x);
    void insertFixup(Node node);
    void transplant(Node u, Node v);
    void removeFixup(Node x);
    Node minimum(Node node) const;
    void remove(Node nodeToDelete);
public:
    RubyTree() : root(nullptr) {}
    void insert(const T& value);
    void remove(const T& value);
    Node search(const T& value) const;
};


#endif // !_RUBYTREE_HH_