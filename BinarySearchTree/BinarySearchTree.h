#include <iostream>

template<class T>
struct TreeNode {
    T data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

template<class T>
class AVLTree {
private:
    TreeNode<T>* root;
    void removeLeaf(TreeNode<T>*);
    void removeLeft(TreeNode<T>*);
    void removeRight(TreeNode<T>*);
    void removeBoth(TreeNode<T>*);
    void adder(TreeNode<T>*, TreeNode<T>*);
    int getHeight(TreeNode<T>*);
    void rotateRight(TreeNode<T>*);
    void rotateLeft(TreeNode<T>*);
public:
    TreeNode<T>* getRoot();
    TreeNode<T>* getNode(T obj, TreeNode<T>*);
    void insert(T obj);
    T* readMinNode();
    T* popMinNode();
    void remove(T obj);
    void balance(TreeNode<T>*);
    
    AVLTree() {
        root = NULL;
    }
};