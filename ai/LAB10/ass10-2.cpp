#include <bits/stdc++.h>
using namespace std;

struct State {
    int A, B;
    char pos;

    string str() const {
        return "(" + to_string(A) + "," + to_string(B) + "," + pos + ")";
    }
};

bool goal(State s) {
    return s.A == 0 && s.B == 0;
}

vector<string> actions = {"Suck", "Left", "Right"};

vector<State> results(State s, string action) {
    vector<State> res;
    if(action == "Suck") {
        // clean_current
        State s1 = s;
        if(s.pos == 'A') s1.A = 0;
        else s1.B = 0;
        res.push_back(s1);

        // clean_both
        State s2 = s;
        s2.A = 0; s2.B = 0;
        res.push_back(s2);

        // erratic:_add dirt
        State s3 = s;
        if(s.pos == 'A') s3.A = 1;
        else s3.B = 1;
        res.push_back(s3);
    }

    else if(action == "Left") {
        State s1 = s;
        s1.pos = 'A';
        res.push_back(s1);
    }

    else if(action == "Right") {
        State s1 = s;
        s1.pos = 'B';
        res.push_back(s1);
    }

    return res;
}

bool OR_SEARCH(State s, set<string> path, int depth);
bool AND_SEARCH(vector<State> states, set<string> path, int depth);

bool OR_SEARCH(State s, set<string> path, int depth) {
    string indent(depth * 2, ' ');
    cout << indent << "OR: Exploring state " << s.str() << endl;
    if(goal(s)) {
        cout << indent << " Goal reached at " << s.str() << endl;
        return true;
    }

    if(path.count(s.str())) {
        cout << indent << " Cycle detected at " << s.str() << endl;
        return false;
    }
    path.insert(s.str());
    for(auto action : actions) {
        cout << indent << "Trying action: " << action << endl;
        vector<State> res = results(s, action);
        cout << indent << "  Possible outcomes:\n";
        for(auto &r : res) {
            cout << indent << "    " << r.str() << endl;
        }
        if(AND_SEARCH(res, path, depth + 1)) {
            cout << indent << " Action " << action << " SUCCESS at " << s.str() << endl;
            return true;
        } else {
            cout << indent << " Action " << action << " FAILED at " << s.str() << endl;
        }
    }

    return false;
}

bool AND_SEARCH(vector<State> states, set<string> path, int depth) {
    string indent(depth * 2, ' ');
    cout << indent << "AND: Checking all outcomes\n";
    for(auto s : states) {
        cout << indent << " Need to solve " << s.str() << endl;
        if(!OR_SEARCH(s, path, depth + 1)) {
            cout << indent << " Failed at " << s.str() << endl;
            return false;
        }
    }
    cout << indent << " All outcomes succeeded\n";
    return true;
}

int main() {
    State start = {1,1,'A'};
    cout << "===== STARTING AND-OR SEARCH =====\n\n";
    if(OR_SEARCH(start, {}, 0))
        cout << "\n Solution exists\n";
    else
        cout << "\n No guaranteed solution\n";

    return 0;
}