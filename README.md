Overview
This project addresses a programming assignment focused on directed weighted graphs, representing a lexical knowledge base. The assignment requires students to implement a solution in C++ without using STL or similar libraries, specifically using an adjacency matrix for graph representation.

Key Requirements
Graph Representation: The implementation uses an adjacency matrix to represent the directed weighted graph.

Operations: The program must support the following functionalities:

Load the graph from a specified text file format
Add and remove nodes
Add and remove edges between nodes
Print graph representation
Delete the graph from memory
User Interaction: The program should interact with the user through a simple menu that allows sequential execution of operations in any order. Input can be taken from standard input or text files.

Error Handling: Solutions must be robust against errors and provide clear feedback to the user.

Evaluation Criteria: Resource utilization and avoiding recursion in solutions will be considered during grading.

File Format for Input
The input file must include:

Number of nodes (n)
Number of edges (e)
n words as node identifiers
e lines specifying edges in the format: word1 word2 similarity
Additional Functionalities
The project also includes features for semantic similarity queries, shortest path analysis, and identification of strongly connected components within the graph.
