#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BST {
public:
    BST() : root(NULL) {}

    void insert(int val) {
        root = insert(root, val);
    }

    bool search(int val) {
        return search(root, val);
    }

    void remove(int val) {
        root = remove(root, val);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int val) {
        if (node == NULL) {
            return new TreeNode(val);
        }
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    bool search(TreeNode* node, int val) {
        if (node == NULL) {
            return false;
        }
        if (val == node->val) {
            return true;
        } else if (val < node->val) {
            return search(node->left, val);
        } else {
            return search(node->right, val);
        }
    }

    TreeNode* remove(TreeNode* node, int val) {
        if (node == NULL) {
            return node;
        }
        if (val < node->val) {
            node->left = remove(node->left, val);
        } else if (val > node->val) {
            node->right = remove(node->right, val);
        } else {
            if (node->left == NULL) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->right);
            node->val = temp->val;
            node->right = remove(node->right, temp->val);
        }
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    void inorder(TreeNode* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->val << " ";
            inorder(node->right);
        }
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder traversal: ";
    tree.inorder();

    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 25: " << (tree.search(25) ? "Found" : "Not Found") << endl;

    tree.remove(20);
    cout << "Inorder traversal after deleting 20: ";
    tree.inorder();

    tree.remove(30);
    cout << "Inorder traversal after deleting 30: ";
    tree.inorder();

    tree.remove(50);
    cout << "Inorder traversal after deleting 50: ";
    tree.inorder();

    return 0;
}
