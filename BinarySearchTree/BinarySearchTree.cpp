#include <iostream> 

template<class T>
struct TreeNode {
    T data;             //Should this just be a reference to the data object?
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
    public:
        TreeNode<T>* getNode(T obj, TreeNode<T>*);
        void insert(T obj);
        void addHelper(TreeNode<T>*, TreeNode<T>*);
        T* readMinNode();
        T* popMinNode();
        void remove(T obj);   //TODO: Different name from the specification
    
    
        /*void balance(TreeNode*);
        void rotateRight(TreeNode*);
        void rotateLeft(TreeNode*);*/
    
        AVLTree() {
            root = NULL;
        }
};


template <class T>                                             //This may require an additions parameter
TreeNode<T>* AVLTree<T>::getNode(T obj, TreeNode<T>* currentNode){
    if(currentNode == NULL) {
        return NULL;
    } else if (currentNode->data == obj) {
        return currentNode;
    } else if (obj < currentNode->data){
        return getNode(obj, currentNode->left);
    } else {
        return getNode(obj, currentNode->right);
    }
}

template <class T>
    T* AVLTree<T>::readMinNode() {
    TreeNode<T>* currentNode = root;
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    return &(currentNode->data);       //This right?
}

template <class T>
T* AVLTree<T>::popMinNode() {
    TreeNode<T>* currentNode = root;
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    T* data = &(currentNode->data);               //This right?
    remove(currentNode);
    return data;
}

template <class T>
void AVLTree<T>::insert(T obj) {
    TreeNode<T>* nodeToInsert = new TreeNode<T>();
    nodeToInsert->data = obj;
    nodeToInsert->left = nodeToInsert->right = NULL;
        
    if (root == NULL){
        root = nodeToInsert;
    } else {
        addHelper(nodeToInsert, root);
    }
        
    //balance(nodeToInsert);
}


template <class T>                      //Is this necessary?
void AVLTree<T>::addHelper(TreeNode<T>* nodeToInsert, TreeNode<T>* currentNode) {
    if (nodeToInsert->data <= currentNode->data) {              //Comparisons may require different method
        if (currentNode->left == NULL) {
            currentNode->left = nodeToInsert;
            nodeToInsert->parent = currentNode;
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


template <class T>
void AVLTree<T>::remove(T obj) {
    TreeNode<T>* nodeToRemove = getNode(obj, root);
    if (nodeToRemove == NULL) {
        return;
    }
    
    if (nodeToRemove->left == NULL && nodeToRemove->right == NULL) {
        removeLeaf(nodeToRemove);
    } else if (nodeToRemove->left == NULL) {
        removeRight(nodeToRemove);
    } else if (nodeToRemove->right == NULL) {
        removeLeft(nodeToRemove);
    } else {
        removeBoth(nodeToRemove);
    }
    
    //balance(nodeToRemove->parent);
}

template <class T>
void AVLTree<T>::removeLeaf(TreeNode<T>* nodeToRemove) {
    if (nodeToRemove->parent == NULL) {
        root = NULL;
    } else if (nodeToRemove == nodeToRemove->parent->right) {
        nodeToRemove->parent->right = NULL;
    } else {
        nodeToRemove->parent->left = NULL;
    }
    
    delete nodeToRemove;
}


template <class T>
void AVLTree<T>::removeRight(TreeNode<T>* nodeToRemove) {
    if (nodeToRemove->parent == NULL) {
        root = nodeToRemove->right;
        nodeToRemove->right->parent = NULL;
    } else if (nodeToRemove == nodeToRemove->parent->right) {
        nodeToRemove->parent->right = nodeToRemove->right;
        nodeToRemove->right->parent = nodeToRemove->parent;
    } else {
        nodeToRemove->parent->left = nodeToRemove->right;
        nodeToRemove->right->parent = nodeToRemove->parent;
    }
    
    delete nodeToRemove;
}


template <class T>
void AVLTree<T>::removeLeft(TreeNode<T>* nodeToRemove) {
    if (nodeToRemove->parent == NULL) {
        root = nodeToRemove->left;
        nodeToRemove->left->parent = NULL;
    } else if (nodeToRemove == nodeToRemove->parent->right) {
        nodeToRemove->parent->right = nodeToRemove->left;
        nodeToRemove->left->parent = nodeToRemove->parent;
    } else {
        nodeToRemove->parent->left = nodeToRemove->left;
        nodeToRemove->left->parent = nodeToRemove->parent;
    }
    
    delete nodeToRemove;
}


template <class T>
void AVLTree<T>::removeBoth(TreeNode<T>* nodeToRemove) {
    //Find a valid node to swap with the node to remove
    TreeNode<T>* replacement = nodeToRemove->left;
    while (replacement->right != NULL) {
        replacement = replacement->right;
    }
    
    //Swap data in replacement with node to remove
    nodeToRemove->data = replacement->data;
    
    //Update pointers for replacement node
    if (replacement->parent->right == replacement) {
        replacement->parent->right = replacement->left;
    } else {
        replacement->parent->left = replacement->left;
    }
    
    if (replacement->left != NULL) {
        replacement->left->parent = replacement->parent;
    }
    
    delete replacement;
}


int main(int argc, const char * argv[]) {
    AVLTree<int> tree;
    tree.insert(17);
    tree.insert(21);
    tree.insert(6);
    tree.insert(1);
    tree.insert(7);
    tree.insert(2);
    tree.insert(19);
    tree.insert(34);
    
    tree.remove(19);
    tree.remove(1);
    tree.remove(17);
    std::cout<<"Finish";
}
