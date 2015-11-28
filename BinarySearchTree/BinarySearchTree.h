#ifndef BinarySearchTree_h
#define BinarySearchTree_h

template<class T, class S>
struct TreeNode {
    T* obj;
    S data;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};


template<class T, class S>
class AVLTree {
private:
    TreeNode<T,S>* root;
    void removeLeaf(TreeNode<T,S>*);
    void removeLeft(TreeNode<T,S>*);
    void removeRight(TreeNode<T,S>*);
    void removeBoth(TreeNode<T,S>*);
    void adder(TreeNode<T,S>*, TreeNode<T,S>*);
    int getHeight(TreeNode<T,S>*);
    void rotateRight(TreeNode<T,S>*);
    void rotateLeft(TreeNode<T,S>*);
public:
    TreeNode<T,S>* getRoot();
    TreeNode<T,S>* getNode(T*, S, TreeNode<T,S>*);
    void insert(T*, S);
    T* readMinNode();
    T* popMinNode();
    void remove(T*, S);
    void balance(TreeNode<T,S>*);
    
    AVLTree() {
        root = NULL;
    }
};


template <class T, class S>
TreeNode<T,S>* AVLTree<T,S>::getRoot(){
    return root;
}


template <class T, class S>
TreeNode<T,S>* AVLTree<T,S>::getNode(T* objectToFind, S data, TreeNode<T,S>* currentNode){
    if(currentNode == NULL) {
        return NULL;
    } else if (currentNode->obj == objectToFind) {
        return currentNode;
    } else if (data < currentNode->data){
        return getNode(objectToFind, data, currentNode->left);
    } else {
        return getNode(objectToFind, data, currentNode->right);
    }
}


template <class T, class S>
T* AVLTree<T,S>::readMinNode() {
    TreeNode<T,S>* currentNode = root;
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    return currentNode->obj;
}


template <class T, class S>
T* AVLTree<T,S>::popMinNode() {
    TreeNode<T,S>* currentNode = root;
    while (currentNode->left != NULL) {
        currentNode = currentNode->left;
    }
    T* output = currentNode->obj;
    remove(currentNode->obj, currentNode->data);
    return output;
}


template <class T, class S>
void AVLTree<T,S>::insert(T* obj, S data) {
    TreeNode<T,S>* nodeToInsert = new TreeNode<T,S>();
    nodeToInsert->obj = obj;
    nodeToInsert->data = data;
    nodeToInsert->left = nodeToInsert->right = NULL;
    
    if (root == NULL){
        root = nodeToInsert;
    } else {
        adder(nodeToInsert, root);
    }
    
    balance(nodeToInsert);
}


template <class T, class S>
void AVLTree<T,S>::adder(TreeNode<T,S>* nodeToInsert, TreeNode<T,S>* currentNode) {
    if (nodeToInsert->data <= currentNode->data) {
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


template <class T, class S>
void AVLTree<T,S>::remove(T* obj, S data) {
    TreeNode<T,S>* nodeToRemove = getNode(obj, data, root);
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


template <class T, class S>
void AVLTree<T,S>::removeLeaf(TreeNode<T,S>* nodeToRemove) {
    if (nodeToRemove->parent == NULL) {
        root = NULL;
    } else if (nodeToRemove == nodeToRemove->parent->right) {
        nodeToRemove->parent->right = NULL;
    } else {
        nodeToRemove->parent->left = NULL;
    }
    
    delete nodeToRemove;
}


template <class T, class S>
void AVLTree<T,S>::removeRight(TreeNode<T,S>* nodeToRemove) {
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


template <class T, class S>
void AVLTree<T,S>::removeLeft(TreeNode<T,S>* nodeToRemove) {
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


template <class T, class S>
void AVLTree<T,S>::removeBoth(TreeNode<T,S>* nodeToRemove) {
    //Find a valid node to swap with the node to remove
    TreeNode<T,S>* replacement = nodeToRemove->left;
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


template <class T, class S>
void AVLTree<T,S>::balance(TreeNode<T,S>* nodeToBalance) {
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


template <class T, class S>
int AVLTree<T,S>::getHeight(TreeNode<T,S>* node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}


template <class T, class S>
void AVLTree<T,S>::rotateRight(TreeNode<T,S>* nodeToRotate) {
    //Place new root into a temporary node
    TreeNode<T,S>* updatedRoot = nodeToRotate->left;
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


template <class T, class S>
void AVLTree<T,S>::rotateLeft(TreeNode<T,S>* nodeToRotate) {
    //Place new root into a temporary node
    TreeNode<T,S>* updatedRoot = nodeToRotate->right;
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

#endif