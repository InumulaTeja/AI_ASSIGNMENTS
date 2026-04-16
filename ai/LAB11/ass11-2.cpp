#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> pool = {0,1,2,3,4,5,6,7,8,9};
    int found = 0;
    for (int skip1 = 0; skip1 < 10; skip1++) {
        for (int skip2 = skip1+1; skip2 < 10; skip2++) {
            vector<int> chosen;
            for (int d = 0; d < 10; d++)
                if (d != skip1 && d != skip2)
                    chosen.push_back(d);

            sort(chosen.begin(), chosen.end());
            do {
                int S = chosen[0], E = chosen[1], N = chosen[2], D = chosen[3];
                int M = chosen[4], O = chosen[5], R = chosen[6], Y = chosen[7];

                if (S == 0 || M == 0) continue;

                int SEND  =  S*1000 + E*100 + N*10 + D;
                int MORE  =  M*1000 + O*100 + R*10 + E;
                int MONEY =  M*10000 + O*1000 + N*100 + E*10 + Y;

                if (SEND + MORE == MONEY) {
                    found++;
                    cout << "========== SOLUTION " << found << " ==========\n";
                    cout << " S=" << S << "  E=" << E
                         << "  N=" << N << "  D=" << D << "\n";
                    cout << " M=" << M << "  O=" << O
                         << "  R=" << R << "  E=" << Y << "\n\n";
                    cout << "    S E N D\n";
                    cout << "    " << S <<E <<N <<D << "\n";
                    cout << "    M O R E\n";
                    cout << "  + " << M<<O<<R<<E << "\n";
                    cout << "  -------\n";
                    cout << "  " << M<<O<<N<<E<<Y << "\n";
                    cout << "  (MONEY)\n\n";
                }

            } while (next_permutation(chosen.begin(), chosen.end()));
        }
    }

    if (found == 0)
        cout << "No solution found.\n";
    else
        cout << "Total solutions: " << found << "\n";

    return 0;
}