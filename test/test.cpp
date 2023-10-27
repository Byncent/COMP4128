#include<cstdio>
#include <iostream>
#include<vector>
#include<set>
#include<cstring>
using namespace std;
const int maxn = 300010;
struct Edge{
    int s,t;
    int next;
    int vis;
}edge[2*maxn];
int head[maxn],E=0;
void add_edge(int s,int t)
{
    edge[E].s=s;
    edge[E].t=t;
    edge[E].vis=0;
    edge[E].next=head[s];
    head[s]=E++;
}
bool bridge;
int Time, dfn[maxn],low[maxn];
inline int min(int a,int b){return a<b?a:b;}
set<pair<int,int> >ans;
void dfs(int s)
{
    int i,t,id;
    dfn[s]=low[s]=++Time;
    for(i=head[s];i!=-1;i=edge[i].next)
    {
        if(edge[i].vis) continue;
        cout << "curr edge: " << s << " - " <<edge[i].t << '\n';
        ans.insert(make_pair(s,edge[i].t));
        edge[i].vis=edge[i^1].vis=1;
        t=edge[i].t;
        if(!dfn[t])
        {
            dfs(t);
            low[s]=min(low[s],low[t]);
        }
        else low[s]=min(low[s],dfn[t]);
        if(low[t]>dfn[s]) 
        {
            bridge=true;
            return ;
        }
    }
}
void SCC(int n)
{
    int i;
    Time=0;
    memset(dfn,0,sizeof(int)*(n+1));
    for(i=1;i<=n;i++) if(!dfn[i]){
        cout << "iter: " << i << '\n';
        dfs(i);
    }
    
        
}
int main()
{
    int n,m,i,j,a,b;
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        add_edge(a,b);
        add_edge(b,a);
    }
    bridge=false;
    SCC(n);
    if(bridge) puts("0");
    else 
    {
        for(auto it : ans)
            printf("%d %d\n",it.first, it.second);
    }
    return 0;
}