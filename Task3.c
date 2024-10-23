#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50
#define MAX_PHONE 15

// Structure to store contact information
struct Contact {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    int level; 
};

// Structure for adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure for adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure for the graph
struct Graph {
    int V;  
    struct AdjList* array;
    struct Contact* contacts; 
};

// Structure for queue used in BFS
struct Queue {
    int front, rear;
    int capacity;
    int* array;
};

// Create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    graph->contacts = (struct Contact*)malloc(V * sizeof(struct Contact));
    
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
        graph->contacts[i].level = -1;  // Initialize level as -1 (unvisited)
    }
    
    return graph;
}

// Create a queue
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Queue operations
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

void enqueue(struct Queue* queue, int item) {
    if (queue->rear == queue->capacity - 1) return;
    if (queue->front == -1) queue->front = 0;
    queue->array[++queue->rear] = item;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        queue->front++;
    return item;
}

// Add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Perform BFS to find contact levels
void findContactLevels(struct Graph* graph, int criminal) {
    for (int i = 0; i < graph->V; i++) {
        graph->contacts[i].level = -1;
    }
    
    struct Queue* queue = createQueue(graph->V);
    

    graph->contacts[criminal].level = 0;
    enqueue(queue, criminal);
    
    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        struct AdjListNode* temp = graph->array[current].head;
        
        while (temp != NULL) {
            int adjVertex = temp->dest;
            
            if (graph->contacts[adjVertex].level == -1) {
                graph->contacts[adjVertex].level = graph->contacts[current].level + 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    
    free(queue);
}

// Print contacts by level
void printContactsByLevel(struct Graph* graph) {
    int maxLevel = 0;
    
    // Find maximum level
    for (int i = 0; i < graph->V; i++) {
        if (graph->contacts[i].level > maxLevel) {
            maxLevel = graph->contacts[i].level;
        }
    }
    
    // Print contacts level by level
    for (int level = 0; level <= maxLevel; level++) {
        printf("\nLevel %d contacts:\n", level);
        for (int i = 0; i < graph->V; i++) {
            if (graph->contacts[i].level == level) {
                printf("Name: %s, Phone: %s\n", 
                       graph->contacts[i].name, 
                       graph->contacts[i].phone);
            }
        }
    }
}

int main() {
    int V;
    printf("Enter number of people in the network: ");
    scanf("%d", &V);
    
    struct Graph* graph = createGraph(V);
    
    // Input contact information
    printf("\nEnter contact information:\n");
    for (int i = 0; i < V; i++) {
        printf("Person %d:\n", i);
        printf("Name: ");
        scanf("%s", graph->contacts[i].name);
        printf("Phone: ");
        scanf("%s", graph->contacts[i].phone);
    }
    
    // Input connections
    int E;
    printf("\nEnter number of connections: ");
    scanf("%d", &E);
    
    printf("Enter connections (person1 person2):\n");
    for (int i = 0; i < E; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    
    // Input criminal
    int criminal;
    printf("\nEnter the index of the criminal: ");
    scanf("%d", &criminal);
    
    // Find and print contact levels
    findContactLevels(graph, criminal);
    printf("\nContact Tracing Results:");
    printContactsByLevel(graph);
    
    return 0;
}
