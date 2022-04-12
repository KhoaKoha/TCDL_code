#include <iostream>
using namespace std;

struct NODE {
    int data;
    NODE  *left, *right;
};

NODE* createNode(int data)
{
    NODE *newNode = new NODE();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

NODE* minPositive(NODE *root) {
    if (root == NULL) {
        return NULL;
    }

    NODE *result = NULL;
    if (root->data > 0) {
        result = root;
    }
    
    // Find min positive node of left branch
    NODE *minLeft = minPositive(root->left);
    // Find min positive node of right branch
    NODE *minRight = minPositive(root->right);

    if (minLeft != NULL) {
        if (result == NULL || result->data > minLeft->data) {
            result = minLeft;
        }
    }

    if (minRight != NULL) {
        if (result == NULL || result->data > minRight->data) {
            result = minRight;
        }
    }
    return result;
}

// main() is where program execution begins.
int main() {
    // Build binary tree
    NODE *root = createNode(-1);
    root->left = createNode(-3);
    root->right = createNode(-2);
    root->left->left = createNode(-4);
    root->left->right = createNode(0);
    root->right->left = createNode(0);
    root->right->right = createNode(-6);
    NODE *minPosNode = minPositive(root);
    if (minPosNode != NULL) {
        cout << "Min positive node value: " << minPosNode->data;
    } else {
        cout << "Min positive node not found";
    }
    return 0;
}