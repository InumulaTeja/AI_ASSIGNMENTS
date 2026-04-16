#include <bits/stdc++.h>
using namespace std;

vector<string> cities = {"A","B","C","D","E","F","G","H"};

int costMatrix[8][8] = {
{0,10,15,20,25,30,35,40},
{12,0,35,15,20,25,30,45},
{25,30,0,10,40,20,15,35},
{18,25,12,0,15,30,20,10},
{22,18,28,20,0,15,25,30},
{35,22,18,28,12,0,40,20},
{30,35,22,18,28,32,0,15},
{40,28,35,22,18,25,12,0}
};

int tourCost(const vector<int>& path)
{
    int cost = 0;
    for(int i=0;i<path.size()-1;i++)
        cost += costMatrix[path[i]][path[i+1]];

    cost += costMatrix[path.back()][path[0]];
    return cost;
}

vector<int> randomPath()
{
    vector<int> p = {0,1,2,3,4,5,6,7};
    random_shuffle(p.begin()+1, p.end());
    return p;
}

vector<int> selectParent(vector<vector<int>>& population)
{
    int a = rand()%population.size();
    int b = rand()%population.size();

    if(tourCost(population[a]) < tourCost(population[b]))
        return population[a];
    return population[b];
}

vector<int> onePointCrossover(vector<int> p1, vector<int> p2)
{
    int n = p1.size();
    int cut = 1 + rand()%(n-2);

    vector<int> child(n,-1);

    for(int i=0;i<=cut;i++)
        child[i]=p1[i];

    int index=cut+1;

    for(int x:p2)
        if(find(child.begin(),child.end(),x)==child.end())
            child[index++]=x;

    return child;
}

vector<int> twoPointCrossover(vector<int> p1, vector<int> p2)
{
    int n=p1.size();
    int c1=1+rand()%(n-3);
    int c2=c1+1+rand()%(n-c1-2);

    vector<int> child(n,-1);

    for(int i=c1;i<=c2;i++)
        child[i]=p1[i];

    int idx=0;
    for(int x:p2)
    {
        if(find(child.begin(),child.end(),x)==child.end())
        {
            while(child[idx]!=-1) idx++;
            child[idx]=x;
        }
    }

    return child;
}

void mutate(vector<int>& path)
{
    int i=1+rand()%7;
    int j=1+rand()%7;
    swap(path[i],path[j]);
}

pair<vector<int>,int> geneticAlgorithm(bool twoPoint)
{
    int POP_SIZE=20;
    int GENERATIONS=200;
    double MUT_RATE=0.2;

    vector<vector<int>> population;

    for(int i=0;i<POP_SIZE;i++)
        population.push_back(randomPath());

    vector<int> best;
    int bestCost=INT_MAX;

    for(int g=0;g<GENERATIONS;g++)
    {
        vector<vector<int>> newPop;
        for(int i=0;i<POP_SIZE;i++)
        {
            vector<int> p1=selectParent(population);
            vector<int> p2=selectParent(population);
            vector<int> child;
            if(twoPoint)
                child=twoPointCrossover(p1,p2);
            else
                child=onePointCrossover(p1,p2);

            if((double)rand()/RAND_MAX < MUT_RATE)
                mutate(child);

            newPop.push_back(child);
        }

        population=newPop;
        for(auto &p:population)
        {
            int c=tourCost(p);
            if(c<bestCost)
            {
                bestCost=c;
                best=p;
            }
        }
    }
    return {best,bestCost};
}

int main()
{
    srand(time(0));
    cout<<"--- One Point Crossover ---\n";
    auto r1 = geneticAlgorithm(false);
    for(int x:r1.first)
        cout<<cities[x]<<" ";
    cout<<cities[r1.first[0]];
    cout<<"\nCost = "<<r1.second<<"\n\n";

    cout<<"--- Two Point Crossover ---\n";
    auto r2 = geneticAlgorithm(true);
    for(int x:r2.first)
        cout<<cities[x]<<" ";
    cout<<cities[r2.first[0]];
    cout<<"\nCost = "<<r2.second<<"\n";

    return 0;
}