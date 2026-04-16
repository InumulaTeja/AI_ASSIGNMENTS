#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int stepCount = 0; 

bool ok(string a, string b) {
    return a != b;
}

bool checkArc(map<string, vector<string>> &dom, string A, string B) {
    bool changed = false;          
    vector<string> temp;           

    // Check each value of A
    for (auto valA : dom[A]) {
        bool possible = false;     

        // Compare with all values of B
        for (auto valB : dom[B]) {
            if (ok(valA, valB)) {   
                possible = true;
                break;
            }
        }

        if (possible) {
            temp.push_back(valA);
        } 
        else {
            changed = true;       
        }
    }

    if (stepCount < 5) {
        cout << "Arc (" << A << "," << B << ") checked, ";
        if (changed)
            cout << "domain reduced\n";
        else
            cout << "no change\n";
        stepCount++;
    }

    dom[A] = temp;

    return changed; 
}

bool runAC3(map<string, vector<string>> &dom,
            map<string, vector<string>> &adj) {

    queue<pair<string, string>> q;  

    for (auto x : adj) {
        for (auto y : x.second) {
            q.push({x.first, y});
        }
    }

    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        string A = p.first;
        string B = p.second;

        if (checkArc(dom, A, B)) {
            if (dom[A].empty()) {
                return false;
            }

            // Add all neighbors again (except B)
            // because change in A may affect them
            for (auto k : adj[A]) {
                if (k != B) {
                    q.push({k, A});
                }
            }
        }
    }

    return true; // arc-consistent
}

int main() {

    map<string, vector<string>> dom = {
        {"P1", {"R1", "R2", "R3"}},
        {"P2", {"R1", "R2", "R3"}},
        {"P3", {"R1", "R2", "R3"}},
        {"P4", {"R1", "R2", "R3"}},
        {"P5", {"R1", "R2", "R3"}},
        {"P6", {"R1", "R2", "R3"}}
    };

    map<string, vector<string>> adj = {
        {"P1", {"P2", "P3", "P6"}},
        {"P2", {"P1", "P3", "P4"}},
        {"P3", {"P1", "P2", "P5"}},
        {"P4", {"P2", "P6"}},
        {"P5", {"P3", "P6"}},
        {"P6", {"P1", "P4", "P5"}}
    };

    bool result = runAC3(dom, adj);
    cout << "\nFinal Result:\n";

    if (result) {
        cout << "Problem is ARC-CONSISTENT\n";
    } else {
        cout << "Problem is NOT arc-consistent\n";
    }

    cout << "\nFinal Domains:\n";
    for (auto x : dom) {
        cout << x.first << " -> ";
        for (auto r : x.second) {
            cout << r << " ";
        }
        cout << endl;
    }

    return 0;
}