// author : greenblatt
// link : https://www.acmicpc.net/problem/4195

#include <iostream>
#include <map>
using namespace std;

const int MAX_N = 200000 + 1;

int T, N;
int p[MAX_N];
map<string, int> nameMap;
char nameA[21], nameB[21];

int find(int n){
    if(p[n] < 0) return n;
    p[n] = find(p[n]);
    return p[n];
}

int merge(int a, int b){
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) return -p[ra];
    if(-p[ra] < -p[rb]) swap(ra, rb);
    p[ra] += p[rb];
    p[rb] = ra;
    return -p[ra];
}

void initTestCase(){
    for(int i = 0; i < MAX_N; i++) p[i] = -1;
    nameMap.clear();
}

int main(){
    scanf("%d\n", &T);
    while(T--){
        initTestCase();
        scanf("%d\n", &N);
        for(int i = 0; i < N; i++){
            scanf("%s %s\n", nameA, nameB);
            if(nameMap.count(nameA) == 0){
                nameMap[nameA] = nameMap.size();
            }
            if(nameMap.count(nameB) == 0){
                nameMap[nameB] = nameMap.size();
            }
            int a = nameMap[nameA];
            int b = nameMap[nameB];
            printf("%d\n", merge(a, b));
        }
    }
    return 0;
}