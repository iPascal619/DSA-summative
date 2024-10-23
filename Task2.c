#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Utility functions
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printCodes(struct MinHeapNode* root, int arr[], int top, FILE* output) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, output);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, output);
    }

    if (!(root->left) && !(root->right)) {
        fprintf(output, "%c:", root->data);
        for (int i = 0; i < top; ++i)
            fprintf(output, "%d", arr[i]);
        fprintf(output, "\n");
    }
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void HuffmanCodes(char data[], int freq[], int size, const char* output_filename) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    
    FILE* output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Error opening output file!\n");
        return;
    }
    
    printCodes(root, arr, top, output);
    fclose(output);
}

int main() {
    char filename[100];
    printf("Enter input filename: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Count character frequencies
    int freq[256] = {0};
    char ch;
    long original_size = 0;
    
    while ((ch = fgetc(file)) != EOF) {
        freq[(unsigned char)ch]++;
        original_size++;
    }
    
    fclose(file);

    char data[256];
    int frequencies[256];
    int size = 0;
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            frequencies[size] = freq[i];
            size++;
        }
    }

    char output_filename[100];
    printf("Enter output filename: ");
    scanf("%s", output_filename);

    HuffmanCodes(data, frequencies, size, output_filename);
    
    // Calculate compressed size 
    FILE* output = fopen(output_filename, "r");
    fseek(output, 0L, SEEK_END);
    long compressed_size = ftell(output);
    fclose(output);

    printf("\nOriginal file size: %ld bytes\n", original_size);
    printf("Compressed file size: %ld bytes\n", compressed_size);
    printf("Compression ratio: %.2f%%\n", 
           (1 - ((float)compressed_size / original_size)) * 100);

    return 0;
}
