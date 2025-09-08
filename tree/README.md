# 树结构

树结构是算法中一种十分重要的数据结构，常在有序数据的查找等操作中被用到

## BST 

二叉查找树是用于数据查找的数据结构，其保证节点的左节点小于节点的val，节点的右节点大于节点的val


```cpp
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```

数据的删除逻辑如下所示：

首先找到需要的节点，然后删除该节点，找到其右侧的最小节点，将这个节点的值赋给该节点，然后递归地删除节点。


```cpp
TreeNode* minVal(TreeNode* root){
    TreeNode* temp = root;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return NULL;
    if (key == root->val) {
        if (!root->right) {
            return root->left;
        } 
        if(root->left != nullptr && root->right != nullptr){
            int mini = minVal(root->right) -> val;
            root->val = mini;
            root->right = deleteNode(root->right, mini);
            return root;
        }
        if(root->right == nullptr){
            root = root->left;
            return root;
        }
        root = root->right;
        return root;
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        root->left = deleteNode(root->left, key);
    }
    return root;
}
```