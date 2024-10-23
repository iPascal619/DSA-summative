# Data Structures and Algorithms Implementation Project

This project contains implementations of six different data structure and algorithm solutions in C. Each implementation demonstrates different concepts and practical applications.

## Table of Contents
1. Graph Algorithms (Dijkstra's and Bellman-Ford)(taask 1)
2. Huffman Coding for File Compression(Task 2)
3. Criminal Contact Tracking System(Task 3)
4. Dictionary Lookup System(Task 4)
5. Dynamic Student Records System(Task 5)
6. To-Do List Manager(Task 6)

## Requirements

- GCC compiler (version 4.8 or higher)
- Standard C libraries
- Minimum 512MB RAM
- Terminal or Command Prompt

## Project Structure

```
.
├── src/
│   ├── graph_algorithms.c
│   ├── huffman_coding.c
│   ├── criminal_tracking.c
│   ├── dictionary.c
│   ├── student_records.c
│   └── todo_list.c
├── README.md
└── LICENSE
```

## Building and Running

### Compilation

For each program, use:

```bash
gcc -o bin/program_name src/program_name.c
```

Example:
```bash
gcc -o bin/Task1 src/Task1.c
```

### Running Programs

Execute the compiled programs from the bin directory:

```bash
./bin/program_name
```

## Program Details

### 1. Graph Algorithms

Features:
- Implements both Dijkstra's and Bellman-Ford algorithms
- Handles weighted graphs
- Supports negative weights (Bellman-Ford)
- Interactive graph input

### 2. Huffman Coding

Features:
- File compression using Huffman coding
- Supports text file compression
- Shows compression statistics
- File decompression capability

### 3. Criminal Contact Tracking

Features:
- Contact network analysis
- BFS implementation
- Level-based contact categorization
- Contact information storage

### 4. Dictionary System

Features:
- BST-based word storage
- Word definition management
- Alphabetical listing
- Search functionality

### 5. Student Records System

Features:
- Red-Black Tree implementation
- Student data management
- Balanced tree operations
- Fast search capabilities

### 6. To-Do List Manager

Features:
- Linked list implementation
- Task management
- Completion tracking
- Automatic cleanup

## Implementation Details

### Time Complexities

- Graph Algorithms:
  - Dijkstra's: O(V²)
  - Bellman-Ford: O(VE)
- Huffman Coding: O(nlogn)
- Criminal Tracking: O(V+E)
- Dictionary: O(logn) average
- Student Records: O(logn)
- To-Do List: O(1) insert, O(n) search

### Space Complexities

- Graph Algorithms: O(V²)
- Huffman Coding: O(n)
- Criminal Tracking: O(V+E)
- Dictionary: O(n)
- Student Records: O(n)
- To-Do List: O(n)

## Error Handling

All programs implement error checking for:
- Memory allocation failures
- File operations
- Invalid input
- Buffer overflows
- Null pointer checks

## Contributing

1. Fork the repository
2. Create feature branch (`git checkout -b feature/improvement`)
3. Commit changes (`git commit -am 'Add improvement'`)
4. Push to branch (`git push origin feature/improvement`)
5. Create Pull Request

## Known Limitations

- Graph Algorithms: Max 100 vertices
- Huffman Coding: Text files only
- Criminal Tracking: Max 100 contacts
- Dictionary: ASCII characters only
- Student Records: Integer IDs only
- To-Do List: Linear search for tasks

## License

This project is licensed under the MIT License - see the LICENSE file for details.
