# 🧠 In-Memory LRU Cache – C++ Implementation

## 📌 Problem Statement

Design and implement an **In-Memory Least Recently Used (LRU) Cache** that supports the following operations in **O(1)** time:

- `get(key: int) -> int`  
  Returns the value associated with the key if it exists, otherwise returns `-1`.

- `put(key: int, value: int) -> None`  
  Inserts or updates the value of the key.  
  If the cache reaches its capacity, it must remove the **least recently used** item before inserting a new one.

---

## ✅ Approach & Design

To ensure **O(1)** time complexity for both `get` and `put` operations, the solution uses:

### 🧩 Visual Representation

Here’s an example of a 3-element LRU cache:

```cpp
//          head      MRU               LRU      tail
// NULL <-{-1, -1}<->{3, 3}<->{2, 2}<->{1, 1}<->{-1, -1} -> NULL
```

### 1. **Doubly Linked List (DLL)**  
To store the order of usage:  
- The **most recently used** node is moved to the front (right after the dummy `head`).
- The **least recently used** node is removed from the back (just before the dummy `tail`).
- Each node stores `key`, `value`, and pointers to its `prev` and `next` neighbors.

### 2. **Hash Map (`unordered_map<int, Node*>`)**  
To allow `O(1)` access to any node by key.  
Maps a key to its corresponding node in the DLL.

---

## 🛠️ Data Structures Used

| Component | Description |
|----------|-------------|
| `Node` class | Represents each key-value pair as a doubly linked list node. Stores `key`, `value`, `prev`, and `next` pointers. |
| `unordered_map<int, Node*>` | Stores key-to-node mappings for constant-time access. |
| `head` and `tail` sentinel nodes | Dummy nodes to simplify edge-case handling when inserting/removing from the list. |

---

## 🧪 How It Works

- On `get(key)`:
  - If key is found in map:  
    → Move the node to the front (mark as most recently used)  
    → Return its value.
  - Else, return `-1`.

- On `put(key, value)`:
  - If key already exists:  
    → Update its value  
    → Move node to the front.
  - If key is new:
    - If cache is at capacity:  
      → Remove least recently used node from the tail.  
      → Delete it and erase from map.
    - Add the new node at the front and map the key.

---

## 🧑‍💻 How to Run the Code

### 🧱 Requirements
- C++17 or later
- G++ compiler

### ▶️ Compile & Run
```bash
g++ -std=c++17 -o LRUCache LRUCache.cpp
./LRUCache
