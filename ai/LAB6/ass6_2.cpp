#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x,y,g,h,f;
    vector<pair<int,int>> path;
};

int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};

class pqueue {
    vector<Node> data;

public:
    void push(Node x)
    {
        data.push_back(x);

        int i = data.size()-2;
        while(i >= 0 && data[i].f > x.f){
            data[i+1] = data[i];
            i--;
        }
        data[i+1] = x;
    }

    void pop(){
        data.erase(data.begin()); 
    }

    Node top(){
        return data[0];
    }

    bool empty(){
        return data.empty();
    }
};

bool valid(int x,int y,vector<vector<int>>&maze){
    return x>=0 && y>=0 && x<5 && y<5 && maze[x][y]!=1;
}

int heuristic(int x,int y,int gx,int gy){
    return abs(x-gx)+abs(y-gy); 
}

vector<pair<int,int>> Astar(pair<int,int> start,pair<int,int> goal,vector<vector<int>> maze){

    pqueue pq;
    set<pair<int,int>> visited;

    Node s;
    s.x=start.first; s.y=start.second;
    s.g=0;
    s.h=heuristic(s.x,s.y,goal.first,goal.second);
    s.f=s.g+s.h;
    s.path={{s.x,s.y}};
    pq.push(s);

    while(!pq.empty()){
        Node cur=pq.top(); pq.pop();

        if(visited.count({cur.x,cur.y})) continue;
        visited.insert({cur.x,cur.y});

        if(cur.x==goal.first && cur.y==goal.second)
            return cur.path;

        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];

            if(valid(nx,ny,maze) && !visited.count({nx,ny})){
                Node nxt;
                nxt.x=nx; nxt.y=ny;
                nxt.g=cur.g+1;
                nxt.h=heuristic(nx,ny,goal.first,goal.second);
                nxt.f=nxt.g+nxt.h;
                nxt.path=cur.path;
                nxt.path.push_back({nx,ny});
                pq.push(nxt);
            }
        }
    }
    return {};
}

int main(){

    vector<vector<int>> maze={
    {2,0,0,0,1},
    {0,1,0,0,3},
    {0,3,0,1,1},
    {0,1,0,0,1},
    {3,0,0,0,3}
    };

    pair<int,int> start;
    vector<pair<int,int>> rewards;

    for(int i=0;i<5;i++)
    for(int j=0;j<5;j++){
        if(maze[i][j]==2) start={i,j};
        if(maze[i][j]==3) rewards.push_back({i,j});
    }

    while(!rewards.empty()){

        int best=0,dist=1e9;
        for(int i=0;i<rewards.size();i++){
            int d=heuristic(start.first,start.second,rewards[i].first,rewards[i].second);
            if(d<dist){dist=d;best=i;}
        }

        auto path=Astar(start,rewards[best],maze);

        cout << "\nNearest Reward: ("
             << rewards[best].first << ","
             << rewards[best].second << ")\n";

        cout << "Path: ";
        for(int i=0;i<path.size();i++){
            cout<<"("<<path[i].first<<","<<path[i].second<<")";
            if(i!=path.size()-1) cout<<"->";
        }
        cout<<endl;

        start=rewards[best];
        rewards.erase(rewards.begin()+best);
    }
}
