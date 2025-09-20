#include <iostream>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


TreeNode* minVal(TreeNode* root){
    TreeNode* temp = root;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return root;
    if (root->val == key) {
        if (!root->left && !root->right) {
            return nullptr;
        } else if (root->left && !root->right) {
            return root->left;
        } else if (root->left && root->right) {
            int mini = minVal(root->right)->val;
            root->val = mini;
            root->right = deleteNode(root->right, mini);
            return root;
        } else {
                root = root->right;
                return root;
        }
    } else if (root->val > key) {
        root->left = deleteNode(root->left, key);
    } else {
        root->right = deleteNode(root->right, key);
    }
    return root;

}

int main() {

}
