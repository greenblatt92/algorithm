// author : greenblatt
// link : https://www.acmicpc.net/problem/1717

#include <iostream>
using namespace std;

const int MAX_N = 1000000;
int N, M;
int p[MAX_N + 1];

int find(int n){
    if(p[n] < 0) return n;
    p[n] = find(p[n]);
    return p[n];
}

void merge(int a, int b){
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) return;
    p[ra] += p[rb];
    p[rb] = ra;
}

int main(){
    scanf("%d %d", &N, &M);
    
    for(int i = 0; i <= N; i++){
        p[i] = -1;
    }
    
    while(M--){
        int q, a, b;
        scanf("%d %d %d", &q, &a, &b);
        if(q == 0){
            merge(a, b);
        }else{
            if(find(a) == find(b)){
                printf("YES\n");
            }else{
                printf("NO\n");
            }
        }
    }
    return 0;
}