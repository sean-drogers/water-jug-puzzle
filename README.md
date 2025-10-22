# Water Jug Puzzle

**Language:** C++  
**Purpose:** Solves the classic three-jug water puzzle using a Breadth-First Search (BFS) algorithm.

---

##  How It Works
- Uses BFS to explore all possible states of three water jugs (A, B, C).  
- Each state tracks the current gallons in each jug and the previous state.  
- The algorithm finds the shortest sequence of pours to reach the goal configuration.  
- Supports input validation and clear step-by-step solution output.

---

##  Build & Run
```bash
g++ -O2 -std=c++17 -o waterjugpuzzle src/waterjugpuzzle.cpp
./waterjugpuzzle <capA> <capB> <capC> <goalA> <goalB> <goalC>
