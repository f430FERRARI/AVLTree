#include <iostream>
#include "BinarySearchTree.h"   
#include "BinarySearchTreeTests.h"
#include "TestThread.h"

using namespace std;

/*  
 Expected output: readMinNode = 1
 */
bool BinarySearchTreeTests::readMinNodeTest() {
    AVLTree<TestThread, int> testTree;
    TestThread one (1,1);
    TestThread two (2,2);
    TestThread three (3,3);

    testTree.insert(&one,1);
    testTree.insert(&two,2);
    testTree.insert(&three,3);
    return testTree.readMinNode() == &one;
}

/*
 Expected output: readMinNode = 2
 */
bool BinarySearchTreeTests::popMinNodeTest() {
    AVLTree<TestThread, int> testTree;
    TestThread one (1,1);
    TestThread two (2,2);
    TestThread three (3,3);
    
    testTree.insert(&one,1);
    testTree.insert(&two,2);
    testTree.insert(&three,3);
    TestThread* popped = testTree.popMinNode();
    return ((popped = &one) && (testTree.readMinNode() == &two));
}

/*
 Expected output: Root = 5, height = 2
 */
bool BinarySearchTreeTests::rightZigZagTest() {
    AVLTree<TestThread, int> testTree;
    TestThread three (3,3);
    TestThread six (6,6);
    TestThread five (5,5);

    testTree.insert(&three,3);
    testTree.insert(&six,6);
    testTree.insert(&five,5);
    return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 5));
}

/*
 Expected output: Root = 6, height = 2
 */
bool BinarySearchTreeTests::rightZigZigTest(){
    AVLTree<TestThread, int> testTree;
    TestThread three (3,3);
    TestThread six(6,6);
    TestThread nine (9,9);

    testTree.insert(&three,3);
    testTree.insert(&six,6);
    testTree.insert(&nine,9);
    return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 6));
    
}

/*
 Expected output: Root = 5, height = 2
 */
bool BinarySearchTreeTests::leftZigZagTest() {
    AVLTree<TestThread, int> testTree;
    TestThread six (6,6);
    TestThread three (3,3);
    TestThread five (5,5);
    
    testTree.insert(&six,6);
    testTree.insert(&three,3);
    testTree.insert(&five,5);
    return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 5));
}

/*
 Expected output: Root = 6, height = 2
 */
bool BinarySearchTreeTests::leftZigZigTest(){
    AVLTree<TestThread, int> testTree;
    TestThread nine (9,9);
    TestThread six (6,6);
    TestThread three (3,3);

    
    testTree.insert(&nine,9);
    testTree.insert(&six,6);
    testTree.insert(&three,3);
    return ((testTree.getRoot()->height == 2) && (testTree.getRoot()->data == 6));
    
}

/*
 Expected output: Height = 1, root = 5
 */
bool BinarySearchTreeTests::deleteLeafTest() {
    AVLTree<TestThread, int> testTree;
    TestThread five (5,5);
    TestThread six (6,6);

    testTree.insert(&five,5);
    testTree.insert(&six, 6);
    testTree.remove(&six,6);
    return ((testTree.getRoot()->height == 1) && (testTree.getRoot()->data == 5));
}


/*
 Expected output: Root = 30, height = 4
 */
bool BinarySearchTreeTests::bigTreeInsertDeleteAllCasesTest(){
    AVLTree<TestThread, int> testTree;
    TestThread thirty (30,30);
    TestThread six (6,6);
    TestThread fortyfive (45,45);
    TestThread nine (9,9);
    TestThread four (4,4);
    TestThread three (3,3);
    TestThread fifty (50,50);
    TestThread hundred (100,100);
    TestThread one (1,1);
    TestThread fifteen (15,15);

    
    testTree.insert(&thirty,30);
    testTree.insert(&six,6);
    testTree.insert(&fortyfive,45);
    testTree.insert(&nine,9);
    testTree.insert(&four,4);
    testTree.insert(&three,3);
    testTree.insert(&fifty,50);
    testTree.insert(&hundred,100);
    testTree.insert(&one,1);
    testTree.insert(&thirty,30);
    testTree.insert(&fifteen,15);
    testTree.remove(&fortyfive,45);
    testTree.remove(&one,1);
    testTree.remove(&thirty,30);
    testTree.remove(&four,4);
    return ((testTree.getRoot()->height==4) && (testTree.getRoot()->data == 30));
}

void BinarySearchTreeTests::runTests() {
    readMinNodeTest() ? cout << "Pass" << endl : cout << "readMinNodeTest Fail" << endl;
    popMinNodeTest() ? cout << "Pass" << endl : cout << "popMinNodeTest Fail" << endl;
    rightZigZagTest() ? cout << "Pass" << endl : cout << "rightZigZagTest Fail" << endl;
    rightZigZigTest() ? cout << "Pass" << endl : cout << "rightZigZigTest Fail" << endl;
    leftZigZagTest() ? cout << "Pass" << endl : cout << "leftZigZagTest Fail" << endl;
    leftZigZigTest() ? cout << "Pass" << endl : cout << "leftZigZigTest Fail" << endl;
    deleteLeafTest() ? cout << "Pass" << endl : cout << "deleteLeafTest Fail" << endl;
    bigTreeInsertDeleteAllCasesTest() ? cout << "Pass" << endl : cout << "bigTreeTest Fail" << endl;
}
