#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SET_SIZE 53 // 定义集合的最大大小（用于存储路径）

// 定义集合结构
typedef struct {
    char elements[MAX_SET_SIZE]; // 存储集合元素
    int size;                    // 当前集合大小
} Set;

// 初始化集合
void initializeSet(Set* set) {
    set->size = 0;
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        set->elements[i] = '\0';
    }
}

// 添加元素到集合
void addElement(Set* set, char element) {
    if (set->size >= MAX_SET_SIZE) {
        printf("集合已满，无法添加更多元素。\n");
        return;
    }

    // 检查元素是否已存在于集合中
    if (isMember(set, element)) {
        // 元素已存在，无需重复添加
        return;
    }

    // 添加元素到集合
    set->elements[set->size++] = element;
}

// 检查元素是否存在于集合中
int isMember(const Set* set, char element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return 1; // 元素存在
        }
    }
    return 0; // 元素不存在
}

// 定义二叉树节点
typedef struct TreeNode {
    char data;               // 节点存储的字符
    struct TreeNode* left;  // 指向左子节点的指针
    struct TreeNode* right; // 指向右子节点的指针
} TreeNode, * BinaryTree;

// 创建二叉树
BinaryTree createTree() {
    char ch;
    printf("请输入节点数据（#表示空节点）: ");
    scanf(" %c", &ch); // 读取一个字符，跳过任何空白字符
    if (ch == '#') {
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        perror("内存分配失败：无法分配新节点内存");
        exit(EXIT_FAILURE);
    }
    node->data = ch;
    node->left = createTree();  // 递归创建左子树
    node->right = createTree(); // 递归创建右子树
    return node;
}

// 查找节点并记录路径
int findNode(BinaryTree root, char x, LinkedList* path) {
    if (root == NULL) return 0;
    if (root->data == x) return 1;
    if (findNode(root->left, x, path)) {
        addElement(path, root->data); // 记录当前节点到路径
        return 1;
    }
    if (findNode(root->right, x, path)) {
        addElement(path, root->data); // 记录当前节点到路径
        return 1;
    }
    return 0;
}

// 打印祖先节点
void printAncestors(LinkedList path) {
    printf("祖先节点: ");
    for (int i = 0; i < path->size; i++) {
        printf("%c ", path->elements[i]);
    }
    printf("\n");
}

// 定义链表节点
typedef struct Node {
    char data;
    struct Node* next;
} Node, * LinkedList;

// 创建链表
LinkedList createList() {
    LinkedList list = (LinkedList)malloc(sizeof(Node));
    if (list == NULL) {
        perror("内存分配失败：无法分配链表节点内存");
        exit(EXIT_FAILURE);
    }
    list->next = NULL;
    return list;
}

// 添加元素到链表
void addElement(LinkedList list, char element) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("内存分配失败：无法分配新节点内存");
        exit(EXIT_FAILURE);
    }
    newNode->data = element;
    newNode->next = list->next;
    list->next = newNode;
}

// 打印链表
void printList(LinkedList list) {
    Node* p = list->next;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 释放链表内存
void freeLinkedList(LinkedList list) {
    Node* p = list;
    while (p != NULL) {
        Node* temp = p->next;
        free(p);
        p = temp;
    }
}

// 释放二叉树内存
void freeBinaryTree(BinaryTree T) {
    if (T != NULL) {
        freeBinaryTree(T->left);
        freeBinaryTree(T->right);
        free(T);
    }
}

// 主函数
int main() {
    BinaryTree T;
    char x;
    printf("创建二叉树:\n");
    T = createTree();
    printf("请输入要查找的节点值: ");
    scanf(" %c", &x);
    LinkedList path = createList();
    if (findNode(T, x, &path)) {
        printAncestors(path);
    }
    else {
        printf("未找到节点 %c。\n", x);
    }
    freeLinkedList(path);
    freeBinaryTree(T);
    return 0;
}