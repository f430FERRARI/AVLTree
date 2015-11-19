#include <iostream>
#include "BinarySearchTree.cpp"  //Should this be .h?
using namespace std;

namespace BinarySearchTreeTests {

    /*
     Expected output: readMinNode = 1
     */
    bool readMinNodeTest() {
        AVLTree<int> testTree;
        testTree.insert(1);
        testTree.insert(2);
        testTree.insert(3);
        return (*testTree.readMinNode() == 1);
    }

    /*
     Expected output: readMinNode = 2
     */
    bool popMinNodeTest() {
        AVLTree<int> testTree;
        testTree.insert(1);
        testTree.insert(2);
        testTree.insert(3);
        int popped = *testTree.popMinNode();
        return ((popped = 1) && (*testTree.readMinNode() == 2));
    }

    /*
     Expected output: Root = 5, height = 2
     */
    bool rightZigZagTest() {
        AVLTree<int> testTree;
        testTree.insert(3);
        testTree.insert(6);
        testTree.insert(5);
        return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 5));
    }

    /*  
     Expected output: Root = 6, height = 2
     */
    bool rightZigZigTest(){
        AVLTree<int> testTree;
        testTree.insert(3);
        testTree.insert(6);
        testTree.insert(9);
        return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 6));

    }

    /*
     Expected output: Root = 5, height = 2
     */
    bool leftZigZagTest() {
        AVLTree<int> testTree;
        testTree.insert(6);
        testTree.insert(3);
        testTree.insert(5);
        return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 5));
    }

    /* 
     Expected output: Root = 6, height = 2
     */
    bool leftZigZigTest(){
        AVLTree<int> testTree;
        testTree.insert(9);
        testTree.insert(6);
        testTree.insert(3);
        return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 6));

    }

    /*  
     Expected output: Height = 1, root = 5
     */
    bool deleteLeafTest() {
        AVLTree<int> testTree;
        testTree.insert(6);
        testTree.insert(3);
        testTree.insert(5);
        testTree.remove(3);
        testTree.remove(6);
        return ((testTree.getRoot()->height == 1) && (testTree.getRoot()->data == 5));
    }

    /* 
     Expected output:
     */
    bool bigTreeTest(){
        AVLTree<int> testTree;
        testTree.insert(30);
        testTree.insert(6);
        testTree.insert(45);
        testTree.insert(9);
        testTree.insert(4);
        testTree.insert(3);
        testTree.insert(50);
        testTree.insert(100);
        testTree.insert(2);
        testTree.insert(1);
        testTree.insert(30);
        testTree.insert(15);
        testTree.remove(45);
        testTree.remove(1);
        testTree.remove(30);
        testTree.remove(4);
        return true;
    }

    void runTests() {
        readMinNodeTest() ? cout << "Pass" << endl : cout << "readMinNodeTest Fail" << endl;
        popMinNodeTest() ? cout << "Pass" << endl : cout << "popMinNodeTest Fail" << endl;
        rightZigZagTest() ? cout << "Pass" << endl : cout << "rightZigZagTest Fail" << endl;
        rightZigZigTest() ? cout << "Pass" << endl : cout << "rightZigZigTest Fail" << endl;
        leftZigZagTest() ? cout << "Pass" << endl : cout << "leftZigZagTest Fail" << endl;
        leftZigZigTest() ? cout << "Pass" << endl : cout << "leftZigZigTest Fail" << endl;
        deleteLeafTest() ? cout << "Pass" << endl : cout << "deleteLeafTest Fail" << endl;
        bigTreeTest() ? cout << "Pass" << endl : cout << "bigTreeTest Fail" << endl;
    }

}

int main() {
    BinarySearchTreeTests::runTests();
    return 0;
}