// poj1043
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int map[25][25],r[25],fn[25],fm[25],res[25],used[25];
int n,sum,match,m;
char id[25][50],ct,tmp[50],name[25][50];
bool in[25];

inline int cmp(int i,int j){
   if (memcmp(name[i],name[j],sizeof name[i]) <= 0) return 1;
   else return 0;
}

int path(int u){
   for (int v = 0;v < m;v ++) if (map[u][v] && used[v] == 0){
       used[v] = 1;
       if (fm[v] == -1 || path(fm[v])){
           fm[v] = u;
           fn[u] = v;
           return 1;
       }
   }
   return 0;
}

int hungary(){
   match = 0;
   memset(fn,-1,sizeof fn);
   memset(fm,-1,sizeof fm);
   for (int i = 0;i < n;i ++) if (fn[i] == -1){
       memset(used,0,sizeof used);
       match += path(i);
   }
   return match;
}

void getmatch(){
   int i,j;
   m = n;
   for (i = 0;i < n;i ++){
       for (j = 0;j < n;j ++) if (map[i][j]){
           map[i][j] = 0;
           if (hungary() != n){map[i][j] = 1;break;}
           map[i][j] = 1;
       }
       if (j == n) res[i] = -1 ;else res[i] = j;
   }
}

int main(){    
   scanf("%d",&n);
   for (int i = 0;i < n;i ++) scanf("%s",id[i]);
   memset(map,-1,sizeof map);
   memset(in,0,sizeof in);
   scanf("\n");
   sum = 0;
   for (scanf("%c",&ct);ct != 'Q';scanf("%c",&ct)){
       scanf("%s\n",tmp);
       int i;
       switch (ct){
           case 'E':
               for (i = 0;i < sum && strcmp(tmp,name[i]) != 0;i ++);
               if (i == sum) strcpy(name[sum ++],tmp);
               in[i] = 1;break;
           case 'L':
               for (i = 0;i < sum && strcmp(tmp,name[i]) != 0;i ++);
               in[i] = 0;break;
           case 'M':
               for (i = 0;i < n && strcmp(tmp,id[i]) != 0;i ++);
               for (int j = 0;j < sum;j ++) if (!in[j]) map[j][i] = 0;
               for (int j = sum;j < n;j ++) map[j][i] = 0;
               break;
       }
   }
   getmatch();
   for (int i = 0;i < n;i ++) r[i] = i;
   sort(r,r + n,cmp);
   for (int i = 0;i < n;i ++){
       printf("%s:",name[r[i]]);
       if (res[r[i]] == -1) printf("???\n");
       else printf("%s\n",id[res[r[i]]]);
   }
   return 0;
}