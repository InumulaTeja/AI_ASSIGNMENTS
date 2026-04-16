#include<bits/stdc++.h>
using namespace std;

struct state
{
    int gl;
    int bl;
    int boat;   // 0 = Left, 1 = Right
};

map<string, bool> visited;
vector<state> path;
int exploredCount = 0;

string getKey(state s)
{
    return to_string(s.gl) + "-" +to_string(s.bl) + "-" +to_string(s.boat);
}

bool isValid(state s)
{
    if (s.gl < 0 || s.gl > 3 || s.bl < 0 || s.bl > 3)
        return false;

    int gr = 3 - s.gl;
    int br = 3 - s.bl;
    if (s.gl > 0 && s.gl < s.bl)
        return false;

    if (gr > 0 && gr < br)
        return false;

    return true;
}

bool isGoal(state s)
{
    return (s.gl == 0 && s.bl == 0 && s.boat == 1);
}

void printPath()
{
    cout << "\nSolution Path:\n";
    for(int i = 0; i < path.size(); i++)
    {
        cout << " . ("<< path[i].gl << ", "<< path[i].bl << ", "<< (path[i].boat == 0 ? "Left" : "Right")<< ")\n";
    }
}

bool DLS(state current, int limit)
{
    exploredCount++;  
    path.push_back(current);
    if (isGoal(current))
    {
        printPath();
        return true;
    }
    if (limit == 0)
    {
        path.pop_back();
        return false;
    }
    visited[getKey(current)] = true;
    int moves[5][2] = {{1,0}, {0,1}, {2,0}, {0,2}, {1,1}};
    for(int i = 0; i < 5; i++)
    {
        state next = current;
        if(current.boat == 0)
        {
            next.gl -= moves[i][0];
            next.bl -= moves[i][1];
            next.boat = 1;
        }
        else
        {
            next.gl += moves[i][0];
            next.bl += moves[i][1];
            next.boat = 0;
        }
        if(isValid(next) && !visited[getKey(next)])
        {
            if(DLS(next, limit - 1))
                return true;
        }
    }
    path.pop_back();
    return false;
}

int main()
{
    state initial = {3, 3, 0};
    int depth_limit = 3;
    bool result = DLS(initial, depth_limit);
    if(!result)
        cout << "Goal not reachable.\n";

    cout << "\nTotal Explored States: "
         << exploredCount << endl;

    return 0;
}
