#include <iostream> 

struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

template<class T> class AVLTree {
    private:
        TreeNode* root;
    public:
        void insert(T obj);
        void addHelper(TreeNode*, TreeNode*);
        void remove(T obj);
        AVLTree() {
            root = NULL;
        }
};

template<class T> void AVLTree::insert(T data) {
    TreeNode* nodeToInsert = new TreeNode();
    nodeToInsert->data = data;
    nodeToInsert->left = nodeToInsert->right = NULL;
        
    if (root == NULL){
        root = nodeToInsert;
    } else {
        addHelper(TreeNode* node, TreeNode* currentNode);
    }
        
    balance(nodeToInsert);
}

void AVLTree::addHelper(TreeNode* nodeToInsert, TreeNode* currentNode) {
    if (nodeToInsert->data <= currentNode->data) {
        if (currentNode->left == NULL) {
            currentNode->left = nodeToInsert;
            nodeToInsert-> = currentNode;
        } else {
            addHelper(nodeToInsert, currentNode->left);
        }
    } else {
        if (currentNode->right == NULL) {
            currentNode->right = nodeToInsert;
            nodeToInsert->parent = currentNode;
        } else {
            addHelper(nodeToInsert, currentNode->right);
        }
    }
}

int main(int argc, const char * argv[]) {
    AVLTree<int> tree;
    tree.insert<int>(2);
}


