#include<bits/stdc++.h>
using namespace std;

const int N = 25;

string names[N] = {
    "Banaskantha","Patan","Mehsana","Sabarkantha","GandhiNagar","Ahmedabad","Surendranagar","Kheda","Panchmahal","Dahod","Anand","Vadodara","Rajkot",
    "Jamnagar","Porbandar","Junaghad","Bhavnagar","Amreli","Bharuch","Narmada","Surat","Navsari","Dangs","Valsad","Kuchchh"
};

vector<int> adj[N] = {
    {1,2,3},                    // 0: Banaskantha
    {0,2,6},                    // 1: Patan
    {0,1,3,4,5,6},              // 2: Mehsana
    {0,2,4,7,8},                // 3: Sabarkantha
    {2,3,5,7,8},                // 4: GandhiNagar
    {2,4,6,7,10,16},            // 5: Ahmedabad
    {1,2,5,12,16,17},           // 6: Surendranagar
    {3,4,5,8,10,11},            // 7: Kheda
    {3,4,7,9,11},               // 8: Panchmahal
    {8,11},                     // 9: Dahod
    {5,7,11,16},                // 10: Anand
    {7,8,9,10,18,19},           // 11: Vadodara
    {6,13,15,16,17},            // 12: Rajkot
    {12,14,15},                 // 13: Jamnagar
    {13,15},                    // 14: Porbandar
    {13,14,17},                 // 15: Junaghad 
    {5,6,10,12,17,18},          // 16: Bhavnagar
    {6,12,15,16,18},            // 17: Amreli
    {11,16,17,19,20},           // 18: Bharuch
    {11,18,20},                 // 19: Narmada
    {18,19,21},                 // 20: Surat
    {20,22,23},                 // 21: Navsari
    {21,23},                    // 22: Dangs 
    {21,22},                    // 23: Valsad 
    {}                          // 24: Kuchchh 
};

int color[N];
int numColors = 4;

bool isSafe(int v, int c) {
    for (int u : adj[v]) {
        if (color[u] == c) return false;
    }
    return true;
}

bool solve(int v) {
    if (v == N) return true;
    for (int c = 1; c <= numColors; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            if (solve(v + 1)) return true;
            color[v] = 0;
        }
    }
    return false;
}

int main() {
    fill(color, color + N, 0);

    cout << " Gujarat district map coloring \n\n";

    for (int k = 1; k <= 4; k++) {
        numColors = k;
        fill(color, color + N, 0);
        if (solve(0)) {
            cout << "Minimum colors needed: " << k << "\n\n";
            cout << "District Coloring:\n";
            cout << string(40, '-') << "\n";
            for (int i = 0; i < N; i++) {
                cout << names[i] << " -> Color " << color[i] << "\n";
            }
            break;
        }
    }
    return 0;
}