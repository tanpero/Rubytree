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
    size_t getSize() const;
};

template <typename T>
void RubyTree<T>::leftRotate(RubyTree<T>::Node x) {
    // 右子节点 y
    Node y = x->right;

    // 将 y 的左子树移到 x 的右子树
    x->right = y->left;
    if (y->right) {
        y->right->parent = x;  // 如果 y 的左子树非空，需要更新其父节点
    }
    // 将 y 的父节点指向 x 的父节点
    y->parent = x->parent;

    // 如果 x 是根节点，更新树的根节点
    if (!x->parent) {
        root = y;  // x 是根节点，所以 y 成为新的根节点
    } else if (x == x->parent->right) {
        x->parent->right = y;  // 如果 x 是其父节点的左子节点，将 y 设置为其父节点的左子节点
    } else {
        x->parent->left = y; // 如果 x 是其父节点的右子节点，将 y 设置为其父节点的右子节点
    }
    
    // 将 x 作为 y 的左子节点
    y->left = x;
    x->parent = y;
}

template <typename T>
void RubyTree<T>::rightRotate(RubyTree<T>::Node x) {
    // 右子节点 y
    Node y = x->right;
    
    // 将 y 的左子树移到 x 的右子树
    x->left = y->right;
    if (y->right) {
        y->right->parent = x;  // 如果 y 的左子树非空，需要更新其父节点
    }
    
    // 将 y 的父节点指向 x 的父节点
    y->parent = x->parent;
    
    // 如果 x 是根节点，更新树的根节点
    if (!x->parent) {
        root = y;  // x 是根节点，所以 y 成为新的根节点
    } else if (x == x->parent->right) {
        x->parent->right = y;  // 如果 x 是其父节点的左子节点，将 y 设置为其父节点的左子节点
    } else {
        x->parent->left = y; // 如果 x 是其父节点的右子节点，将 y 设置为其父节点的右子节点
    }
    
    // 将 x 作为 y 的左子节点
    y->right = x;
    x->parent = y;
}

template <typename T>
void RubyTree<T>::insertFixup(RubyTree<T>::Node node) {
    while (node != root && node->parent->color == Color::RED) {
        if (node->parent == node->parent->parent->left) {  // 父节点是祖父节点的左子节点
            Node uncle = node->parent->parent->right;

            // Case 1: 叔叔节点是红色
            if (uncle != nullptr && uncle->color == Color::RED) {
                // 变色
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;  // 向上调整
            } else {
                // Case 2: 当前节点是右子节点
                if (node == node->parent->right) {
                    node = node->parent;
                    leftRotate(node);  // 左旋
                }

                // Case 3: 当前节点是左子节点
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rightRotate(node->parent->parent);  // 右旋
            }
        } else {  // 父节点是祖父节点的右子节点
            Node uncle = node->parent->parent->left;

            // Case 1: 叔叔节点是红色
            if (uncle != nullptr && uncle->color == Color::RED) {
                // 变色
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;  // 向上调整
            } else {
                // Case 2: 当前节点是左子节点
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);  // 右旋
                }

                // Case 3: 当前节点是右子节点
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                leftRotate(node->parent->parent);  // 左旋
            }
        }
    }

    // 根节点保持黑色
    root->color = Color::BLACK;
}

template <typename T>
void RubyTree<T>::removeFixup(RubyTree<T>::Node x) {
    while (x != root && (x == nullptr || x->color == Color::BLACK)) {
        if (x == x->parent->left) {
            Node w = x->parent->right;  // 获取兄弟节点

            // Case 1: 兄弟节点是红色
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->parent->color = Color::RED;
                leftRotate(x->parent);  // 进行左旋
                w = x->parent->right;  // 更新 w 为新的兄弟节点
            }

            // Case 2: 兄弟节点是黑色，且兄弟的子节点也是黑色
            if ((w->left == nullptr || w->left->color == Color::BLACK) &&
                (w->right == nullptr || w->right->color == Color::BLACK)) {
                w->color = Color::RED;
                x = x->parent;  // 向上调整
            } else {
                // Case 3: 兄弟节点是黑色，且兄弟的右子节点是黑色，左子节点是红色
                if (w->right == nullptr || w->right->color == Color::BLACK) {
                    if (w->left != nullptr) {
                        w->left->color = Color::BLACK;
                    }
                    w->color = Color::RED;
                    rightRotate(w);  // 右旋
                    w = x->parent->right;  // 更新 w
                }

                // Case 4: 兄弟节点是黑色，且兄弟的右子节点是红色
                w->color = x->parent->color;
                x->parent->color = Color::BLACK;
                if (w->right != nullptr) {
                    w->right->color = Color::BLACK;
                }
                leftRotate(x->parent);  // 左旋
                x = root;  // 修复完成，退出循环
            }
        } else {  // x 是其父节点的右子节点
            Node w = x->parent->left;  // 获取兄弟节点

            // Case 1: 兄弟节点是红色
            if (w->color == Color::RED) {
                w->color = Color::BLACK;
                x->parent->color = Color::RED;
                rightRotate(x->parent);  // 进行右旋
                w = x->parent->left;  // 更新 w 为新的兄弟节点
            }

            // Case 2: 兄弟节点是黑色，且兄弟的子节点也是黑色
            if ((w->left == nullptr || w->left->color == Color::BLACK) &&
                (w->right == nullptr || w->right->color == Color::BLACK)) {
                w->color = Color::RED;
                x = x->parent;  // 向上调整
            } else {
                // Case 3: 兄弟节点是黑色，且兄弟的左子节点是黑色，右子节点是红色
                if (w->left == nullptr || w->left->color == Color::BLACK) {
                    if (w->right != nullptr) {
                        w->right->color = Color::BLACK;
                    }
                    w->color = Color::RED;
                    leftRotate(w);  // 左旋
                    w = x->parent->left;  // 更新 w
                }

                // Case 4: 兄弟节点是黑色，且兄弟的左子节点是红色
                w->color = x->parent->color;
                x->parent->color = Color::BLACK;
                if (w->left != nullptr) {
                    w->left->color = Color::BLACK;
                }
                rightRotate(x->parent);  // 右旋
                x = root;  // 修复完成，退出循环
            }
        }
    }

    if (x != nullptr) {
        x->color = Color::BLACK;
    }
}

