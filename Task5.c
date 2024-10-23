#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

enum Color { RED, BLACK };

struct Student {
    int id;
    char name[MAX_NAME];
    float grade;
};

struct Node {
    struct Student data;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    enum Color color;
};

typedef struct Node *NodePtr;
struct Node *root = NULL;

// Create a new node
NodePtr createNode(struct Student student) {
    NodePtr newNode = (NodePtr)malloc(sizeof(struct Node));
    newNode->data = student;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = RED;
    return newNode;
}

void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    
    if (y->left != NULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    
    if (y->right != NULL)
        y->right->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    
    y->right = x;
    x->parent = y;
}

void fixInsert(NodePtr k) {
    NodePtr u;
    while (k->parent != NULL && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u != NULL && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u != NULL && u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) break;
    }
    root->color = BLACK;
}

void insert(struct Student student) {
    NodePtr node = createNode(student);
    
    NodePtr y = NULL;
    NodePtr x = root;
    
    while (x != NULL) {
        y = x;
        if (node->data.id < x->data.id)
            x = x->left;
        else
            x = x->right;
    }
    
    node->parent = y;
    
    if (y == NULL)
        root = node;
    else if (node->data.id < y->data.id)
        y->left = node;
    else
        y->right = node;
    
    fixInsert(node);
}

NodePtr search(int id) {
    NodePtr current = root;
    while (current != NULL) {
        if (id == current->data.id)
            return current;
        else if (id < current->data.id)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

void inorderTraversal(NodePtr node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("ID: %d, Name: %s, Grade: %.2f\n", 
               node->data.id, node->data.name, node->data.grade);
        inorderTraversal(node->right);
    }
}

int main() {
    int choice;
    struct Student student;
    
    do {
        printf("\nStudent Records Management System\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Display All Students\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &student.id);
                printf("Enter student name: ");
                getchar();
                fgets(student.name, MAX_NAME, stdin);
                student.name[strcspn(student.name, "\n")] = 0;
                printf("Enter student grade: ");
                scanf("%f", &student.grade);
                insert(student);
                printf("Student added successfully!\n");
                break;
                
            case 2:
                printf("Enter student ID to search: ");
                scanf("%d", &student.id);
                NodePtr result = search(student.id);
                if (result != NULL)
                    printf("Found - ID: %d, Name: %s, Grade: %.2f\n",
                           result->data.id, result->data.name, result->data.grade);
                else
                    printf("Student not found!\n");
                break;
                
            case 3:
                printf("\nAll Students (Sorted by ID):\n");
                inorderTraversal(root);
                break;
                
            case 4:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);
    
    return 0;
}
