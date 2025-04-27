#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SET_SIZE 53 // ���弯�ϵ�����С�����ڴ洢·����

// ���弯�Ͻṹ
typedef struct {
    char elements[MAX_SET_SIZE]; // �洢����Ԫ��
    int size;                    // ��ǰ���ϴ�С
} Set;

// ��ʼ������
void initializeSet(Set* set) {
    set->size = 0;
    for (int i = 0; i < MAX_SET_SIZE; i++) {
        set->elements[i] = '\0';
    }
}

// ���Ԫ�ص�����
void addElement(Set* set, char element) {
    if (set->size >= MAX_SET_SIZE) {
        printf("�����������޷���Ӹ���Ԫ�ء�\n");
        return;
    }

    // ���Ԫ���Ƿ��Ѵ����ڼ�����
    if (isMember(set, element)) {
        // Ԫ���Ѵ��ڣ������ظ����
        return;
    }

    // ���Ԫ�ص�����
    set->elements[set->size++] = element;
}

// ���Ԫ���Ƿ�����ڼ�����
int isMember(const Set* set, char element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return 1; // Ԫ�ش���
        }
    }
    return 0; // Ԫ�ز�����
}

// ����������ڵ�
typedef struct TreeNode {
    char data;               // �ڵ�洢���ַ�
    struct TreeNode* left;  // ָ�����ӽڵ��ָ��
    struct TreeNode* right; // ָ�����ӽڵ��ָ��
} TreeNode, * BinaryTree;

// ����������
BinaryTree createTree() {
    char ch;
    printf("������ڵ����ݣ�#��ʾ�սڵ㣩: ");
    scanf(" %c", &ch); // ��ȡһ���ַ��������κοհ��ַ�
    if (ch == '#') {
        return NULL;
    }
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) {
        perror("�ڴ����ʧ�ܣ��޷������½ڵ��ڴ�");
        exit(EXIT_FAILURE);
    }
    node->data = ch;
    node->left = createTree();  // �ݹ鴴��������
    node->right = createTree(); // �ݹ鴴��������
    return node;
}

// ���ҽڵ㲢��¼·��
int findNode(BinaryTree root, char x, LinkedList* path) {
    if (root == NULL) return 0;
    if (root->data == x) return 1;
    if (findNode(root->left, x, path)) {
        addElement(path, root->data); // ��¼��ǰ�ڵ㵽·��
        return 1;
    }
    if (findNode(root->right, x, path)) {
        addElement(path, root->data); // ��¼��ǰ�ڵ㵽·��
        return 1;
    }
    return 0;
}

// ��ӡ���Ƚڵ�
void printAncestors(LinkedList path) {
    printf("���Ƚڵ�: ");
    for (int i = 0; i < path->size; i++) {
        printf("%c ", path->elements[i]);
    }
    printf("\n");
}

// ��������ڵ�
typedef struct Node {
    char data;
    struct Node* next;
} Node, * LinkedList;

// ��������
LinkedList createList() {
    LinkedList list = (LinkedList)malloc(sizeof(Node));
    if (list == NULL) {
        perror("�ڴ����ʧ�ܣ��޷���������ڵ��ڴ�");
        exit(EXIT_FAILURE);
    }
    list->next = NULL;
    return list;
}

// ���Ԫ�ص�����
void addElement(LinkedList list, char element) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("�ڴ����ʧ�ܣ��޷������½ڵ��ڴ�");
        exit(EXIT_FAILURE);
    }
    newNode->data = element;
    newNode->next = list->next;
    list->next = newNode;
}

// ��ӡ����
void printList(LinkedList list) {
    Node* p = list->next;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

// �ͷ������ڴ�
void freeLinkedList(LinkedList list) {
    Node* p = list;
    while (p != NULL) {
        Node* temp = p->next;
        free(p);
        p = temp;
    }
}

// �ͷŶ������ڴ�
void freeBinaryTree(BinaryTree T) {
    if (T != NULL) {
        freeBinaryTree(T->left);
        freeBinaryTree(T->right);
        free(T);
    }
}

// ������
int main() {
    BinaryTree T;
    char x;
    printf("����������:\n");
    T = createTree();
    printf("������Ҫ���ҵĽڵ�ֵ: ");
    scanf(" %c", &x);
    LinkedList path = createList();
    if (findNode(T, x, &path)) {
        printAncestors(path);
    }
    else {
        printf("δ�ҵ��ڵ� %c��\n", x);
    }
    freeLinkedList(path);
    freeBinaryTree(T);
    return 0;
}