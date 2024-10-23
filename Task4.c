#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 50
#define MAX_DEF 200

// Structure for dictionary node
struct DictNode {
    char word[MAX_WORD];
    char definition[MAX_DEF];
    struct DictNode* left;
    struct DictNode* right;
};

struct DictNode* createNode(char* word, char* definition) {
    struct DictNode* newNode = (struct DictNode*)malloc(sizeof(struct DictNode));
    strcpy(newNode->word, word);
    strcpy(newNode->definition, definition);
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct DictNode* insert(struct DictNode* root, char* word, char* definition) {
    if (root == NULL) {
        return createNode(word, definition);
    }
    
    int cmp = strcmp(word, root->word);
    
    if (cmp < 0) {
        root->left = insert(root->left, word, definition);
    }
    else if (cmp > 0) {
        root->right = insert(root->right, word, definition);
    }
    else {
        strcpy(root->definition, definition);
    }
    
    return root;
}

// Find the minimum value node in a BST
struct DictNode* minValueNode(struct DictNode* node) {
    struct DictNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Delete a word from the BST
struct DictNode* deleteNode(struct DictNode* root, char* word) {
    if (root == NULL) {
        return root;
    }
    
    int cmp = strcmp(word, root->word);
    
    if (cmp < 0) {
        root->left = deleteNode(root->left, word);
    }
    else if (cmp > 0) {
        root->right = deleteNode(root->right, word);
    }
    else {
        // Node to be deleted found
        
        // Node with one child or no child
        if (root->left == NULL) {
            struct DictNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct DictNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with 2 childrn
        struct DictNode* temp = minValueNode(root->right);
        strcpy(root->word, temp->word);
        strcpy(root->definition, temp->definition);
        root->right = deleteNode(root->right, temp->word);
    }
    return root;
}

// to Search for a word in the BST
struct DictNode* search(struct DictNode* root, char* word) {
    if (root == NULL || strcmp(root->word, word) == 0) {
        return root;
    }
    
    if (strcmp(word, root->word) < 0) {
        return search(root->left, word);
    }
    
    return search(root->right, word);
}

// This is to Perform in-order traversal to display all words alphabetically
void inorderTraversal(struct DictNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("\nWord: %s\nDefinition: %s\n", root->word, root->definition);
        inorderTraversal(root->right);
    }
}

int main() {
    struct DictNode* root = NULL;
    int choice;
    char word[MAX_WORD], definition[MAX_DEF];
    
    do {
        printf("\nDictionary Operations:\n");
        printf("1. Add word\n");
        printf("2. Delete word\n");
        printf("3. Search word\n");
        printf("4. Display all words\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Enter word: ");
                fgets(word, MAX_WORD, stdin);
                word[strcspn(word, "\n")] = 0; 
                
                printf("Enter definition: ");
                fgets(definition, MAX_DEF, stdin);
                definition[strcspn(definition, "\n")] = 0; 
                
                root = insert(root, word, definition);
                printf("Word added successfully!\n");
                break;
                
            case 2:
                printf("Enter word to delete: ");
                fgets(word, MAX_WORD, stdin);
                word[strcspn(word, "\n")] = 0;
                
                root = deleteNode(root, word);
                printf("Word deleted successfully!\n");
                break;
                
            case 3:
                printf("Enter word to search: ");
                fgets(word, MAX_WORD, stdin);
                word[strcspn(word, "\n")] = 0;
                
                struct DictNode* result = search(root, word);
                if (result != NULL) {
                    printf("\nWord found!\nDefinition: %s\n", result->definition);
                } else {
                    printf("\nWord not found!\n");
                }
                break;
                
            case 4:
                printf("\nDictionary contents (alphabetically ordered):");
                inorderTraversal(root);
                break;
                
            case 5:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
    
    return 0;
}
