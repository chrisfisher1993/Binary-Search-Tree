#include <iostream>
#include <vector>

class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* _insert(TreeNode* node, int key) {
        if (node == nullptr) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = _insert(node->left, key);
        } else if (key > node->key) {
            node->right = _insert(node->right, key);
        }

        return node;
    }

    TreeNode* _search(TreeNode* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return _search(node->left, key);
        }

        return _search(node->right, key);
    }

    TreeNode* _delete(TreeNode* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = _delete(node->left, key);
        } else if (key > node->key) {
            node->right = _delete(node->right, key);
        } else {
            if (node->left == nullptr) {
                return node->right;
            } else if (node->right == nullptr) {
                return node->left;
            }

            node->key = _minValue(node->right);
            node->right = _delete(node->right, node->key);
        }

        return node;
    }

    int _minValue(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node->key;
    }

    void _inorderTraversal(TreeNode* node, std::vector<int>& result) {
        if (node != nullptr) {
            _inorderTraversal(node->left, result);
            result.push_back(node->key);
            _inorderTraversal(node->right, result);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key) {
        root = _insert(root, key);
    }

    TreeNode* search(int key) {
        return _search(root, key);
    }

    void deleteNode(int key) {
        root = _delete(root, key);
    }

    std::vector<int> inorderTraversal() {
        std::vector<int> result;
        _inorderTraversal(root, result);
        return result;
    }
};

int main() {
    BinarySearchTree bst;
    std::vector<int> nodes = {50, 30, 20, 40, 70, 60, 80};

    for (int node : nodes) {
        bst.insert(node);
    }

    std::cout << "Inorder traversal: ";
    for (int val : bst.inorderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    int searchKey = 40;
    std::cout << "Search for " << searchKey << ": " << (bst.search(searchKey) ? "Found" : "Not Found") << std::endl;

    bst.deleteNode(40);
    
    std::cout << "Inorder traversal after deleting " << searchKey << ": ";
    for (int val : bst.inorderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
