# 🔄 NTU Algorithms PA3 – Cycle Breaking

## 📌 Project Title
**Cycle Breaking** – Programming Assignment 3 for NTU Algorithms (Fall 2024)

## 📄 Introduction
This project solves the **Cycle Breaking** problem, where the goal is to make a given graph acyclic by removing edges with the **minimum total weight**, while keeping the graph **connected** (undirected) or **weakly connected** (directed). It supports both **undirected** and **directed weighted graphs**, and implements efficient algorithms tailored to each type.

## 📚 Table of Contents
- [Introduction](#-introduction)
- [Installation](#-installation)
- [Usage](#-usage)
- [Input Format](#-input-format)
- [Output Format](#-output-format)
- [Algorithms Used](#-algorithms-used)
- [File Structure](#-file-structure)
- [Compilation](#-compilation)
- [Performance](#-performance)
- [Troubleshooting](#-troubleshooting)
- [License](#-license)

## 🛠️ Installation
- Platform: Linux (EDA Union Server recommended)
- Language: C++
- Compiler: `g++` with C++11 or higher
- No external libraries needed

## 🚀 Usage
```bash
./cb <input_file> <output_file>
```
**Example:**
```bash
./cb inputs/1.in outputs/1.out
```

## 📥 Input Format
1. First line: `'u'` for undirected or `'d'` for directed graph
2. Second line: `n` (number of vertices)
3. Third line: `m` (number of edges)
4. Next `m` lines: `i j w` — edge from `i` to `j` with weight `w`
5. Final line: `0` to terminate input

**Constraints:**
- Undirected: `n ≤ 10,000`, `m ≤ 20,000,000`
- Directed: `n ≤ 5,000`, `m ≤ 10,000`
- Edge weights: `-100 ≤ w ≤ 100`

## 📤 Output Format
- First line: Total weight of removed edges
- Following lines: Removed edges and their weights (`i j w`)
- Output `0` if no edges are removed

## 💡 Algorithms Used

### Undirected Graphs
- **Kruskal’s Algorithm** to find a **Maximum Spanning Tree**
- All other edges are removed to break cycles

### Directed Graphs
- **Kosaraju’s Algorithm** to find **Strongly Connected Components (SCCs)**
- Repeatedly remove the lightest edge from each SCC until the graph is acyclic

## 🧩 File Structure
```
<student_id>_pa3/
├── bin/
│   └── cb                  # Compiled binary
├── doc/
│   └── report.pdf          # Design and analysis report
├── src/
│   └── cycle_breaking.cpp  # Source code
├── makefile                # Builds 'cb'
├── README                  # This file
```

## 🧱 Compilation
Run from your project root directory:
```bash
make
```
Binary will be located at:
```
bin/cb
```

## 📈 Performance
- Efficient memory and runtime handling of large graphs
- Runtime optimizations using `-O3`
- Directed case performance depends on number and size of SCCs

## 🐛 Troubleshooting

| Issue                        | Solution                                      |
|-----------------------------|-----------------------------------------------|
| Segmentation fault          | Use servers with sufficient memory (EDA)      |
| Incorrect edge directions   | Double-check for `u` vs `d` in input          |
| No output file created      | Ensure correct command syntax and file paths  |
| Compile errors              | Ensure C++11 or higher is enabled             |

## 🪪 License
This project is part of NTU’s Algorithms Course Fall 2024. Redistribution or unauthorized sharing is strictly prohibited and subject to academic policy.