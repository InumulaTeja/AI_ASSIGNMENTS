#include <bits/stdc++.h>
using namespace std;

struct P {
    double x,y; 
};

vector<P> loadCSV(string f){
    ifstream in(f); 
    if(!in){ 
        cout<<"Cannot open file\n"; exit(0); 
    }
    vector<P> c; 
    string line;
    if(getline(in,line)){
        replace(line.begin(),line.end(),',',' ');
        stringstream ss(line); 
        P t;
        if(ss>>t.x>>t.y) c.push_back(t);
    }
    while(getline(in,line)){
        if(line.empty()) continue;
        replace(line.begin(),line.end(),',',' ');
        stringstream ss(line); 
        P t;
        if(ss>>t.x>>t.y) c.push_back(t);
    }
    cout<<"Loaded "<<c.size()<<" cities\n\n";
    return c;
}

inline double d2(const P&a,const P&b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

vector<int> assignCities(const vector<P>&c,const vector<P>&a){
    vector<int> L(c.size());
    for(int i=0;i<(int)c.size();i++){
        double best=1e18; 
        int bk=0;
        for(int k=0;k<(int)a.size();k++){
            double d=d2(c[i],a[k]);
            if(d<best){ 
                best=d; 
                bk=k; 
            }
        }
        L[i]=bk;
    }
    return L;
}

vector<P> initialize(const vector<P>&c,int K){
    mt19937 g(42); 
    vector<P> a;
    uniform_int_distribution<int> u(0,(int)c.size()-1);
    a.push_back(c[u(g)]);
    for(int k=1;k<K;k++){
        vector<double> d(c.size()); 
        double sum=0;
        for(int i=0;i<(int)c.size();i++){
            double b=1e18;
            for(auto&ap:a) b=min(b,d2(c[i],ap));
            d[i]=b; sum+=b;
        }
        uniform_real_distribution<double> R(0,sum);
        double r=R(g),acc=0;
        for(int i=0;i<(int)c.size();i++){
            acc+=d[i];
            if(acc>=r){ 
                a.push_back(c[i]); 
                break; 
            }
        }
    }
    return a;
}

double SSD(const vector<P>&c,const vector<P>&a,const vector<int>&L){
    double s=0;
    for(int i=0;i<(int)c.size();i++) 
        s+=d2(c[i],a[L[i]]);
    return s;
}

vector<double> perSSD(const vector<P>&c,const vector<P>&a,const vector<int>&L,int K){
    vector<double> s(K,0);
    for(int i=0;i<(int)c.size();i++) 
        s[L[i]]+=d2(c[i],a[L[i]]);
    return s;
}

vector<int> citiesPerAirport(const vector<int>&L,int K){
    vector<int> cnt(K,0);
    for(int l:L) cnt[l]++;
    return cnt;
}

void printResults(const string& method, const vector<P>&a,
                  const vector<double>&s, const vector<int>&cnt,
                  double total, int it, int K){

    cout<<" "<<method<<"\n\n";
    cout<<" Converged in : "<<it<<" iterations\n";
    cout<<" Total SSD    : "<<fixed<<setprecision(6)<<total<<"\n\n";
    for(int k=0;k<K;k++)
        cout<<" Airport "<<char('A'+k)
            <<" -> X="<<setw(9)<<a[k].x
            <<" Y="<<setw(9)<<a[k].y
            <<" | Cities Served : "<<setw(3)<<cnt[k]
            <<" | SSD : "<<s[k]<<"\n\n";
}

void gradient(const vector<P>&c,int K=3){
    auto a=initialize(c,K); 
    double prev=1e18; 
    int it=0;

    for(;it<5000;it++){
        auto L=assignCities(c,a);
        double ssd=SSD(c,a,L);
        vector<double> gx(K,0),gy(K,0);

        for(int i=0;i<(int)c.size();i++){
            int k=L[i];
            gx[k]+=-2*(c[i].x-a[k].x);
            gy[k]+=-2*(c[i].y-a[k].y);
        }
        for(int k=0;k<K;k++){
            a[k].x-=0.01*gx[k];
            a[k].y-=0.01*gy[k];
        }
        if(fabs(prev-ssd)<1e-9 && it>10){ 
            it++; break; 
        }
        prev=ssd;
    }

    auto L   = assignCities(c,a);
    auto s   = perSSD(c,a,L,K);
    auto cnt = citiesPerAirport(L,K);
    double total=accumulate(s.begin(),s.end(),0.0);

    printResults("METHOD A : Gradient Descent",a,s,cnt,total,it,K);
}

void newton(const vector<P>&c,int K=3){
    auto a = initialize(c,K);
    double prev = 1e18;
    int it = 0;
    for(; it < 500; it++){
        auto L = assignCities(c,a);
        double ssd = SSD(c,a,L);

        vector<double> gx(K,0), gy(K,0);
        vector<int> cnt(K,0);
        for(int i=0;i<(int)c.size();i++){
            int k = L[i];
            gx[k] += -2*(c[i].x - a[k].x);
            gy[k] += -2*(c[i].y - a[k].y);
            cnt[k]++;
        }
        for(int k=0;k<K;k++){
            if(cnt[k] > 0){
                double hessian = 2.0 * cnt[k];
                a[k].x -= gx[k] / hessian;
                a[k].y -= gy[k] / hessian;
            }
        }

        if(fabs(prev - ssd) < 1e-10 && it > 1){
            it++;
            break;
        }
        prev = ssd;
    }

    auto L   = assignCities(c,a);
    auto s   = perSSD(c,a,L,K);
    auto cnt = citiesPerAirport(L,K);
    double total = accumulate(s.begin(), s.end(), 0.0);
    printResults("METHOD B : Newton-Raphson (2nd Order)", a, s, cnt, total, it, K);
}

int main(){
    cout<<"Finding 3 Optimal Airport Locations\n\n";
    auto cities=loadCSV("cities.csv");

    gradient(cities);
    newton(cities);

    return 0;
}