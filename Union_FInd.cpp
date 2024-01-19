#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;
int find(int u,vector<int>& alliance)
{
    if(u == alliance[u])
        return u;
    
    else
        return  find(alliance[u],alliance);
}
int combine (int u, int v,vector<int>& alliance,vector<int>& size,int* count)
{
     u = find(u,alliance);
     v = find(v,alliance);

     if(u != v)   
     {
       alliance[v] = u;
       size[u]=size[u]+size[v];
       *count=*count-1;
    }
    return size[u];
}
int main(int argc, char const *argv[])
{
    int n,m;
    cin>>n>>m;
    int count=n;
    int max_s=1;
    vector<int> alliance(n+1);
    vector<int> size(n+1,1);
    for(int i=1;i<=n;i++){
        alliance[i]=i;
    }
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        max_s=max(max_s,combine(a,b,alliance,size,&count));
        cout<<count<<" "<<max_s<<'\n';
    }
    return 0;
}

