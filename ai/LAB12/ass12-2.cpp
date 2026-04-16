#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define N 9

// Each cell has a domain (set of possible values)
vector<set<int>> dom(81);

// Get row, col
int row(int i) { return i / 9; }
int col(int i) { return i % 9; }

// Check constraint: values must be different
bool ok(int a, int b) {
    return a != b;
}

// Get neighbors of a cell
vector<int> getNeighbors(int idx) {
    vector<int> nbrs;
    int r = row(idx), c = col(idx);

    // Row + Column
    for (int i = 0; i < 9; i++) {
        if (i != c) nbrs.push_back(r * 9 + i);
        if (i != r) nbrs.push_back(i * 9 + c);
    }

    // 3x3 box
    int sr = (r / 3) * 3;
    int sc = (c / 3) * 3;

    for (int i = sr; i < sr + 3; i++) {
        for (int j = sc; j < sc + 3; j++) {
            int id = i * 9 + j;
            if (id != idx) nbrs.push_back(id);
        }
    }

    return nbrs;
}

// Revise function
bool revise(int xi, int xj, int &removedCount) {
    bool changed = false;
    vector<int> toRemove;

    for (int x : dom[xi]) {
        bool possible = false;

        for (int y : dom[xj]) {
            if (ok(x, y)) {
                possible = true;
                break;
            }
        }

        if (!possible) {
            toRemove.push_back(x);
        }
    }

    for (int v : toRemove) {
        dom[xi].erase(v);
        removedCount++;
        changed = true;
    }

    return changed;
}

// AC-3 Algorithm
bool AC3(int &removedCount) {
    queue<pair<int,int>> q;

    // Generate all arcs
    for (int i = 0; i < 81; i++) {
        for (int j : getNeighbors(i)) {
            q.push({i, j});
        }
    }

    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int xi = p.first, xj = p.second;

        if (revise(xi, xj, removedCount)) {

            if (dom[xi].empty()) return false;

            for (int xk : getNeighbors(xi)) {
                if (xk != xj) {
                    q.push({xk, xi});
                }
            }
        }
    }

    return true;
}

int main() {

    int grid[9][9] = {
        {0,0,0,0,0,6,0,0,0}, 
        {0,5,9,0,0,0,0,0,8}, 
        {2,0,0,0,0,8,0,0,0}, 
        {0,4,5,0,0,0,0,0,0}, 
        {0,0,3,0,0,0,0,0,0}, 
        {0,0,6,0,0,3,0,5,0}, 
        {0,0,0,0,0,7,0,0,0}, 
        {0,0,0,0,0,0,0,0,0}, 
        {0,0,0,0,5,0,0,0,2}
    // {5,3,0,0,7,0,0,0,0},
    // {6,0,0,1,9,5,0,0,0},
    // {0,9,8,0,0,0,0,6,0},
    // {8,0,0,0,6,0,0,0,3},
    // {4,0,0,8,0,3,0,0,1},
    // {7,0,0,0,2,0,0,0,6},
    // {0,6,0,0,0,0,2,8,0},
    // {0,0,0,4,1,9,0,0,5},
    // {0,0,0,0,8,0,0,7,9}
    };

    // Initialize domains
    for (int i = 0; i < 81; i++) {
        int r = i / 9, c = i % 9;

        if (grid[r][c] == 0) {
            for (int v = 1; v <= 9; v++)
                dom[i].insert(v);
        } else {
            dom[i].insert(grid[r][c]);
        }
    }

    int removedCount = 0;

    bool result = AC3(removedCount);

    cout << "Values removed: " << removedCount << endl;

    cout << "\nDomain size grid:\n";

    bool allOne = true;

    for (int i = 0; i < 81; i++) {
        int size = dom[i].size();
        cout << size << " ";

        if (size != 1) allOne = false;

        if ((i + 1) % 9 == 0) cout << endl;
    }

    cout << "\n";

    if (!result) {
        cout << "Some domain became empty -> UNSOLVABLE\n";
    }
    else if (allOne) {
        cout << "Solved completely by AC-3\n";
    }
    else {
        cout << "Partially reduced, needs backtracking\n";
    }

    return 0;
}