#include <iostream> 

template<class T>
struct TreeNode {
    T data;             //Should this just be a reference to the data object?
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
        TreeNode<T>* getNode(T obj, TreeNode<T>*);
        void insert(T obj);
        T* readMinNode();
        T* popMinNode();
        void remove(T obj);   //TODO: Different name from the specification
        void balance(TreeNode<T>*);
    
        AVLTree() {
            root = NULL;
        }
};


template <class T>              //This may require an additions parameter
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
    return &(currentNode->data);       //This right? i get address of node
}

template <class T>
T* AVLTree<T>::popMinNode() {
    TreeNode<T>* currentNode = root;
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    T* data = &(currentNode->data);               //This right? i get address of node
    remove(currentNode->data);          //This right?
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
        adder(nodeToInsert, root);
    }
        
    balance(nodeToInsert);
}


template <class T>                      //Is this necessary?
void AVLTree<T>::adder(TreeNode<T>* nodeToInsert, TreeNode<T>* currentNode) {
    if (nodeToInsert->data <= currentNode->data) {              //Comparisons may require different method
        if (currentNode->left == NULL) {
            currentNode->left = nodeToInsert;
            nodeToInsert->parent = currentNode;
        } else {
            adder(nodeToInsert, currentNode->left);
        }
    } else {
        if (currentNode->right == NULL) {
            currentNode->right = nodeToInsert;
            nodeToInsert->parent = currentNode;
        } else {
            adder(nodeToInsert, currentNode->right);
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
    
    balance(nodeToRemove->parent);
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


template <class T>
void AVLTree<T>::balance(TreeNode<T>* nodeToBalance) {
    //End function when it has gone above the parent
    if (nodeToBalance == NULL) {
        return;
    }
    
    //Get the height of right and left nodes
    int rightHeight = getHeight(nodeToBalance->right);
    int leftHeight = getHeight(nodeToBalance->left);
    
    //Rotate the tree based on 4 cases
    if (rightHeight > leftHeight + 1) {
        int rightLeftHeight = getHeight(nodeToBalance->right->left);
        int rightRightHeight = getHeight(nodeToBalance->right->right);
        if (rightRightHeight >= rightLeftHeight) {
            rotateLeft(nodeToBalance);
        } else {
            rotateRight(nodeToBalance->right);
            rotateLeft(nodeToBalance);
        }
    } else  if (rightHeight + 1 < leftHeight) {
        int leftRightHeight= getHeight(nodeToBalance->left->right);
        int leftLeftHeight= getHeight(nodeToBalance->left->left);
        if (leftLeftHeight >= leftRightHeight) {
            rotateRight(nodeToBalance);
        } else {
            rotateLeft(nodeToBalance->left);
            rotateRight(nodeToBalance);
        }
    //Update height of node to balance
    } else {
        if (leftHeight >= rightHeight) {
            nodeToBalance->height = leftHeight + 1;
        } else {
            nodeToBalance->height = rightHeight + 1;
        }
    }
    
    balance(nodeToBalance->parent);
    
}


template <class T>
int AVLTree<T>::getHeight(TreeNode<T>* node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

template <class T>
void AVLTree<T>::rotateRight(TreeNode<T>* nodeToRotate) {
    //Place new root into a temporary node
    TreeNode<T>* updatedRoot = nodeToRotate->left;
    nodeToRotate->left->parent = nodeToRotate->parent;
    
    if (nodeToRotate->parent == NULL) {
        root = updatedRoot;
    } else {
        if (nodeToRotate == nodeToRotate->parent->right) {
            nodeToRotate->parent->right = updatedRoot;
        } else {
            nodeToRotate->parent->left = updatedRoot;
        }
    }
    
    //Reassign child of new root
    nodeToRotate->left = updatedRoot->right;
    if (nodeToRotate->left != NULL) {
        nodeToRotate->left->parent = nodeToRotate;
    }
    
    updatedRoot->right = nodeToRotate;
    nodeToRotate->parent = updatedRoot;
    
    //Update the height of the original root
    int leftHeight = getHeight(nodeToRotate->left);
    int rightHeight = getHeight(nodeToRotate->right);
    if (leftHeight >= rightHeight) {
        nodeToRotate->height = leftHeight + 1;
    } else {
        nodeToRotate->height = rightHeight + 1;
    }
    
}

template <class T>
void AVLTree<T>::rotateLeft(TreeNode<T>* nodeToRotate) {
    //Place new root into a temporary node
    TreeNode<T>* updatedRoot = nodeToRotate->right;
    nodeToRotate->right->parent = nodeToRotate->parent;
    
    if (nodeToRotate->parent == NULL) {
        root = updatedRoot;
    } else {
        if (nodeToRotate == nodeToRotate->parent ->right) {
            nodeToRotate->parent->right = updatedRoot;
        } else {
            nodeToRotate->parent->left = updatedRoot;
        }
    }
    
    //Reassign child of new root
    nodeToRotate->right = updatedRoot->left;
    if (nodeToRotate->right != NULL) {
        nodeToRotate->right->parent = nodeToRotate;
    }
    
    updatedRoot->left = nodeToRotate;
    nodeToRotate->parent = updatedRoot;
    
    //Update the height of the original root
    int leftHeight = getHeight(nodeToRotate->left);
    int rightHeight = getHeight(nodeToRotate->right);
    if (leftHeight >= rightHeight) {
        nodeToRotate->height = leftHeight + 1;
    } else {
        nodeToRotate->height = rightHeight + 1;
    }
    
}

int main(int argc, const char * argv[]) {
    AVLTree<int> tree;
    
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    
    int* min = tree.readMinNode();
    int* min2 = tree.popMinNode();
    
    tree.remove(1);
    tree.remove(2);
    tree.remove(5);
    
    /*tree.insert(17);
    tree.insert(21);
    tree.insert(6);
    tree.insert(1);
    tree.insert(7);
    tree.insert(2);
    tree.insert(19);
    tree.insert(34);
    tree.remove(19);
    tree.remove(1);
    tree.remove(17);*/
    std::cout<<"Finish";
}
