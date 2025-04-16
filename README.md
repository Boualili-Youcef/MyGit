# MyGit - A Simple Git Implementation

## Introduction
MyGit is a custom implementation of a version control system inspired by Git. This project aims to recreate the core functionality of Git from scratch to better understand its internal mechanisms and data structures.

## Purpose
The main goals of this project are:
- To understand how Git works internally
- To learn about content-addressable storage systems
- To implement fundamental Git commands and functionality
- To create a simplified yet functional Git alternative
- To get an internship hh

## Current Implementation
As of now, MyGit supports the following features:
- **Repository Initialization (`init`)**: Creates a `.myGit` directory with the basic structure needed for version control
- **Object Hashing and Storage (`hash-object`)**: Computes SHA-1 hash for files and optionally stores them in the object database
- **Blob Storage**: Implements content-addressable storage with objects saved in `.myGit/objects/xx/yyyyyy...` format

## Technical Details
MyGit is implemented in C++ and utilizes:
- OpenSSL for SHA-1 hashing
- Standard C++ filesystem library for file operations
- Object-oriented design with classes representing Git objects

The project is organized into:
- `commands/`: Implementation of user-facing commands
- `objets/`: Core classes representing Git objects (Blob, etc.)
- Utility functions for file operations and hashing

## Roadmap
Future implementations will include:
- **Index/Staging Area**: For tracking changes before committing
- **Tree Objects**: For representing directories and file hierarchies
- **Commit Objects**: For creating snapshots of the repository
- ...

## Installation and Usage

### Prerequisites
- C++ compiler with C++17 support
- CMake 3.10 or higher
- OpenSSL development libraries

### Building
```bash
git clone https://github.com/yourusername/MyGit.git
cd MyGit
mkdir build && cd build
cmake ..
make
```

### Basic Commands
```bash
# Initialize a repository
./mygit init

# Hash a file (without storing) for testing without polluting the repo
./mygit hash-object <file>

# Hash a file and store it in the object database
./mygit hash-object -w <file>

# Add file to staging area (index)
./mygit add <file>
```

## Learning Objectives
This project serves as a practical exploration of:
- Low-level file operations
- Content-based addressing and hashing
- Efficient storage mechanisms
- Version control concepts and algorithms

## Project Progress

- [x] Repository structure (`.myGit` directory)
- [x] Object hashing (`hash-object`)
- [x] Content-addressable storage (blobs in `.myGit/objects`)
- [x] Index/staging area (`add` command)
- [ ] Tree objects (directory representation)
- [ ] Commit objects (snapshots with metadata)
- ...

