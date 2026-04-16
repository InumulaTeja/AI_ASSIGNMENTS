#include <bits/stdc++.h>
using namespace std;

class LogicSystem
{
private:

    int getPrecedence(string op)
    {
        if (op == "~") return 4;
        if (op == "^") return 3;
        if (op == "v") return 2;
        if (op == "->") return 1;
        if (op == "<->") return 0;
        return -1;
    }

    bool isRightAssociative(string op)
    {
        return (op == "~" || op == "->" || op == "<->");
    }

    bool applyOperator(string op, bool a, bool b = false)
    {
        if (op == "~") return !a;
        if (op == "^") return a && b;
        if (op == "v") return a || b;
        if (op == "->") return (!a) || b;
        if (op == "<->") return a == b;
        return false;
    }

    vector<string> tokenize(string expr)
    {
        vector<string> tokens;

        for (int i = 0; i < expr.size(); i++)
        {
            if (expr[i] == ' ') continue;

            if (isalpha(expr[i]))
                tokens.push_back(string(1, expr[i]));

            else if (expr[i] == '~')
                tokens.push_back("~");

            else if (expr[i] == '^')
                tokens.push_back("^");

            else if (expr[i] == 'v' || expr[i] == '∨')
                tokens.push_back("v");

            else if (expr[i] == '∧')
                tokens.push_back("^");

            else if (i+2 < expr.size() && expr.substr(i,3) == "<->")
            {
                tokens.push_back("<->");
                i += 2;
            }
            else if (i+1 < expr.size() && expr.substr(i,2) == "->")
            {
                tokens.push_back("->");
                i++;
            }
            else if (expr[i] == '(' || expr[i] == ')')
                tokens.push_back(string(1, expr[i]));
        }

        return tokens;
    }

    vector<string> infixToPostfix(vector<string> &tokens)
    {
        vector<string> output;
        stack<string> ops;

        for (string tok : tokens)
        {
            if (isalpha(tok[0]))
            {
                output.push_back(tok);
            }
            else if (tok == "(")
            {
                ops.push(tok);
            }
            else if (tok == ")")
            {
                while (!ops.empty() && ops.top() != "(")
                {
                    output.push_back(ops.top());
                    ops.pop();
                }
                ops.pop();
            }
            else
            {
                while (!ops.empty() && ops.top() != "(")
                {
                    string topOp = ops.top();

                    int p1 = getPrecedence(tok);
                    int p2 = getPrecedence(topOp);

                    if ((!isRightAssociative(tok) && p1 <= p2) ||
                        ( isRightAssociative(tok) && p1 < p2))
                    {
                        output.push_back(topOp);
                        ops.pop();
                    }
                    else break;
                }
                ops.push(tok);
            }
        }

        while (!ops.empty())
        {
            output.push_back(ops.top());
            ops.pop();
        }

        return output;
    }

    bool evaluatePostfix(vector<string> &postfix, bool values[])
    {
        stack<bool> st;

        for (string tok : postfix)
        {
            if (isalpha(tok[0]))
            {
                int index = tok[0] - 'P';
                st.push(values[index]);
            }
            else if (tok == "~")
            {
                bool a = st.top(); st.pop();
                st.push(applyOperator("~", a));
            }
            else
            {
                bool b = st.top(); st.pop();
                bool a = st.top(); st.pop();
                st.push(applyOperator(tok, a, b));
            }
        }

        return st.top();
    }

    void getSymbols(string expr, bool used[])
    {
        for (int i = 0; i < expr.size(); i++)
        {
            if (isalpha(expr[i]))
            {
                int index = expr[i] - 'P';
                used[index] = true;
            }
        }
    }

public:

    void printTruthTable(string expr)
    {
        bool used[3] = {false};
        getSymbols(expr, used);

        vector<char> symbols;
        for (int i = 0; i < 3; i++)
            if (used[i]) symbols.push_back('P' + i);

        vector<string> tokens = tokenize(expr);
        vector<string> postfix = infixToPostfix(tokens);

        int n = symbols.size();
        int rows = 1 << n;

        cout << "\n====================================\n";
        cout << "Expression: " << expr << "\n";
        cout << "====================================\n";

        for (char c : symbols) cout << c << " ";
        cout << "| Result\n";

        for (int i = 0; i < rows; i++)
        {
            bool values[3] = {false};

            for (int j = 0; j < n; j++)
            {
                bool val = (i >> (n-j-1)) & 1;
                values[symbols[j] - 'P'] = val;

                cout << (val ? "T " : "F ");
            }

            bool result = evaluatePostfix(postfix, values);
            cout << "| " << (result ? "T" : "F") << "\n";
        }
    }
};

int main()
{
    LogicSystem obj;

    vector<string> expressions = {
        "~P->Q",
        "~P^~Q",
        "~Pv~Q",
        "~P->~Q",
        "~P<->~Q",
        "(PvQ)^(~P->Q)",
        "(PvQ)->~R",
        "((PvQ)->~R)<->((~P^~Q)->~R)",
        "((P->Q)^(Q->R))->(Q->R)",
        "((P->(QvR))->(~P^~Q^~R))"
    };

    for (string expr : expressions)
    {
        obj.printTruthTable(expr);
    }
    return 0;
}