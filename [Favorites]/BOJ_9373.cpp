// author : greenblatt
// link : https://www.acmicpc.net/problem/9373

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAX_N = 1002 + 1;

struct Sensor{
    double x, y, r;
    Sensor():Sensor(0, 0, 0){}
    Sensor(double x1, double y1, double r1):x(x1), y(y1), r(r1){}
};

struct Edge{
    int u, v;
    double w;
    Edge():Edge(-1, -1, 0){}
    Edge(int from, int to, double weight):u(from), v(to), w(weight){}
    bool operator<(const Edge &e) const{
        return w < e.w;
    }
};

int T, W, N;
int p[MAX_N];
vector<Sensor> sensors;
vector<Edge> edges;

double getDist(Sensor s1, Sensor s2){
    double dist = sqrt((ll)(s1.x - s2.x) * (s1.x - s2.x) + (ll)(s1.y - s2.y) * (s1.y - s2.y));
    dist -= (s1.r + s2.r);
    if(dist <= 0) return 0;
    return dist;
}

double getDistFromLeftWall(Sensor s){
    return max((double)0, s.x - s.r);
}

double getDistFromRightWall(Sensor s){
    return max((double)0, W - s.x - s.r);
}

int find(int n){
    if(p[n] < 0) return n;
    p[n] = find(p[n]);
    return p[n];
}

void merge(int a, int b){
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) return;
    if(-p[ra] < -p[rb]) swap(ra, rb);
    p[ra] += p[rb];
    p[rb] = ra;
}

int main(){
    scanf("%d\n", &T);
    while(T--){
        scanf("%d\n", &W);
        scanf("%d\n", &N);
        
        for(int i = 0; i <= (N + 1); i++) p[i] = -1;
        sensors.clear();
        edges.clear();
        
        edges.push_back(Edge(0, N + 1, W));
        
        for(int i = 1; i <= N; i++){
            double x, y, r;
            scanf("%lf %lf %lf", &x, &y, &r);
            Sensor s = Sensor(x, y, r);
            sensors.push_back(s);
            edges.push_back(Edge(0, i, getDistFromLeftWall(s)));
            edges.push_back(Edge(N + 1, i, getDistFromRightWall(s)));
        }
        for(int i = 0; i < N - 1; i++){
            for(int j = i + 1; j < N; j++){
                edges.push_back(Edge(i + 1, j + 1, getDist(sensors[i], sensors[j])));
            }
        }
        
        sort(edges.begin(), edges.end());
        
        double ans = 0;
        for(int i = 0; i < edges.size(); i++){
            int u = edges[i].u;
            int v = edges[i].v;
            double w = edges[i].w;
            merge(u, v);
            if(find(0) == find(N + 1)){
                ans = w;
                break;
            }
        }
        if(ans == (double)0){
            puts("0");
        }else{
            printf("%.6lf\n", ans / (double)2);
        }
    }
    return 0;
}