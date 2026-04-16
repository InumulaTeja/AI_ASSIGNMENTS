#include <bits/stdc++.h>
using namespace std;

const int N = 8;
const int MAX_RESTARTS = 50;

struct Result {
    vector<int> initial_board;
    vector<int> final_board;
    int initial_h;
    int final_h;
    int steps;
    string status;
};


void printBoard(vector<int> &board) {
    for(int i=0;i<N;i++)
        cout << board[i] << " ";
}

int heuristic(vector<int> &board) {
    int h = 0;
    for(int i=0;i<N;i++)
        for(int j=i+1;j<N;j++)
            if(board[i]==board[j] || abs(board[i]-board[j])==abs(i-j))
                h++;
    return h;
}

vector<int> randomBoard() {
    vector<int> board(N);
    for(int i=0;i<N;i++)
        board[i] = rand()%N;
    return board;
}

Result firstChoiceHillClimb(vector<int> board) {

    Result res;
    res.initial_board = board;
    res.initial_h = heuristic(board);
    res.steps = 0;

    while(true) {

        int current_h = heuristic(board);
        bool moved = false;

        for(int col=0; col<N && !moved; col++) {

            int original = board[col];

            for(int row=0; row<N; row++) {

                if(row==original) continue;

                board[col]=row;
                int h=heuristic(board);

                if(h<current_h) {
                    moved=true;
                    res.steps++;
                    break;
                }
            }

            if(!moved)
                board[col]=original;
        }

        if(!moved) {
            res.final_board=board;
            res.final_h=heuristic(board);
            res.status=(res.final_h==0)?"Solved":"Local Minima";
            return res;
        }
    }
}

Result steepestHillClimb(vector<int> board) {

    Result res;
    res.initial_board=board;
    res.initial_h=heuristic(board);
    res.steps=0;

    while(true){

        int current_h=heuristic(board);
        int best_h=current_h;
        vector<int> best_board=board;

        for(int col=0;col<N;col++){
            int original=board[col];

            for(int row=0;row<N;row++){
                if(row==original) continue;

                board[col]=row;
                int h=heuristic(board);

                if(h<best_h){
                    best_h=h;
                    best_board=board;
                }
            }
            board[col]=original;
        }

        if(best_h>=current_h){
            res.final_board=board;
            res.final_h=current_h;
            res.status=(current_h==0)?"Solved":"Fail";
            return res;
        }

        board=best_board;
        res.steps++;
    }
}

Result randomRestartHillClimb(){

    Result best;
    best.final_h=INT_MAX;

    for(int i=1;i<=MAX_RESTARTS;i++){

        vector<int> board=randomBoard();
        Result r=steepestHillClimb(board);

        if(r.final_h<best.final_h)
            best=r;

        if(r.final_h==0){
            best.status="Solved after Restart";
            return best;
        }
    }

    best.status="Fail after Restarts";
    return best;
}

int main(){

    srand(time(0));

    for(int i=1;i<=50;i++){

        cout<<"\n================ RUN "<<i<<" ================\n";

        // FIRST CHOICE
        cout<<"\n--- First Choice Hill Climb ---\n";
        Result fc=firstChoiceHillClimb(randomBoard());

        cout<<"Initial Board : "; printBoard(fc.initial_board); cout<<endl;
        cout<<"Final Board   : "; printBoard(fc.final_board); cout<<endl;
        cout<<"Initial h     : "<<fc.initial_h<<endl;
        cout<<"Final h       : "<<fc.final_h<<endl;
        cout<<"Steps         : "<<fc.steps<<endl;
        cout<<"Status        : "<<fc.status<<endl;

        // RANDOM RESTART
        cout<<"\n--- Random Restart Hill Climb ---\n";
        Result rr=randomRestartHillClimb();

        cout<<"Initial Board : "; printBoard(rr.initial_board); cout<<endl;
        cout<<"Final Board   : "; printBoard(rr.final_board); cout<<endl;
        cout<<"Initial h     : "<<rr.initial_h<<endl;
        cout<<"Final h       : "<<rr.final_h<<endl;
        cout<<"Steps         : "<<rr.steps<<endl;
        cout<<"Status        : "<<rr.status<<endl;
    }
}