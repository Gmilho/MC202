#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x,y) (((x) > (y))?(x):(y))

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int findRootIndex(int* arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

TreeNode* buildTreeUtil(int* inOrder, int* postOrder, int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    TreeNode* root = createNode(postOrder[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd) {
        return root;
    }

    int rootIndex = findRootIndex(inOrder, inStart, inEnd, root->value);

    root->right = buildTreeUtil(inOrder, postOrder, rootIndex + 1, inEnd, postIndex);
    root->left = buildTreeUtil(inOrder, postOrder, inStart, rootIndex - 1, postIndex);

    return root;
}

TreeNode* buildTree(int* inOrder, int* postOrder, int size) {
    int postIndex = size - 1;
    return buildTreeUtil(inOrder, postOrder, 0, size - 1, &postIndex);
}

void printInOrder(TreeNode* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

int SomaGraos(TreeNode* A){
  if (A == NULL){return 0;}
  int respE = SomaGraos(A->left);
  int respD = SomaGraos(A->right);
  int maxSubtreeSum = (respE > respD) ? respE : respD;
  printf("%d\n", A->value);
  printf("%d\n", maxSubtreeSum);
  return maxSubtreeSum + A->value;
}

int main(){
  int inorder[] = {2, -1, 4, 5, -12, -2, 2, 3};
  int postorder[] = {2, 4, 5, -1, 2, -2, 3, -12};

  TreeNode* arvoreBin = buildTree(inorder, postorder, 8);

  int resposta1 = SomaGraos(arvoreBin->left);
  printf("%d\n", resposta1);
  
  return 0;
}