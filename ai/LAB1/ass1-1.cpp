#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string,int>>> cityGraph = {
    {"Syracuse", {{"Buffalo", 150}, {"Philadelphia", 253}, {"New York", 254}, {"Boston", 312}}},
    {"Buffalo", {{"Syracuse", 150}, {"Detroit", 256}, {"Cleveland", 215}, {"Pittsburgh", 189}}},
    {"Detroit", {{"Chicago", 283}, {"Buffalo", 256}, {"Cleveland", 169}}},
    {"Cleveland", {{"Detroit", 169}, {"Buffalo", 215}, {"Pittsburgh", 134}, {"Columbus", 144}, {"Chicago", 345}}},
    {"Pittsburgh", {{"Buffalo", 189}, {"Cleveland", 134}, {"Columbus", 185}, {"Baltimore", 247}, {"Philadelphia", 305}}},
    {"Chicago", {{"Detroit", 283}, {"Cleveland", 345}, {"Indianapolis", 182}}},
    {"Indianapolis", {{"Chicago", 182}, {"Columbus", 176}}},
    {"Columbus", {{"Indianapolis", 176}, {"Cleveland", 144}, {"Pittsburgh", 185}}},
    {"Philadelphia", {{"Syracuse", 253}, {"Pittsburgh", 305}, {"Baltimore", 101}, {"New York", 97}}},
    {"New York", {{"Syracuse", 254}, {"Philadelphia", 97}, {"Boston", 215}, {"Providence", 181}}},
    {"Baltimore", {{"Pittsburgh", 247}, {"Philadelphia", 101}}},
    {"Boston", {{"Syracuse", 312}, {"New York", 215}, {"Providence", 50}, {"Portland", 107}}},
    {"Providence", {{"Boston", 50}, {"New York", 181}}},
    {"Portland", {{"Boston", 107}}}
};

int dfsPathCount = 0;
int bfsPathCount = 0;


void DFS(string current, string destination,
         map<string,bool>& visited,
         vector<string>& path,
         int cost)
{
    if (current == destination) {
        dfsPathCount++;
        cout << "Path: ";
        for (auto city : path) {
           cout << city << " ";
           cout << (city == destination ? "" : " -> ") ;
        }
        cout << "| Cost = " << cost << endl;
        return;
    }

    visited[current] = true;

    for (auto &neighbor : cityGraph[current]) {
        if (!visited[neighbor.first]) {
            path.push_back(neighbor.first);
            DFS(neighbor.first, destination, visited, path, cost + neighbor.second);
            path.pop_back();
        }
    }

    visited[current] = false;
}


void BFS(string start, string destination)
{
    queue<pair<vector<string>, int>> q;
    q.push({{start}, 0});

    cout << "\nBFS Paths:\n";

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        vector<string> path = current.first;
        int cost = current.second;
        string lastCity = path.back();

        if (lastCity == destination) {
            bfsPathCount++;
            cout << "Path: ";
            for (auto &city : path) {
              cout << city << " ";
              cout << (city == destination ? "" : " -> ") ;
            } 
            cout << "| Cost = " << cost << endl;
            continue;
        }

        for (auto &neighbor : cityGraph[lastCity]) {
            if (find(path.begin(), path.end(), neighbor.first) == path.end()) {
                vector<string> newPath = path;
                newPath.push_back(neighbor.first);
                q.push({newPath, cost + neighbor.second});
            }
        }
    }
}


int BFS_Exploration_Cost(string startCity, string destinationCity)
{
    queue<pair<string, pair<vector<string>, int>>> q;
    unordered_set<string> visited;

    q.push({startCity, {{startCity}, 0}});
    visited.insert(startCity);

    int totalExplorationCost = 0;

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        string currentCity = curr.first;
        vector<string> path = curr.second.first;
        int cost = curr.second.second;

        totalExplorationCost += cost;

        if (currentCity == destinationCity)
            break;

        for (auto &neighbor : cityGraph[currentCity]) {
            string nextCity = neighbor.first;
            int edgeCost = neighbor.second;

            if (!visited.count(nextCity)) {
                visited.insert(nextCity);
                vector<string> newPath = path;
                newPath.push_back(nextCity);
                q.push({nextCity, {newPath, cost + edgeCost}});
            }
        }
    }

    return totalExplorationCost;
}


int main()
{
    string startCity = "Syracuse";
    string destinationCity = "Chicago";

    cout << "DFS Paths:\n";
    map<string,bool> visited;
    vector<string> path;
    path.push_back(startCity);

    DFS(startCity, destinationCity, visited, path, 0);
    cout << "\nTotal DFS paths = " << dfsPathCount << endl;

    BFS(startCity, destinationCity);
    cout << "\nTotal BFS paths = " << bfsPathCount << endl;

    int explorationCost = BFS_Exploration_Cost(startCity, destinationCity);
    cout << "\nBFS Exploration Cost = " << explorationCost << endl;

    return 0;
}
