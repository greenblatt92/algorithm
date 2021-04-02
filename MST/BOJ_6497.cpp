// author : greenblatt
// link : https://www.acmicpc.net/problem/6497

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_V = 200000 + 1;
const int MAX_E = 200000 + 1;

struct Edge{
    int u;
    int v;
    int w;
    Edge():Edge(-1, -1, 0){}
    Edge(int from, int to, int weight):u(from), v(to), w(weight){}
    bool operator<(const Edge& e) const {
        return w < e.w;
    }
};

int V, E;
int p[MAX_V];
Edge edges[MAX_E];

int find(int n){
    if(p[n] < 0) return n;
    p[n] = find(p[n]);
    return p[n];
}

bool merge(int a, int b){
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) return true;
    p[rb] = ra;
    return false;
}

int main(){
    while(true){
        for(int i = 0; i < MAX_V; i++) p[i] = -1;
        scanf("%d %d\n", &V, &E);
        if(V == 0) break;
        
        int ans = 0;
        for(int i = 0; i < E; i++){
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            edges[i] = Edge(x, y, z);
            ans += z;
        }
        
        sort(edges, edges + E);

        for(int i = 0; i < E; i++){
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if(!merge(u, v)){
                ans -= w;
            }
        }
        
        printf("%d\n", ans);
    }
    return 0;
}