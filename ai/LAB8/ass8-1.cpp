#include <bits/stdc++.h>
using namespace std;

vector<string> cities = {"A","B","C","D","E","F","G","H"};

int costMatrix[8][8] = {
{0,10,15,20,25,30,35,40},
{12,0,35,15,20,25,30,45},
{25,30,0,10,40,20,15,35},
{18,25,12,0,15,30,20,10},
{22,18,28,20,0,15,25,30},
{35,22,18,28,12,0,40,20},
{30,35,22,18,28,32,0,15},
{40,28,35,22,18,25,12,0}
};

int tourCost(vector<int> path)
{
    int total = 0;
    for(int i = 0; i < path.size()-1; i++)
        total += costMatrix[path[i]][path[i+1]];
    total += costMatrix[path.back()][path[0]];
    return total;
}

vector<vector<int>> getNeighbors(vector<int> path)
{
    vector<vector<int>> neighbors;
    for(int i = 1; i < path.size(); i++)
    {
        for(int j = i+1; j < path.size(); j++)
        {
            vector<int> newPath = path;
            swap(newPath[i], newPath[j]);
            neighbors.push_back(newPath);
        }
    }
    return neighbors;
}
pair<vector<int>,int> localBeamSearch(int k, int iterations)
{
    vector<vector<int>> states;
    srand(time(0));
    for(int i = 0; i < k; i++)
    {
        vector<int> path = {0,1,2,3,4,5,6,7};
        random_shuffle(path.begin()+1, path.end());
        states.push_back(path);
    }
    vector<int> bestPath;
    int bestCost = INT_MAX;
    for(int it = 0; it < iterations; it++)
    {
        vector<vector<int>> allNeighbors;
        for(auto s : states)
        {
            vector<vector<int>> neigh = getNeighbors(s);
            allNeighbors.insert(allNeighbors.end(),neigh.begin(), neigh.end());
        }
        sort(allNeighbors.begin(), allNeighbors.end(),[](vector<int> a, vector<int> b){
            return tourCost(a) < tourCost(b);
        });

        states.clear();
        for(int i = 0; i < k; i++)
            states.push_back(allNeighbors[i]);
        int currentCost = tourCost(states[0]);
        if(currentCost < bestCost)
        {
            bestCost = currentCost;
            bestPath = states[0];
        }
    }

    return {bestPath, bestCost};
}

int main()
{
    vector<int> kValues = {3,5,10};
    for(int k : kValues)
    {
        auto result = localBeamSearch(k, 50);
        cout << "\nBeam Width k = " << k << endl;
        cout << "Best Path: ";
        for(int i : result.first)
            cout << cities[i] << " ";

        cout << cities[result.first[0]];
        cout << "\nCost: " << result.second << endl;
    }

    return 0;
}