template <typename T>
void RubyTree<T>::transplant(RubyTree<T>::Node u, RubyTree<T>::Node v) {
    if (u->parent == nullptr) {
        root = v;  // u 是根节点，直接将 v 设为根节点
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template <typename T>
typename RubyTree<T>::Node RubyTree<T>::minimum(RubyTree<T>::Node node) const {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
void RubyTree<T>::remove(RubyTree<T>::Node nodeToDelete) {
    Node y = nodeToDelete;
    Node x;
    Node xParent;

    Color yOriginalColor = y->color;  // 记录 y 的原始颜色

    // 情况 1: 如果要删除的节点有两个子节点
    if (nodeToDelete->left != nullptr && nodeToDelete->right != nullptr) {
        y = minimum(nodeToDelete->right);  // 找到右子树的最小节点
        yOriginalColor = y->color;  // 保存 y 的原始颜色
        x = y->right;  // x 是 y 的右子树

        if (y->parent == nodeToDelete) {
            xParent = y;
        } else {
            xParent = y->parent;
            transplant(y, y->right);  // 将 y 替换为其右子树
            y->right = nodeToDelete->right;
            y->right->parent = y;
        }

        // 替换 nodeToDelete 为 y
        transplant(nodeToDelete, y);
        y->left = nodeToDelete->left;
        y->left->parent = y;
        y->color = nodeToDelete->color;  // 继承 nodeToDelete 的颜色
    } else {  // 情况 2: 如果要删除的节点只有一个子节点或没有子节点
        if (nodeToDelete->left != nullptr) {
            x = nodeToDelete->left;
        } else {
            x = nodeToDelete->right;
        }

        xParent = nodeToDelete->parent;

        if (x != nullptr) {
            x->parent = xParent;
        }

        if (xParent == nullptr) {
            root = x;
        } else if (nodeToDelete == xParent->left) {
            xParent->left = x;
        } else {
            xParent->right = x;
        }

        if (nodeToDelete->color == Color::BLACK) {
            removeFixup(x);
        }
    }

}

template <typename T>
void RubyTree<T>::insert(const T& value) {
    Node newNode = std::make_shared<NodeObject>(value);
    Node parent = nullptr;
    Node current = root;

    // 找到新节点应该插入的位置
    while (current != nullptr) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // 设置新节点的父节点
    newNode->parent = parent;

    // 如果树为空，新的节点成为根节点
    if (parent == nullptr) {
        root = newNode;
    } else if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // 新节点的初始颜色是红色
    newNode->color = Color::RED;

    // 调用 insertFixUp 来修复红黑树
    insertFixup(newNode);
}

template <typename T>
void RubyTree<T>::remove(const T& value) {
    Node z = root;
    while (z) {
        if (z->value == value) {
            remove(z);
            return;
        }
        if (value < z->value) {
            z = z->left;
        } else {
            z = z->right;
        }
    }
}

template <typename T>
typename RubyTree<T>::Node RubyTree<T>::search(const T& value) const {
    Node node = root;

    while (node && node->value != value) {
        if (value < node->value) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node;
}

template <typename T>
size_t RubyTree<T>::getSize() const {
    size_t size = 0;
    auto countNodes = [&size](const Node& node) {
        if (node) {
            ++size;
            countNodes(node->left);
            countNodes(node->right);
        }
    };
    countNodes(root);  // 从根节点开始计算
    return size;
}

#endif // !_RUBYTREE_HH_