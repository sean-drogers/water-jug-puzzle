//Author: Sean Rogers
//Pledge: I pledge my honor that I have abided by the Stevens Honor System.

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <cerrno>
#include <cctype>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};



bool parse_nonneg_int(const string &s, long &out) {
    if (s.empty()) return false;

    // make sure every character must be a digit
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }

   // converts the string to a number 
    char *endptr = nullptr;
    errno = 0;
    unsigned long val = strtoul(s.c_str(), &endptr, 10);

    // check for overflow or leftover characters
    if (errno != 0 || *endptr != '\0') return false;

    // result
    out = static_cast<long>(val);
    return true;
}


void print_solution(State *goal_state) {
    // We use a stack to reverse the order of steps
    stack<State*> path;

    // Walk backward from goal to start using parent pointers
    State *current = goal_state;
    while (current != nullptr) {
        path.push(current);
        current = current->parent;
    }

    // Now pop from the stack to print from start to goal
    while (!path.empty()) {
        State *step = path.top();
        path.pop();

        cout << step->directions << " " << step->to_string() << endl;
    }
}

bool bfs(int capA, int capB, int capC,int goalA, int goalB, int goalC, State *&goal_state) {

    vector<vector<vector<bool>>> visited(
        capA + 1,
        vector<vector<bool>>(capB + 1,
            vector<bool>(capC + 1, false)
        )
    );

    queue<State*> empty;

    State *start = new State(0, 0, capC, "Initial state.");
    empty.push(start);
    visited[start->a][start->b][start->c] = true;

    // BFS loop
    while (!empty.empty()) {
        State *cur = empty.front();
        empty.pop();

        // Goal check
        if (cur->a == goalA && cur->b == goalB && cur->c == goalC) {
            goal_state = cur;
            return true;
        }

        // 1. C -> A
        if (cur->c > 0 && cur->a < capA) {
            int amount = min(cur->c, capA - cur->a);
            int newA = cur->a + amount;
            int newB = cur->b;
            int newC = cur->c - amount;
            if (!visited[newA][newB][newC]) {
                if (amount == 1) {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallon from C to A.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                } else {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallons from C to A.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                }
            }
        }

        // 2. B -> A
        if (cur->b > 0 && cur->a < capA) {
            int amount = min(cur->b, capA - cur->a);
            int newA = cur->a + amount;
            int newB = cur->b - amount;
            int newC = cur->c;
            if (!visited[newA][newB][newC]) {
                if (amount == 1) {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallon from B to A.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                } else {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallons from B to A.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                }
            }
        }

        // 3. C -> B
        if (cur->c > 0 && cur->b < capB) {
            int amount = min(cur->c, capB - cur->b);
            int newA = cur->a;
            int newB = cur->b + amount;
            int newC = cur->c - amount;
            if (!visited[newA][newB][newC]) {
                if (amount == 1) {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallon from C to B.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                } else {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallons from C to B.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                }
            }
        }

        // 4. A -> B
        if (cur->a > 0 && cur->b < capB) {
            int amount = min(cur->a, capB - cur->b);
            int newA = cur->a - amount;
            int newB = cur->b + amount;
            int newC = cur->c;
            if (!visited[newA][newB][newC]) {
                if (amount == 1) {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallon from A to B.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                } else {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallons from A to B.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                }
            }
        }

        // 5. B -> C
        if (cur->b > 0 && cur->c < capC) {
            int amount = min(cur->b, capC - cur->c);
            int newA = cur->a;
            int newB = cur->b - amount;
            int newC = cur->c + amount;
            if (!visited[newA][newB][newC]) {
                if (amount == 1) {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallon from B to C.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                } else {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallons from B to C.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                }
            }
        }

        // 6. A -> C
        if (cur->a > 0 && cur->c < capC) {
            int amount = min(cur->a, capC - cur->c);
            int newA = cur->a - amount;
            int newB = cur->b;
            int newC = cur->c + amount;
            if (!visited[newA][newB][newC]) {
                if (amount == 1) {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallon from A to C.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                } else {
                    State *next = new State(newA, newB, newC,
                        "Pour " + to_string(amount) + " gallons from A to C.");
                    next->parent = cur;
                    visited[newA][newB][newC] = true;
                    empty.push(next);
                }

            }
        }
    }

    // No solution found
    return false;
}


int main(int argc, char *argv[]){
    if(argc != 7 ){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 1;
    }

    long capA, capB, capC, goalA, goalB, goalC;


    if (!parse_nonneg_int(argv[1], capA) || capA <= 0) {
        cout << "Error: Invalid capacity '" << argv[1] << "' for jug A.";
        return 0;
    }

    if (!parse_nonneg_int(argv[2], capB) || capB <= 0) {
        cout << "Error: Invalid capacity '" << argv[2] << "' for jug B.";
        return 0;
    }

    if (!parse_nonneg_int(argv[3], capC) || capC <= 0) {
        cout << "Error: Invalid capacity '" << argv[3] << "' for jug C.";
        return 0;
    }

    if (!parse_nonneg_int(argv[4], goalA) || goalA < 0) {
        cout << "Error: Invalid goal '" << argv[4] << "' for jug A.";
        return 0;
    }

    if (!parse_nonneg_int(argv[5], goalB) || goalB < 0) {
        cout << "Error: Invalid goal '" << argv[5] << "' for jug B.";
        return 0;
    }

    if (!parse_nonneg_int(argv[6], goalC) || goalC < 0) {
        cout << "Error: Invalid goal '" << argv[6] << "' for jug C.";
        return 0;
    }


    if(capA < goalA){
        cout << "Error: Goal cannot exceed capacity of jug A.";
        return 0;
    }


    if(capB < goalB){
        cout << "Error: Goal cannot exceed capacity of jug B.";
        return 0;
    }


    if(capC < goalC){
        cout << "Error: Goal cannot exceed capacity of jug C.";
        return 0;
    }


    if(goalA + goalB + goalC != capC){
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 0;
    }

     // ---- Run BFS ----
    State *goal_state = nullptr;
    bool found = bfs(capA, capB, capC, goalA, goalB, goalC, goal_state);

    // ---- Output ----
    if (found) {
        print_solution(goal_state);
    } else {
        cout << "No solution." << endl;
    }

    return 0;

}

