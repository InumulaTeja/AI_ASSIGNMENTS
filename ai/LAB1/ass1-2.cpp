#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> friendGraph;

vector<string> BFS(string startFriend)
{
    vector<string> bfsOrder;
    map<string,bool> visitedFriends;
    queue<string> q;

    visitedFriends[startFriend] = true;
    q.push(startFriend);

    while (!q.empty()) {
        string currentFriend = q.front();
        q.pop();
        bfsOrder.push_back(currentFriend);

        for (auto &friendName : friendGraph[currentFriend]) {
            if (!visitedFriends[friendName]) {
                visitedFriends[friendName] = true;
                q.push(friendName);
            }
        }
    }

    return bfsOrder;
}

void DFS_Traversal(string currentFriend, map<string,bool> &visitedFriends, vector<string> &dfsOrder)
{
    visitedFriends[currentFriend] = true;
    dfsOrder.push_back(currentFriend);

    for (auto &friendName : friendGraph[currentFriend]) {
        if (!visitedFriends[friendName]) {
            DFS_Traversal(friendName, visitedFriends, dfsOrder);
        }
    }
}

vector<string> DFS(string startFriend)
{
    vector<string> dfsOrder;
    map<string,bool> visitedFriends;

    DFS_Traversal(startFriend, visitedFriends, dfsOrder);

    return dfsOrder;
}

int main()
{
    
    friendGraph["Raj"]   = {"Sunil","Neha2"};
    friendGraph["Akash"] = {"Sunil","Priya"};
    friendGraph["Sunil"] = {"Raj", "Maya","Sneha","Akash"};
    friendGraph["Sneha"] = {"Sunil", "Neha2","Rahul"};
    friendGraph["Maya"]  = {"Sunil", "Rahul","Arjun1"};
    friendGraph["Priya"] = {"Raj","Neha2", "Aarav","Akash"};
    friendGraph["Neha"]  = {"Raj", "Akash", "Aarav","Sneha"};
    friendGraph["Neha1"] = {"Priya","Neha2","Rahul","Aarav"};
    friendGraph["Rahul"] = {"Neha2","Neha1","Sneha","Pooja","Maya","Arjun2"};
    friendGraph["Aarav"] = {"Neha2","Neha1", "Arjun2"};
    friendGraph["Arjun"] = {"Rahul", "Neha1","Aarav"};
    friendGraph["Arjun1"] = {"Maya","Pooja"};
    friendGraph["Pooja"] = {"Rahul","Arjun2", "Arjun1"};

    string startFriend = "Raj";

    vector<string> bfsOrder = BFS(startFriend);
    cout << "BFS TRAVERSAL" << "\n";
    for (auto &f : bfsOrder)
        cout << f << "  ";
    cout << "\n";

    
    vector<string> dfsOrder = DFS(startFriend);
    cout << "DFS TRAVERSAL" << "\n";
    for (auto &f : dfsOrder)
        cout << f << "  ";
    cout << "\n";

    return 0;
}
