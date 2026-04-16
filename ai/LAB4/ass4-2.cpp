#include <bits/stdc++.h>
using namespace std;

struct rule {
    int id;
    string condition;
    string action;
};

struct node {
    int id;
    int h;
    vector<int> path;
};

class priorityqueue {
public:
    vector<node> pq;

    void push(node n) {
        pq.push_back(n);
    }

    node pop() {
        int minIndex = 0;
        for (int i = 1; i < pq.size(); i++) {
            if (pq[i].h < pq[minIndex].h)
                minIndex = i;
        }
        node best = pq[minIndex];
        pq.erase(pq.begin() + minIndex);
        return best;
    }

    bool empty() {
        return pq.empty();
    }
};

int heuristic(int u, int v, int cols) {
    int ux = u % cols, uy = u / cols;
    int vx = v % cols, vy = v / cols;
    return abs(ux - vx) + abs(uy - vy);
}

int main() {

    vector<rule> rules = {
        {1, "Robot at start cell", "Insert start node into OPEN list"},
        {2, "OPEN list not empty", "Select node with minimum heuristic"},
        {3, "Selected node is goal", "Stop search and print path"},
        {4, "Selected node is not goal", "Expand neighbors"},
        {5, "Neighbor is obstacle", "Ignore neighbor"},
        {6, "Neighbor already visited", "Ignore neighbor"},
        {7, "Valid neighbor", "Insert into OPEN list"},
        {8, "OPEN list empty", "Stop search (No path found)"}
    };

    // 0 = free cell, 1 = obstacle
    vector<vector<int>> floor = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,0,1,1,0,1,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,1,1,1,1,0,0,0,0,0},
        {0,0,0,0,1,1,1,0,1,0},
        {0,1,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,1,0,1,0,0}
    };

    int rows = floor.size();      
    int cols = floor[0].size();   

    vector<vector<int>> id(rows, vector<int>(cols));
    int counter = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            id[i][j] = counter++;

    int N = rows * cols;

    int startX = 3, startY = 1;
    int goalX  = 8, goalY  = 3;

    int start = id[startY][startX];
    int goal  = id[goalY][goalX];

    vector<vector<int>> adj(N, vector<int>(N, 0));

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {

            if (floor[y][x] == 1) continue;

            int u = id[y][x];

            for (int k = 0; k < 4; k++) {
                int ny = y + dy[k];
                int nx = x + dx[k];

                if (ny >= 0 && ny < rows &&
                    nx >= 0 && nx < cols &&
                    floor[ny][nx] == 0) {

                    int v = id[ny][nx];
                    adj[u][v] = 1;
                }
            }
        }
    }

    /* BEST FIRST SEARCH */
    vector<bool> visited(N, false);
    priorityqueue open;

    node s;
    s.id = start;
    s.h  = heuristic(start, goal, cols);
    s.path.push_back(start);
    open.push(s);

    int explored = 0;

    cout << "\n BEST FIRST SEARCH EXECUTION \n";

    while (!open.empty()) {
        node curr = open.pop();
        explored++;

        if (visited[curr.id]) continue;
        visited[curr.id] = true;

        if (curr.id == goal) {
            cout << "\nEvacuation Path:\n";
            for (int cid : curr.path)
                cout << "(" << cid / cols << "," << cid % cols << ") ";
            cout << "\n\nCells explored: " << explored;
            return 0;
        }

        for (int v = 0; v < N; v++) {
            if (adj[curr.id][v] && !visited[v]) {
                node next;
                next.id = v;
                next.h  = heuristic(v, goal, cols);
                next.path = curr.path;
                next.path.push_back(v);
                open.push(next);
            }
        }
    }

    cout << "\nExit not reachable!";
    return 0;
}