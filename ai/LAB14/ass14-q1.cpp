#include <bits/stdc++.h>
using namespace std;

bool forwardInfer(vector<pair<vector<string>, string>> ruleSet,
                  vector<string> initialFacts,
                  string target) {

    queue<string> processQueue;
    set<string> known;

    for (auto item : initialFacts) {
        processQueue.push(item);
        known.insert(item);
    }

    map<int, int> pendingCount;
    for (int idx = 0; idx < ruleSet.size(); idx++) {
        pendingCount[idx] = ruleSet[idx].first.size();
    }

    while (!processQueue.empty()) {
        string current = processQueue.front();
        processQueue.pop();

        if (current == target) return true;

        for (int idx = 0; idx < ruleSet.size(); idx++) {
            auto &conditions = ruleSet[idx].first;
            auto result = ruleSet[idx].second;

            if (find(conditions.begin(), conditions.end(), current) != conditions.end()) {
                pendingCount[idx]--;

                if (pendingCount[idx] == 0 && !known.count(result)) {
                    known.insert(result);
                    processQueue.push(result);
                }
            }
        }
    }
    return false;
}

bool backwardHelper(string goal,
                    vector<pair<vector<string>, string>> &ruleSet,
                    set<string> &knownFacts,
                    set<string> &visitedGoals) {

    if (knownFacts.count(goal)) return true;
    if (visitedGoals.count(goal)) return false;

    visitedGoals.insert(goal);

    for (auto &rule : ruleSet) {
        if (rule.second == goal) {
            bool satisfied = true;

            for (auto &cond : rule.first) {
                if (!backwardHelper(cond, ruleSet, knownFacts, visitedGoals)) {
                    satisfied = false;
                    break;
                }
            }

            if (satisfied) return true;
        }
    }
    return false;
}

bool backwardInfer(vector<pair<vector<string>, string>> ruleSet,
                   vector<string> initialFacts,
                   string target) {

    set<string> factBase(initialFacts.begin(), initialFacts.end());
    set<string> visited;

    return backwardHelper(target, ruleSet, factBase, visited);
}

typedef set<string> ClauseSet;

bool checkNegation(string x, string y) {
    return (x == "~" + y || y == "~" + x);
}

vector<ClauseSet> applyResolution(ClauseSet cA, ClauseSet cB) {
    vector<ClauseSet> results;

    for (auto litA : cA) {
        for (auto litB : cB) {
            if (checkNegation(litA, litB)) {
                ClauseSet newClause;

                for (auto v : cA) if (v != litA) newClause.insert(v);
                for (auto v : cB) if (v != litB) newClause.insert(v);

                results.push_back(newClause);
            }
        }
    }
    return results;
}

bool resolveKB(vector<ClauseSet> knowledgeBase, ClauseSet queryClause) {

    set<ClauseSet> allClauses(knowledgeBase.begin(), knowledgeBase.end());
    allClauses.insert(queryClause);

    while (true) {
        set<ClauseSet> generated;

        vector<ClauseSet> clauseList(allClauses.begin(), allClauses.end());

        for (int i = 0; i < clauseList.size(); i++) {
            for (int j = i + 1; j < clauseList.size(); j++) {

                auto newRes = applyResolution(clauseList[i], clauseList[j]);

                for (auto &cl : newRes) {
                    if (cl.empty()) return true;
                    generated.insert(cl);
                }
            }
        }

        bool expanded = false;
        for (auto &cl : generated) {
            if (!allClauses.count(cl)) {
                allClauses.insert(cl);
                expanded = true;
            }
        }

        if (!expanded) return false;
    }
}

int main() {

    cout << "FORWARD CHAINING:\n";

    vector<pair<vector<string>, string>> rulesA = {
        {{"P"}, "Q"},
        {{"L","M"}, "P"},
        {{"A","B"}, "L"}
    };
    vector<string> factsA = {"A","B","M"};

    cout << "a) " << (forwardInfer(rulesA, factsA, "Q") ? "TRUE\n" : "FALSE\n");

    vector<pair<vector<string>, string>> rulesB = {
        {{"A"}, "B"},
        {{"B"}, "C"},
        {{"C"}, "D"},
        {{"D","E"}, "F"}
    };
    vector<string> factsB = {"A","E"};

    cout << "b) " << (forwardInfer(rulesB, factsB, "F") ? "TRUE\n" : "FALSE\n");


    cout << "\nBACKWARD CHAINING:\n";

    vector<pair<vector<string>, string>> rulesC = {
        {{"P"}, "Q"},
        {{"R"}, "Q"},
        {{"A"}, "P"},
        {{"B"}, "R"}
    };
    vector<string> factsC = {"A","B"};

    cout << "a) " << (backwardInfer(rulesC, factsC, "Q") ? "TRUE\n" : "FALSE\n");

    vector<pair<vector<string>, string>> rulesD = {
        {{"A"}, "B"},
        {{"B","C"}, "D"},
        {{"E"}, "C"}
    };
    vector<string> factsD = {"A","E"};

    cout << "b) " << (backwardInfer(rulesD, factsD, "D") ? "TRUE\n" : "FALSE\n");


    cout << "\nRESOLUTION:\n";

    vector<ClauseSet> rulesE = {
        {"P","Q"},
        {"~P","R"},
        {"~Q","S"},
        {"~R","S"}
    };
    ClauseSet queryA = {"~S"};

    cout << "a) " << (resolveKB(rulesE, queryA) ? "TRUE\n" : "FALSE\n");

    vector<ClauseSet> rulesF = {
        {"~P","Q"},
        {"~Q","R"},
        {"~S","~R"},
        {"P"}
    };
    ClauseSet queryB = {"~S"};

    cout << "b) " << (resolveKB(rulesF, queryB) ? "TRUE\n" : "FALSE\n");

    return 0;
}