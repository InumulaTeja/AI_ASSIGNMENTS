#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct node {
    vector<int> path;
    int g;   // actual distance travelled
    int h;   // heuristic
    int f;   // total cost (priority)
};

class priorityQueue {
    vector<node> data;
    int frontIndex = 0;
public:
    void push(node x) {
        if (data.empty()) {
            data.push_back(x);
            return;
        }
        int i = data.size() - 1;
        data.push_back(x);

        while (i >= frontIndex && data[i].f > x.f) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = x;
    }

    void pop() { frontIndex++; }
    node front() { return data[frontIndex]; }
    bool empty() { return frontIndex >= data.size(); }
};

vector<string> cities = {
"Chicago","Indianapolis","Cleveland","Detroit","Columbus","Pittsburgh",
"Baltimore","Philadelphia","Buffalo","New York","Providence","Boston","Portland","Syracuse"
};

vector<int> heuristic = {
860,780,550,610,640,470,360,270,400,215,50,0,107,260
};

vector<vector<int>> adjMatrix = {
{0,182,345,283,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
{182,0,INF,INF,176,INF,INF,INF,INF,INF,INF,INF,INF,INF},
{345,INF,0,169,144,134,INF,INF,189,INF,INF,INF,INF,INF},
{283,INF,169,0,INF,INF,INF,INF,256,INF,INF,INF,INF,INF},
{INF,176,144,INF,0,185,INF,INF,INF,INF,INF,INF,INF,INF},
{INF,INF,134,INF,185,0,247,305,215,INF,INF,INF,INF,INF},
{INF,INF,INF,INF,INF,247,0,101,INF,INF,INF,INF,INF,INF},
{INF,INF,INF,INF,INF,305,101,0,INF,97,INF,INF,INF,253},
{INF,INF,189,256,INF,215,INF,INF,0,INF,INF,INF,INF,150},
{INF,INF,INF,INF,INF,INF,INF,97,INF,0,181,215,INF,254},
{INF,INF,INF,INF,INF,INF,INF,INF,INF,181,0,50,INF,INF},
{INF,INF,INF,INF,INF,INF,INF,INF,INF,215,50,0,107,312},
{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,107,0,INF},
{INF,INF,INF,INF,INF,INF,INF,253,150,254,INF,312,INF,0}
};

void As(int start, int goal)
{
    priorityQueue pq;
    set<int> explored;

    node startNode;
    startNode.path = {start};
    startNode.g = 0;
    startNode.h = heuristic[start];
    startNode.f = startNode.g + startNode.h;

    pq.push(startNode);

    while (!pq.empty())
    {
        node curr = pq.front();
        pq.pop();

        int city = curr.path.back();

        if(explored.count(city)) continue;
        explored.insert(city);

        cout<<"Path: ";
        for(int i:curr.path) cout<<cities[i]<<" -> ";
        cout<<" f="<<curr.f<<endl;

        if(city==goal){
            cout<<"\nCities explored: "<<explored.size()<<endl;
            return;
        }

        for(int i=0;i<adjMatrix.size();i++)
        {
            if(adjMatrix[city][i]!=INF && !explored.count(i))
            {
                node next;
                next.path=curr.path;
                next.path.push_back(i);
                next.g=curr.g+adjMatrix[city][i];
                next.h=heuristic[i];
                next.f=next.g+next.h;
                pq.push(next);
            }
        }
    }
}

int main()
{
    int start=0;  
    int goal=11;   

    As(start,goal);
}
