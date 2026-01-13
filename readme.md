# Simple File Compressor

> A lightweight file compression tool built from scratch in C++ using the Huffman coding algorithm.

## Project Status: Work in Progress


## 🛠 Features & Progress

### Core Logic
- **Data Structures:** Custom Node and Tree structures implemented.
- **Frequency Analysis:** Efficient character counting using Maps.
- **Huffman Algorithm:** Priority Queue implementation to build the Huffman Tree.
- **Encoding Table:** Recursive generation of prefix codes (0s and 1s).

### Low-level Operations
- **Bitwise Manipulation:** Packing bits into bytes (In Progress).
- **Binary I/O:** Reading/Writing binary files directly.
- **File Header:** Saving metadata for decompression.

## Project Structure

- `Huffmantree.h/cpp`: Manages the tree construction and code generation.
- `Bitwriter.h/cpp`: Handles bit-level buffer management and writing to file streams.
- `main.cpp`: Entry point for testing the compression flow.
