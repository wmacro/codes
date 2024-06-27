#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(int x) : val(x), left(NULL), right(NULL), height(1) {}
};

class AVLTree {
public:
    AVLTree() : root(NULL) {}

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

    int height(TreeNode* node) {
        return node == NULL ? 0 : node->height;
    }

    int getBalance(TreeNode* node) {
        return node == NULL ? 0 : height(node->left) - height(node->right);
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    TreeNode* insert(TreeNode* node, int val) {
        if (node == NULL) {
            return new TreeNode(val);
        }
        if (val < node->val) {
            node->left = insert(node->left, val);
        } else if (val > node->val) {
            node->right = insert(node->right, val);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && val < node->left->val) {
            return rightRotate(node);
        }
        if (balance < -1 && val > node->right->val) {
            return leftRotate(node);
        }
        if (balance > 1 && val > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && val < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
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
            if ((node->left == NULL) || (node->right == NULL)) {
                TreeNode* temp = node->left ? node->left : node->right;
                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                TreeNode* temp = minValueNode(node->right);
                node->val = temp->val;
                node->right = remove(node->right, temp->val);
            }
        }

        if (node == NULL) {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != NULL) {
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
    AVLTree tree;
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
