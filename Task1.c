#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Structure for adjacency list node
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure for adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure for graph
struct Graph {
    int V;
    struct AdjList* array;
};

// This is to create new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// For creating the graph,
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;
    
    return graph;
}

// This na to Add edges to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Dijkstra's algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];
    
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = false;
    }
    
    dist[src] = 0;
    
    for (int count = 0; count < V - 1; count++) {
        int min = INF, min_index;
        
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] <= min)
                min = dist[v], min_index = v;
        
        int u = min_index;
        sptSet[u] = true;
        
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            
            if (!sptSet[v] && dist[u] != INF && 
                dist[u] + pCrawl->weight < dist[v])
                dist[v] = dist[u] + pCrawl->weight;
            
            pCrawl = pCrawl->next;
        }
    }
    
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

// Bellman-Ford algorithm
void bellmanFord(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[MAX_VERTICES];
    
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;
    
    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int u = 0; u < V; u++) {
            struct AdjListNode* pCrawl = graph->array[u].head;
            while (pCrawl != NULL) {
                int v = pCrawl->dest;
                int weight = pCrawl->weight;
                if (dist[u] != INF && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
                pCrawl = pCrawl->next;
            }
        }
    }
    
    // To Check for negative weight cycles
    for (int u = 0; u < V; u++) {
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            int weight = pCrawl->weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                printf("Graph contains negative weight cycle\n");
                return;
            }
            pCrawl = pCrawl->next;
        }
    }
    
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main() {
    int V, E, choice;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    
    struct Graph* graph = createGraph(V);
    
    printf("Enter number of edges: ");
    scanf("%d", &E);
    
    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }
    
    printf("\n1. Dijkstra's Algorithm\n2. Bellman-Ford Algorithm\nEnter choice: ");
    scanf("%d", &choice);
    
    int source;
    printf("Enter source vertex: ");
    scanf("%d", &source);
    
    if (choice == 1)
        dijkstra(graph, source);
    else
        bellmanFord(graph, source);
    
    return 0;
}
