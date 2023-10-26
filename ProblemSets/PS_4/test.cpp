#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>
#include<string>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
struct node
{
    int q,id;
}p[1005];
int a[1005][1005],d[1005],n;
bool cmp(node a,node b)
{
    return a.q>b.q;
}
int main()
{
    int i,j,k,v;
    while(scanf("%d",&n)!=EOF)
    {
       for(i=1;i<=n;i++) for(j=1;j<=n;j++) a[i][j]=-1;
       for(i=1;i<=n;i++)
       {
           scanf("%d",&p[i].q);
           p[i].id=i;
       }
       sort(p+1,p+1+n,cmp);
       for(i=1;i<=n;i++)
       {
           d[p[i].id]=i;
       }
       scanf("%d",&k);
       while(k--)
       {
           scanf("%d%d%d",&i,&j,&v);
           i=d[i],j=d[j];
           if(a[i][j]==-1) a[i][j]=v;
           else a[i][j]=min(a[i][j],v);
       }
       int flag=0,ans=0;
       for(i=2;i<=n;i++)
       {
           v=10000000;
           for(j=1;j<i;j++)
           {
               if(p[j].q>p[i].q&&a[j][i]!=-1)
                v=min(v,a[j][i]);
           }
           if(v==10000000) flag=1;
           ans+=v;
           if(flag) break;
       }
       if(flag) ans=-1;
       printf("%d\n",ans);
    }
    return 0;
}